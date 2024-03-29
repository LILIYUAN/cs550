/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "mds_ds_misc.h"
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

/*extern __thread int errno;*/

extern ds_t ds;
extern mds_t mds;

bool_t
getattr_ds_1_svc(getattr_req *argp, getattr_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    struct stat sbuf;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    result->res = stat(name, &sbuf);

    if (result->res != 0) {
        result->res = -errno;
    } else {
        result->sbuf.stat_dev = sbuf.st_dev;
        result->sbuf.stat_ino = sbuf.st_ino;
        result->sbuf.stat_mode = sbuf.st_mode;
        result->sbuf.stat_nlink = sbuf.st_nlink;
        result->sbuf.stat_uid = sbuf.st_uid;
        result->sbuf.stat_gid = sbuf.st_gid;
        result->sbuf.stat_rdev = sbuf.st_rdev;
        result->sbuf.stat_size = sbuf.st_size;
        result->sbuf.stat_blksize = sbuf.st_blksize;
        result->sbuf.stat_blocks = sbuf.st_blocks;
        result->sbuf.stat_atime = sbuf.st_atime;
        result->sbuf.stat_mtime = sbuf.st_mtime;
        result->sbuf.stat_ctime = sbuf.st_ctime;
    }

#ifdef DEBUG
    printf("getattr_ds_1_svc: name: %s resi: %d\n", name, result->res);
#endif
	return retval;
}

bool_t
readdir_ds_1_svc(readdir_req *argp, readdir_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    DIR *dirp;
    struct dirent dent;
    struct dirent *p = NULL;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    dirp = opendir(name);
    if (dirp == NULL) {
        result->res = -errno;
        return retval;
    }

    seekdir(dirp, argp->d_off);
    ret = readdir_r(dirp, &dent, &p);

    if (ret != 0) {
        result->res = -errno;
        closedir(dirp);
        return retval;
    }

    result->dent.d_ino = dent.d_ino;
    result->dent.d_off = dent.d_off;
    result->dent.d_reclen = dent.d_reclen;
    result->dent.d_type = dent.d_type;
    strcpy(result->dent.d_name, dent.d_name);
    result->res = 0;

    if (p == NULL)
        result->eof = 1;
    else 
        result->eof = 0;

#ifdef DEBUG
    printf("readdir_1_svc: dir=%s d_name=%s d_off=%d d_reclen=%d\n", name, dent.d_name, (int)dent.d_off, dent.d_reclen);
#endif
    closedir(dirp);
	return retval;
}

bool_t
mkdir_ds_1_svc(mkdir_req *argp, mkdir_res *result, struct svc_req *rqstp)
{
    bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = mkdir((const char *)name, (mode_t)argp->mode);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

    return retval;
}

bool_t
unlink_ds_1_svc(unlink_req *argp, unlink_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = unlink(name);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

	return retval;
}

bool_t
rmdir_ds_1_svc(rmdir_req *argp, rmdir_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = rmdir(name);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

	return retval;
}

bool_t
rename_ds_1_svc(rename_req *argp, rename_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char old[MAXPATHLEN];
    char new[MAXPATHLEN];

    sprintf(old, "%s/%s", ds.dir, argp->old);
    sprintf(new, "%s/%s", ds.dir, argp->new);

    ret = rename(old, new);
#ifdef DEBUG
    printf("rename_ds_1 : old=%s new=%s ret=%d errno=%d\n", old, new, ret, errno);
#endif

    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

	return retval;
}

bool_t
mknod_ds_1_svc(mknod_req *argp, mknod_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = mknod(name, argp->mode, argp->dev);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

	return retval;
}

bool_t
create_ds_1_svc(create_req *argp, create_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = creat(name, argp->mode);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

	return retval;
}

bool_t
open_ds_1_svc(open_req *argp, open_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int fd;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    fd = open(name, argp->flags, argp->mode);
    if (fd < 0) 
        result->res = -errno;
    else 
        result->res = fd;

    close(fd);

	return retval;
}

