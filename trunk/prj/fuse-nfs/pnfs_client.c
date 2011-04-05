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

static int pnfs_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", server.remote_mntpt, path);
	res = getattr_c(server.mds_name, name, stbuf); 
	printf("getattr : path %s res = %d\n", name, res);

    return res;
}

static int pnfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
/*
    md_readdir_req req;
    md_readir_res res;
*/
    int ret;
	DIR *dfd;
	struct dirent dent;
	struct dirent *res = NULL;
    char name[MAXPATHLEN];

    (void) offset;
    (void) fi;

    sprintf(name, "%s/%s", server.remote_mntpt, path);
    printf("pnfs_readdir(%s)\n", name);
	dfd = opendir(name);	
	ret = readdir_r(dfd, &dent, &res);
	while (res) {
		printf("dirent : %s\n", dent.d_name);
		filler(buf, dent.d_name, NULL, 0);
		ret = readdir_c(server.mds_name, name, offset, &dent);
	} 

	closedir(dfd);

    return 0;
}

static int pnfs_mkdir(const char *dname, mode_t mode)
{
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", server.remote_mntpt, dname);

    ret = mkdir_c(server.mds_name, name, mode);

    return (ret);
}

static int pnfs_unlink(char *fname)
{
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", server.remote_mntpt, fname);

    ret = unlink_c(server.mds_name, name);

    return (ret);
}

static int pnfs_open(const char *path, struct fuse_file_info *fi)
{
	int fd;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", server.remote_mntpt, path);
    printf("pnfs_open(%s)\n", name);
    /*
     * TODO : We could fetch the layout of the file as part of this access.
     * This would reduce another call to the MDS.
     */

	fd = open(name, O_RDWR);
	close(fd);

    return (0);
}

static int pnfs_rmdir()
{
}

static int pnfs_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    size_t len;
	int fd;
    char name[MAXPATHLEN];

    (void) fi;

    sprintf(name, "%s/%s", server.remote_mntpt, path);
	fd = open(name, O_RDONLY);
	len = pread(fd, buf, size, offset);
	close(fd);
	printf("read(%s) offset : %d size %d buf = %s\n", name, (int) offset, len, buf);
    return len;
}

int 
init_server(char *servername, char *remote_fs, char *local_fs)
{
    server.mds_name = servername;
    server.remote_mntpt = remote_fs;
    server.local_mntpt = local_fs;

    printf("init_server : local_mntpt = %s\n", server.local_mntpt);

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
    server = argv[2];
    remote_fs = "/var/tmp/mnt1-back"; 
    local_fs = argv[3];

    printf("remote_sf %s\n", remote_fs);

    ret = init_server(server, remote_fs, local_fs);

    return fuse_main(argc, argv, &pnfs_oper, NULL);
}

