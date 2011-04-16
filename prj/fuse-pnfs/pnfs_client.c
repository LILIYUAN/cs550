#define FUSE_USE_VERSION  26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "mds_ds.h"
#include "mds_ds_misc.h"


/*
 * For now we support only 16 data-servers.
 */
#define MAX_DS  16
#define MAXADDR  128

typedef struct server {
    char    *mds_name;
    char    *local_mntpt;
    char    *remote_mntpt;
    fsid_t  fsid;
/*    CLIENT  *mds_clnt; */
    int     n_ds;
    char    *ds_name[MAX_DS];
/*    CLIENT  *ds_clnt[16]; */
} server_t;

/*
 * The meta-server and data-server details for this mount point.
 */
server_t server;

static int pnfs_getattr(const char *name, struct stat *stbuf)
{
    int res = 0;

	printf("pnfs_getattr : path %s Calling getattr_c\n", name);
	res = getattr_c(server.mds_name, name, stbuf); 
	printf("pnfs_getattr : path %s res = %d\n", name, res);

    return res;
}

/*
static int pnfs_readdir(const char *name, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
    int ret;
	DIR *dfd;
	readdir_res dent; 
    off_t off = offset;

    (void) offset;
    (void) fi;

    printf("pnfs_readdir(%s, offset=%d)\n", name, offset);
	ret = readdir_c(server.mds_name, name, offset, dent);
	while (ret == 0) {
		printf("dirent : %s\n", dent->d_name);
		filler(buf, dent->d_name, NULL, 0);
		ret = readdir_c(server.mds_name, name, offset, dent);
	} 

	closedir(dfd);

    free(dent);
    return 0;
}
*/

static int pnfs_readlink(const char *name, char *buf, size_t size)
{
    return(readlink_c(server.mds_name, name, buf, size));
}

static int pnfs_readdir(const char *name, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
	DIR *dfd;
    readdir_req req;
	readdir_res res; 
    off_t off = offset;
    bool_t ret;
    CLIENT *clnt;

    (void) offset;
    (void) fi;

    printf("pnfs_readdir(%s, offset=%d)\n", name, (int)offset);

    if ((clnt = clnt_create(server.mds_name, MDPROG, MDVERS, "tcp")) == NULL) {
        clnt_pcreateerror(server.mds_name);
        return(-1);
    }

    req.name = (pathname) name;
    req.d_off = offset;

    do {
        printf("pnfs_readdir: Before readdir_ds_1\n");
        ret = readdir_ds_1(&req, &res, clnt);
        printf("pnfs_readdir: Finished readdir_ds_1\n");
        if (ret != RPC_SUCCESS) {
            printf("ret = %d\n",ret);
            clnt_perror(clnt, "call failed");
            return (-1);
        }

        if (res.eof != 1) {
            printf("dirent : %s eof = %d\n", res.dent.d_name, res.eof);
            printf("dirent : res.res = %d\n", res.res);
            filler(buf, res.dent.d_name, NULL, 0);
        }
        req.d_off = res.dent.d_off;
        printf("pnfs_readdir: next iteration\n");
    } while (res.res == 0 && res.eof != 1);

    clnt_destroy(clnt);

    return 0;
}

static int pnfs_mknode(const char *name, mode_t mode, dev_t dev)
{
    return(mknod_c(server.mds_name, name, mode, dev));
}

static int pnfs_mkdir(const char *dname, mode_t mode)
{
    int ret;

    ret = mkdir_c(server.mds_name, dname, mode);

    return (ret);
}

static int pnfs_unlink(char *fname)
{
    int ret;

    ret = unlink_c(server.mds_name, fname);

    return (ret);
}

static int pnfs_rmdir(const char *name)
{
    return(rmdir_c(server.mds_name, name));
}

static int pnfs_symlink(const char *old, const char *new)
{
    return(symlink_c(server.mds_name, old, new)); 
}

