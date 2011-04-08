#define FUSE_USE_VERSION  26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "ds_misc.h"


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

    printf("pnfs_readdir(%s, offset=%d)\n", name, offset);

    if ((clnt = clnt_create(server.mds_name, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(server.mds_name);
        return(-1);
    }

    req.name = name;
    req.d_off = offset;

	ret = readdir_ds_1(&req, &res, clnt);
    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
        return (-1);
    }

	while (res.res == 0) {
		printf("dirent : %s\n", res.dent.d_name);
		filler(buf, res.dent.d_name, NULL, 0);
        req.d_off = res.dent.d_off;
		ret = readdir_ds_1(&req, &res, clnt); 
        if (ret != RPC_SUCCESS) {
            printf("ret = %d\n",ret);
            clnt_perror(clnt, "call failed");
            return (-1);
        }
	} 

	closedir(dfd);

    return 0;
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
    size_t len;
    (void) fi;

	len = read_c(server.mds_name, name, offset, size, buf);
	printf("read(%s) offset : %d size %d buf = %s\n", name,
            (int) offset, len, buf);
    return len;
}

static int pnfs_write(const char *name, const char *buf, size_t size,
        off_t offset, struct fuse_file_info *fi)
{
    size_t len;
    (void) fi;

	len = write_c(server.mds_name, name, offset, size, buf);
	printf("write(%s) offset : %d size %d buf = %s\n", name,
            (int) offset, len, buf);
    return len;
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
  .readdir = pnfs_readdir,
  .open   = pnfs_open,
  .read   = pnfs_read,
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
    char *server;
    char *local_fs;
    char *remote_fs;
    int ret;

    /*
    if (argc != 6) {
        usage(argv[0]);
    }
    */

    /*
     * TODO:
     * Add the getopt code to fetch the options.
     * Right now we hard code the arguments.
     */
    server = "127.0.0.1";
    remote_fs = "/var/tmp/mnt1-back"; 
    local_fs = argv[1];

    printf("remote_sf %s server %s\n", remote_fs, server);

    ret = init_server(server, remote_fs, local_fs);

    return fuse_main(argc, argv, &pnfs_oper, NULL);
}

