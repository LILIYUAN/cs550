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

extern mds_t mds;

int
get_alloc_ds_svr(void)
{
    return (mds.nxt_alloc_ds++ % mds.ds_cnt);
}

int 
get_create_ds_svr(void)
{
    return (mds.nxt_create_ds++ % mds.ds_cnt);
}

/*
 * READ : argp->op == READ request.
 *  - This is a read request so, we open the corresponding file and then
 *      - search for the argp->offset in the list of records.
 *        copy the matching records into the result
 *
 * WRITE :
 *  - Here we check if the record exists (just like for READ). If found return
 *  the entry.
 *  - If not found create a new record for the give length and return it.
 *
 * LOCKING :
 * We lock the file on the metadata server as below :
 * - We take a Shared lock if this is a READ operation
 * - We take an exclusive lock if this is a WRITE operation.
 */ 
bool_t
getlayout_1_svc(getlayout_req *argp, getlayout_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    FILE *fh;
    char name[MAXPATHLEN];
    size_t sz;
    int op = argp->op;
    layout_rec rec;
    off_t start = 0, end = 0;
    off_t ds_start = 0, ds_end = 0;
    int ds;
    int fd;
    int recs = 0;

    sprintf(name, "%s/%s", mds.dir, argp->fname);
    if ((fh = fopen(name, "rw")) == NULL) {
        result->cnt = -errno;
        return (retval);
    }

    fd = fileno(fh);

    if (argp->op == OPREAD)
        flock(fd, LOCK_SH);
    else 
        flock(fd, LOCK_EX);

    /*
     * Read the size of the file in.
     */
    fscanf(fh, "%lu\n", (unsigned long *)&sz);

    result->cnt = 0;
    result->more_recs = 0;
    while (!feof(fh)) {
        fscanf(fh, "%lu %lu %s %s\n", &rec.off, &rec.len, &rec.dsname,
                rec.extname);

#ifdef DEBUG
        printf("rec : off=%lu len=%lu ds=%s extname=%s\n",
                rec.off, rec.len, rec.dsname, rec.extname);
#endif

        if (argp->offset >= rec.off && argp->len <= rec.len) {
            /*
             * Found a record. Copy it.
             */
            result->recs[result->cnt].off = rec.off;
            result->recs[result->cnt].len = rec.len;
            strcpy(result->recs[result->cnt].dsname, rec.dsname);
            strcpy(result->recs[result->cnt].extname, rec.extname);
            result->cnt++;

            if (end < (rec.off + rec.len)) {
                end = rec.off + rec.len;
            }
        } 
        if (result->cnt >  MAXCOUNT) {
            result->more_recs = 1;
            break;
        }
        recs++;
    }

    /*
     * If this is a READ op we return the records that have found.
     */
    if (argp->op == OPREAD) {
        goto windup; 
    }

    /*
     * We reach here if this is a WRITE op.
     * We check if we have found records for the requested range. If not we add
     * a new extent record for the remaining range.
     */
    if (end >= (argp->offset + argp->len)) {
        goto windup; 
    }

    /*
     * We need to allocate a new extent for this file. So, we pick a ds server
     * for it.
     */
    ds = get_alloc_ds_svr();

    /*
     * We now allocate a new extent at the end of the file.
     */
    fseek(fh, 0, SEEK_END);

    while (end < (argp->offset + argp->len)) {
        fprintf(fh, "%lu %lu %s %s.ext%d\n", end+1, STRIPE_SZ, mds.ds[ds], argp->fname, recs);
        end += STRIPE_SZ;
        recs++;
        result->recs[result->cnt].off = rec.off;
        result->recs[result->cnt].len = rec.len;
        strcpy(result->recs[result->cnt].dsname, rec.dsname);
        strcpy(result->recs[result->cnt].extname, rec.extname);
        result->cnt++;
    }

    /*
     * Update the size of the file now.
     */
    if (sz < (argp->offset + argp->len)) {
        fseek(fh, 0, SEEK_SET);
        fprintf(fh, "%lu\n", (argp->offset + argp->len));
    }

windup:
    flock(fd, LOCK_UN);
    fclose(fh);
	return retval;
}

/*
 * The size of the file is saved as the first line of the file.
 * This routine opens the file and returns the size of the file.
 */
size_t
getsize(char *name)
{
    FILE *fh;
    size_t sz;

    if ((fh = fopen(name, "r")) == NULL) {
        return (0);
    }

    fscanf(fh, "%lu", (unsigned long *)&sz);
    fclose(fh);
    return(sz);
}

/*
 * Same as ds_server.
 * Here we might have to read the contents of the first line of the file for the
 * size value.
 */
bool_t
getattr_mds_1_svc(getattr_req *argp, getattr_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    struct stat sbuf;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

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
        result->sbuf.stat_blksize = sbuf.st_blksize;
        result->sbuf.stat_blocks = sbuf.st_blocks;
        result->sbuf.stat_atime = sbuf.st_atime;
        result->sbuf.stat_mtime = sbuf.st_mtime;
        result->sbuf.stat_ctime = sbuf.st_ctime;
        result->sbuf.stat_size = getsize(name); 
    }