static int pnfs_rename(const char *old, const char *new)
{
    return(rename_c(server.mds_name, old, new));
}

static int pnfs_link(const char *old, const char *new)
{
    return(link_c(server.mds_name, old, new));
}

static int pnfs_chmod(const char *name, mode_t mode)
{
    return(chmod_c(server.mds_name, name, mode));
}

static int pnfs_chown(const char *name, uid_t uid, gid_t gid)
{
    return(chown_c(server.mds_name, name, uid, gid));
}

static int pnfs_truncate(const char *name, off_t off)
{
    return(truncate_c(server.mds_name, name, off));
}

static int pnfs_create(const char *name, mode_t mode, struct fuse_file_info *fi)
{
    return(create_c(server.mds_name, name, mode));
}

static int pnfs_open(const char *name, struct fuse_file_info *fi)
{
	int fd;

    printf("pnfs_open(%s)\n", name);
    /*
     * TODO : We could fetch the layout of the file as part of this access.
     * This would reduce another call to the MDS.
     */

	fd = open(name, O_RDWR);
	close(fd);

    return (0);
}

static int pnfs_read(const char *name, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    size_t count;
    size_t len;
    off_t  cur_off;
    (void) fi;
    char *bufp;
    layout_rec ext;
    layout_rec *extp = &ext;
    getlayout_res layout;
    getlayout_req req;
    size_t dummy;

    /*
     * Our RPC call supports 4K chunk reads. So, we break this len into 4K
     * chunks.
     */
    count = size;
    cur_off = offset;
    bufp = buf;
    memset((void *)extp, 0, sizeof (layout_rec));
    while (count != 0) {
        len = MIN(count, SIZE);

        printf("pnfs_read(%s) offset : %d len %d mds_name\n", name, (int) cur_off, len, server.mds_name);
        /*
         * Check if the extent has mapping to the cur_off. If not fetch it using
         * getlayout.
         */
        if (!(cur_off >= ext.off && (cur_off + len) < (ext.off + ext.len))) {
            getlayout_c(server.mds_name, name, cur_off, len, OPREAD, &dummy, &ext);
        }

        printf("pnfs_read(%s) : After getlayout : off=%d len=%d dsname=%s extname=%s\n",
                name, (int) ext.off, (int) ext.len, ext.dsname, ext.extname);

        len = read_c(ext.dsname, ext.extname, cur_off - ext.off, len, bufp);
        printf("write(%s) cur_off : %d len %d buf = %s\n", name,
                (int) cur_off, len, bufp);
        if (len <= 0) 
            break;

        count -= len;
        cur_off += len;
        bufp += len;
    }
    return (size - count);
}

static int pnfs_write(const char *name, const char *buf, size_t size,
        off_t offset, struct fuse_file_info *fi)
{
    size_t  count;
    size_t  len;
    off_t   cur_off;
    (void) fi;
    char *bufp;
    layout_rec ext;
    layout_rec *extp = &ext;
    getlayout_res layout;
    getlayout_req req;
    size_t dummy;

    /*
     * We write in chunks of 4K.
     */
    count = size;
    cur_off = offset;
    bufp = buf;
    memset((void *)extp, 0, sizeof (layout_rec));
    while (count != 0) {
        len = MIN(count, SIZE);

        printf("pnfs_write(%s) offset : %d len %d mds_name\n", name, (int) cur_off, len, server.mds_name);
        /*
         * Check if the extent has mapping to the cur_off. If not fetch it using
         * getlayout.
         */
        if (!(cur_off >= ext.off && (cur_off + len) < (ext.off + ext.len))) {
            getlayout_c(server.mds_name, name, cur_off, len, OPWRITE, &dummy, &ext);
        }

        printf("pnfs_write(%s) : After getlayout : off=%d len=%d dsname=%s extname=%s\n",
                name, (int) ext.off, (int) ext.len, ext.dsname, ext.extname);

        len = write_c(ext.dsname, ext.extname, cur_off - ext.off, len, bufp);
        printf("write(%s) cur_off : %d len %d buf = %s\n", name,
                (int) cur_off, len, bufp);
        if (len <= 0) 
            break;

        count -= len;
        cur_off += len;
        bufp += len;
    }
    return (size - count);
}