bool_t
close_ds_1_svc(close_req *argp, close_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
read_ds_1_svc(read_req *argp, read_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    int fd;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    fd = open(name, O_RDONLY);
    if (fd  < 0) {
        printf("Failed to open(%s) : errno %d\n", argp->name, errno);
        result->res = -errno;
        return (TRUE);
    }

    ret = pread(fd, result->data, argp->count, argp->offset);
    close(fd);

#ifdef DEBUG
    printf("read_ds_1_svc: name=%s count=%lu offset=%lu ret=%d data=%s\n",
            name, argp->count, argp->offset, ret, result->data);
#endif

    if (ret < 0)
        result->res = -errno;
    else 
        result->res = ret;

	return retval;
}

/*
 * This is a helper routine to recursively create the directories on the
 * data-server before writing to a file for the first time.
 *
 * Returns the file descriptor if successful else (-errno).
 */
int
create_and_open(char *fname)
{
    char name[MAXPATHLEN];
    char dname[MAXPATHLEN];
    char *p, *saveptr;
    int fd;
    int ret;

    /*
     * Extract the directory name from the given filepath.
     */
    sprintf(dname, "%s/%s", ds.dir, fname, MAXPATHLEN-1);
    name[0] = '\0';
    p = strrchr(dname, '/');
    *p = '\0';

#ifdef DEBUG
    printf("create_and_open: dname = %s\n", dname);
#endif
    p = strtok_r(dname, "/", &saveptr);
    while (p) {
        strcat(name, "/"); strcat(name, p);
        ret = mkdir(name, 0777);
#ifdef DEBUG
        printf("create_and_open: mkdir(%s) = %d\n", name, ret);
#endif
        /*
         * We either succeed or the directory exists. If not we should return
         * failure.
         */
        if (ret != 0 && errno != EEXIST) {
            ret = - errno;
            return (ret);
        }
        p = strtok_r(NULL, "/", &saveptr); 
    }

    ret = 0;
    sprintf(name, "%s/%s", ds.dir, fname);
    fd = open(name, O_CREAT|O_RDWR, 0777);

    if (fd < 0) {
        printf("Failed to create the extent file : %s\n", name);
        ret = -errno;
    } else {
        ret = fd;
    }

    return (ret);
}

bool_t
write_ds_1_svc(write_req *argp, write_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    int fd;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    fd = open(name, O_RDWR);
    if (fd  < 0) {
        /*
         * If the file does not exist : it is being written for the first time.
         * Hence, create it.
         */
        fd = create_and_open(argp->name);
        if (fd < 0) { 
            printf("Failed to open(%s) : errno %d\n", argp->name, errno);
            result->res = -errno;
            return (TRUE);
        }
    }

    ret = pwrite(fd, argp->data, argp->count, argp->offset);
    close(fd);

    if (ret < 0)
        result->res = -errno;
    else 
        result->res = ret;

	return retval;
}

bool_t
lookup_ds_1_svc(lookup_req *argp, lookup_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
truncate_ds_1_svc(truncate_req *argp, truncate_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int res;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    res = truncate(name, argp->len);
    if (res < 0) 
        result->res = -errno;
    else
        result->res = 0;
    
	return retval;
}

bool_t
statfs_ds_1_svc(statfs_req *argp, statfs_res *result, struct svc_req *rqstp)
{
	bool_t retval;
    struct statfs sbuf;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = statfs(name, &sbuf);

    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

    result->stat.f_type = sbuf.f_type;     /* type of file system (see below) */
    result->stat.f_bsize = sbuf.f_bsize;    /* optimal transfer block size */
    result->stat.f_blocks = sbuf.f_blocks;   /* total data blocks in file system */
    result->stat.f_bfree = sbuf.f_bfree;    /* free blocks in fs */
    result->stat.f_bavail = sbuf.f_bavail;   /* free blocks avail to unprivileged user */
    result->stat.f_files = sbuf.f_files;    /* total file nodes in file system */
    result->stat.f_ffree = sbuf.f_ffree;    /* free file nodes in fs */
    result->stat.f_fsid.__val[0] = sbuf.f_fsid.__val[0]; /* file system id */
    result->stat.f_fsid.__val[1] = sbuf.f_fsid.__val[1]; /* file system id */
    result->stat.f_namelen = sbuf.f_namelen;  /* maximum length of filenames */
    
	return retval;
}

bool_t
chmod_ds_1_svc(chmod_req *argp, chmod_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = chmod(name, argp->mode);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

bool_t
chown_ds_1_svc(chown_req *argp, chown_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, argp->name);

    ret = chown(name, argp->uid, argp->gid);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;


	return retval;
}

bool_t
link_ds_1_svc(link_req *argp, link_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char old[MAXPATHLEN];
    char new[MAXPATHLEN];

    sprintf(old, "%s/%s", ds.dir, argp->old);
    sprintf(new, "%s/%s", ds.dir, argp->new);

    ret = link(old, new);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

bool_t
symlink_ds_1_svc(symlink_req *argp, symlink_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char old[MAXPATHLEN];
    char new[MAXPATHLEN];

    sprintf(old, "%s/%s", ds.dir, argp->old);
    sprintf(new, "%s/%s", ds.dir, argp->new);

    ret = symlink(old, new);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

bool_t
readlink_ds_1_svc(readlink_req *argp, readlink_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", ds.dir, name);
    ret = readlink(name, result->buf, argp->bufsize);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}


int
dsprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