#ifdef DEBUG
    printf("getattr_mds_1_svc: name: %s resi: %d\n", name, result->res);
#endif
	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
readdir_mds_1_svc(readdir_req *argp, readdir_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    DIR *dirp;
    struct dirent dent;
    struct dirent *p = NULL;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

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
    printf("readdir_mds_1_svc: dir=%s d_name=%s d_off=%d d_reclen=%d\n", name, dent.d_name, (int)dent.d_off, dent.d_reclen);
#endif
    closedir(dirp);
	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
mkdir_mds_1_svc(mkdir_req *argp, mkdir_res *result, struct svc_req *rqstp)
{
    bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

    ret = mkdir((const char *)name, (mode_t)argp->mode);
    if (ret != 0)
        result->res = -errno;
    else
        result->res = 0;

    return retval;
}

/*
 * We will need to parse the contents of the file to find all the ds_servers
 * that have the stripes of this file and unlink them.
 */
bool_t
unlink_mds_1_svc(unlink_req *argp, unlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * We will need to parse the contents of the file to find all the ds_servers
 * that have the stripes of this file and unlink them.
 */
bool_t
rmdir_mds_1_svc(rmdir_req *argp, rmdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * We will need to parse the contents of the file to find all the ds_servers
 * that have the stripes of this file and rename them.
 */
bool_t
rename_mds_1_svc(rename_req *argp, rename_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
mknod_mds_1_svc(mknod_req *argp, mknod_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

    ret = mknod(name, argp->mode, argp->dev);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
create_mds_1_svc(create_req *argp, create_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];
    FILE *fh;

    sprintf(name, "%s/%s", mds.dir, argp->name);

    ret = creat(name, argp->mode);
    if (ret != 0) 
        result->res = -errno;
    else 
        result->res = 0;

    /*
     * Initialize the size to 0
     */
    fh = fopen(name, "w");
    fprintf(fh, "0\n");

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
open_mds_1_svc(open_req *argp, open_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int fd;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

    fd = open(name, argp->flags, argp->mode);
    if (fd < 0) 
        result->res = -errno;
    else 
        result->res = fd;

    close(fd);

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
close_mds_1_svc(close_req *argp, close_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * This should NOT be called on MDS. So, we can eliminate this.
 */
bool_t
read_mds_1_svc(read_req *argp, read_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * This should NOT be called on MDS. So, we can eliminate this.
 */
bool_t
write_mds_1_svc(write_req *argp, write_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * Same as ds_server
 */
bool_t
lookup_mds_1_svc(lookup_req *argp, lookup_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * This is a little complicated.
 * - If we are reducing the size :
 *      - Walk through all the ds_server entries and unlink those stripes which
 *      fall out of the range.
 *      - Truncate the partial length if any.
 *      - Update the size.
 * - For the size is extended
 *      - Update the size.
 */
bool_t
truncate_mds_1_svc(truncate_req *argp, truncate_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
statfs_mds_1_svc(statfs_req *argp, statfs_res *result, struct svc_req *rqstp)
{
	bool_t retval;
    struct statfs sbuf;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

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

/*
 * Same as ds_server.
 */
bool_t
chmod_mds_1_svc(chmod_req *argp, chmod_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

    ret = chmod(name, argp->mode);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
chown_mds_1_svc(chown_req *argp, chown_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, argp->name);

    ret = chown(name, argp->uid, argp->gid);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

/*
 * Same as ds_server.
 */
bool_t
link_mds_1_svc(link_req *argp, link_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char old[MAXPATHLEN];
    char new[MAXPATHLEN];

    sprintf(old, "%s/%s", mds.dir, argp->old);
    sprintf(new, "%s/%s", mds.dir, argp->new);

    ret = link(old, new);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

/*
 * Same as ds_server.
 * NEEDS SOME THOUGHT
 */
bool_t
symlink_mds_1_svc(symlink_req *argp, symlink_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char old[MAXPATHLEN];
    char new[MAXPATHLEN];

    sprintf(old, "%s/%s", mds.dir, argp->old);
    sprintf(new, "%s/%s", mds.dir, argp->new);

    ret = symlink(old, new);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

/*
 * Same as ds_server.
 * NEEDS SOME THOUGHT
 */
bool_t
readlink_mds_1_svc(readlink_req *argp, readlink_res *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    int ret;
    char name[MAXPATHLEN];

    sprintf(name, "%s/%s", mds.dir, name);
    ret = readlink(name, result->buf, argp->bufsize);
    if (ret < 0)
        result->res = -errno;
    else
        result->res = 0;

	return retval;
}

bool_t
mount_mds_1_svc(mount_req *argp, mount_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

int
mdsprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