static int pnfs_statfs(const char *name, struct statvfs *buf)
{
    return(statfs_c(server.mds_name, name, buf));
}

int 
init_server(char *servername, char *remote_fs, char *local_fs)
{
    server.mds_name = servername;
    server.remote_mntpt = remote_fs;
    server.local_mntpt = local_fs;

    printf("init_server : local_mntpt=%s mds_name=%s\n", server.local_mntpt, server.mds_name);

    /*
     * Contact the server and make sure the remote-fs has been shared.
     */
/*
    server->clnt = clnt_create(server, MDPROG, MDVERS, "tcp");
    if (server->clnt == NULL) {
        clnt_pcreateerror(server);
        return (-1);
    }

    ret = mount_1(&req, &res);
*/

    return (0);

}

static struct fuse_operations pnfs_oper = {
  .getattr   = pnfs_getattr,
  .readlink = pnfs_readlink,
  .readdir  = pnfs_readdir,
  .mknod    = pnfs_mknode,
  .mkdir    = pnfs_mkdir,
  .unlink   = pnfs_unlink,
  .rmdir    = pnfs_rmdir,
  .symlink  = pnfs_symlink,
  .rename   = pnfs_rename,
  .link     = pnfs_link,
  .chmod    = pnfs_chmod,
  .chown    = pnfs_chown,
  .truncate = pnfs_truncate,

  .create   = pnfs_create,
  .open     = pnfs_open,
  .read     = pnfs_read,
  .write    = pnfs_write,
  .statfs   = pnfs_statfs,
  /*.lookup   = pnfs_lookup,*/
  /*.close    = pnfs_close,*/
};

void usage(char *name)
{
    printf("Usage : %s -S <server_name> -f <filesystem> <local_mountpoint>\n", name);
    printf("server_name : The name of the metadata server\n");
}

/*
 */
int main(int argc, char *argv[])
{
    char *server = NULL;
    char *local_fs = NULL;
    char *remote_fs = NULL;
    int ret, opt, i, debug = 0;
    int fuseargc = 0;
    char *fuseargv[50];

    if (argc < 6) {
        usage(argv[0]);
        return (1);
    }


    while ((opt = getopt(argc, argv, "S:f:d")) != -1) {
        switch (opt) {
            case 'S':
                server = optarg;
                break;
            case 'f':
                remote_fs = optarg;
                break;
            case 'd':
                debug = 1;
                break;
        }
    }

    local_fs = argv[optind];
    printf("server = %s remote_fs = %s local_fs = %s\n",
            server, remote_fs, local_fs);

    if (!server || !remote_fs || !local_fs) {
        usage(argv[0]);
        return (1);
    }

    ret = init_server(server, remote_fs, local_fs);

    /*
     * Copy the remaining arguments to fuseargs for it to process
     */
    fuseargv[fuseargc] = argv[0]; fuseargc++;
    if (debug) {
        fuseargv[fuseargc] = "-d";
        fuseargc++;
    }

    for (i = optind+1; i < argc; i++) {
        fuseargv[fuseargc] = argv[i];
        fuseargc++;
    }
    fuseargv[fuseargc] = local_fs; fuseargc++;

#ifdef DEBUG
    printf("Fuse arguments : fuseargc=%d fuseargv = [ ", fuseargc);
    for (i = 0; i < fuseargc; i++) {
        printf("%s ,", fuseargv[i]);
    }
    printf("]\n");
#endif

    return fuse_main(fuseargc, fuseargv, &pnfs_oper, NULL);
}

