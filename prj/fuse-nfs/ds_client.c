/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ds_misc.h"
#include "mds_misc.h"
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

void
dsprog_1(char *host)
{
	CLIENT *clnt;
	enum clnt_stat retval_1;
	getattr_res result_1;
	getattr_req  getattr_ds_1_arg;
	enum clnt_stat retval_2;
	readdir_res result_2;
	readdir_req  readdir_ds_1_arg;
	enum clnt_stat retval_3;
	mkdir_res result_3;
	mkdir_req  mkdir_ds_1_arg;
	enum clnt_stat retval_4;
	unlink_res result_4;
	unlink_req  unlink_ds_1_arg;
	enum clnt_stat retval_5;
	rmdir_res result_5;
	rmdir_req  rmdir_ds_1_arg;
	enum clnt_stat retval_6;
	rename_res result_6;
	rename_req  rename_ds_1_arg;
	enum clnt_stat retval_7;
	mknod_res result_7;
	mknod_req  mknod_ds_1_arg;
	enum clnt_stat retval_8;
	create_res result_8;
	create_req  create_ds_1_arg;
	enum clnt_stat retval_9;
	open_res result_9;
	open_req  open_ds_1_arg;
	enum clnt_stat retval_10;
	close_res result_10;
	close_req  close_ds_1_arg;
	enum clnt_stat retval_11;
	read_res result_11;
	read_req  read_ds_1_arg;
	enum clnt_stat retval_12;
	write_res result_12;
	write_req  write_ds_1_arg;
	enum clnt_stat retval_13;
	lookup_res result_13;
	lookup_req  lookup_ds_1_arg;
	enum clnt_stat retval_14;
	truncate_res result_14;
	truncate_req  truncate_ds_1_arg;
	enum clnt_stat retval_15;
	statfs_res result_15;
	statfs_req  statfs_ds_1_arg;
	enum clnt_stat retval_16;
	chmod_res result_16;
	chmod_req  chmod_ds_1_arg;
	enum clnt_stat retval_17;
	chown_res result_17;
	chown_req  chown_ds_1_arg;
	enum clnt_stat retval_18;
	link_res result_18;
	link_req  link_ds_1_arg;
	enum clnt_stat retval_19;
	symlink_res result_19;
	symlink_req  symlink_ds_1_arg;
	enum clnt_stat retval_20;
	readlink_res result_20;
	readlink_req  readlink_ds_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DSPROG, DSVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	retval_1 = getattr_ds_1(&getattr_ds_1_arg, &result_1, clnt);
	if (retval_1 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_2 = readdir_ds_1(&readdir_ds_1_arg, &result_2, clnt);
	if (retval_2 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_3 = mkdir_ds_1(&mkdir_ds_1_arg, &result_3, clnt);
	if (retval_3 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_4 = unlink_ds_1(&unlink_ds_1_arg, &result_4, clnt);
	if (retval_4 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_5 = rmdir_ds_1(&rmdir_ds_1_arg, &result_5, clnt);
	if (retval_5 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_6 = rename_ds_1(&rename_ds_1_arg, &result_6, clnt);
	if (retval_6 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_7 = mknod_ds_1(&mknod_ds_1_arg, &result_7, clnt);
	if (retval_7 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_8 = create_ds_1(&create_ds_1_arg, &result_8, clnt);
	if (retval_8 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_9 = open_ds_1(&open_ds_1_arg, &result_9, clnt);
	if (retval_9 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_10 = close_ds_1(&close_ds_1_arg, &result_10, clnt);
	if (retval_10 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_11 = read_ds_1(&read_ds_1_arg, &result_11, clnt);
	if (retval_11 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_12 = write_ds_1(&write_ds_1_arg, &result_12, clnt);
	if (retval_12 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_13 = lookup_ds_1(&lookup_ds_1_arg, &result_13, clnt);
	if (retval_13 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_14 = truncate_ds_1(&truncate_ds_1_arg, &result_14, clnt);
	if (retval_14 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_15 = statfs_ds_1(&statfs_ds_1_arg, &result_15, clnt);
	if (retval_15 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_16 = chmod_ds_1(&chmod_ds_1_arg, &result_16, clnt);
	if (retval_16 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_17 = chown_ds_1(&chown_ds_1_arg, &result_17, clnt);
	if (retval_17 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_18 = link_ds_1(&link_ds_1_arg, &result_18, clnt);
	if (retval_18 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_19 = symlink_ds_1(&symlink_ds_1_arg, &result_19, clnt);
	if (retval_19 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_20 = readlink_ds_1(&readlink_ds_1_arg, &result_20, clnt);
	if (retval_20 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int getattr_c(char *ds_svr, char *path, struct stat *buf)
{
    getattr_req req;
    getattr_res res;
    CLIENT *clnt;
    bool_t ret;

#ifdef DEBUG
    printf("getattr_c(ds_svr=%s, path=%s, sbuf)\n", ds_svr, path);
#endif
    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;

    ret = getattr_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    } else
        errno = 0;

    // individually copy the items
    buf->st_dev = res.sbuf.stat_dev;
    buf->st_ino = res.sbuf.stat_ino;
    buf->st_mode = res.sbuf.stat_mode;
    buf->st_nlink = res.sbuf.stat_nlink; 
    buf->st_uid = res.sbuf.stat_uid; 
    buf->st_gid = res.sbuf.stat_gid;
    buf->st_rdev = res.sbuf.stat_rdev; 
    buf->st_size = res.sbuf.stat_size;
    buf->st_blksize = res.sbuf.stat_blksize;
    buf->st_blocks =  res.sbuf.stat_blocks;
    buf->st_atime = res.sbuf.stat_atime;
    buf->st_mtime = res.sbuf.stat_mtime;
    buf->st_ctime = res.sbuf.stat_ctime;

    clnt_destroy(clnt);
    return res.res;
}

int readdir_c(char *ds_svr, char *path, off_t offset, struct dirent *dentry)
{
    readdir_req req;
    readdir_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.d_off = offset;

    ret = readdir_ds_1(&req,&res,clnt);

#ifdef DEBUG
    printf("readdir_c: Returned from readdir_ds_1()\n");
#endif
    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

#ifdef DEBUG
    /*
    printf("readdir_c : d_name=%s d_ino=%ul d_off=%l d_reclen=%d d_type=%d\n",
            res.dent.d_name, res.dent.d_ino, res.dent.d_off, res.dent.d_reclen, res.dent.d_type);
            */
#endif
    // individually copy the items
    printf(" Here 0\n");
    dentry->d_ino = (int) res.dent.d_ino;
    dentry->d_ino = 0;
    printf(" Here 1\n");
    dentry->d_off = (int) res.dent.d_off;
    printf(" Here 2\n");
    dentry->d_reclen = res.dent.d_reclen;
    printf(" Here 3\n");
    dentry->d_type = res.dent.d_type;
    printf(" Here 4\n");
    strcpy(dentry->d_name, res.dent.d_name);
    printf(" Here 5\n");

    clnt_destroy(clnt);
    return res.res;
}

int mkdir_c(char *ds_svr, char *path, mode_t mode)
{
    mkdir_req req;
    mkdir_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.mode = mode;

    ret = mkdir_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int unlink_c(char *ds_svr, char *path)
{
    unlink_req req;
    unlink_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;

    ret = unlink_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}


int rmdir_c(char *ds_svr, char *path)
{
    rmdir_req req;
    rmdir_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;

    ret = rmdir_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int rename_c(char *ds_svr, char *oldpath, char *newpath)
{
    rename_req req;
    rename_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.old = oldpath;
    req.new = newpath;

    ret = rename_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int mknod_c(char *ds_svr, char *path, mode_t mode, dev_t dev)
{
    mknod_req req;
    mknod_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.mode = mode;
    req.dev = dev;

    ret = mknod_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int create_c(char *ds_svr, char *path, mode_t mode)
{
    create_req req;
    create_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.mode = mode;

    ret = create_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int open_c(char *ds_svr, char *path, int flags, mode_t mode)
{
    open_req req;
    open_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.flags = flags;
    req.mode = mode;

    ret = open_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int close_c(char *ds_svr, char *path)
{
    close_req req;
    close_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;

    ret = close_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int read_c(char *ds_svr, char *path, off_t offset, size_t size, char *buf)
{
    read_req req;
    read_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.offset = offset;
    req.count = size;
#ifdef DEBUG
    printf("read_c: path=%s offset=%lu res.count=%lu size=%lu\n", path,
            (unsigned long)req.offset, (unsigned long)req.count, (unsigned long)size);
#endif
    ret = read_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
        return (-EIO);
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    // individually copy the items
    //
    memcpy(buf, res.data, res.res);
#ifdef DEBUG
    printf("read_c: res.res=%d res.data=%s\n", res.res, res.data);
#endif
    clnt_destroy(clnt);
    return res.res;
}

int write_c(char *ds_svr, char *path, off_t offset, size_t count, char *buf)
{
    write_req req;
    write_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    memcpy(req.data, buf, count); 
    req.offset = offset;
    req.count = count;

    ret = write_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int lookup_c(char *ds_svr, char *path)
{
    lookup_req req;
    lookup_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;

    ret = lookup_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int truncate_c(char *ds_svr, char *path, off_t length)
{
    truncate_req req;
    truncate_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.len = length;

    ret = truncate_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int statfs_c(char *ds_svr, char *path, struct my_statfs *buf)
{
    statfs_req req;
    statfs_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;

    ret = statfs_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    // individually copy the items
    //
    buf->f_type = res.stat.f_type;
    buf->f_bsize = res.stat.f_bsize;
    buf->f_blocks = res.stat.f_blocks;
    buf->f_bfree = res.stat.f_bfree;
    buf->f_bavail = res.stat.f_bavail;
    buf->f_files = res.stat.f_files;
    buf->f_ffree = res.stat.f_ffree;
    buf->f_fsid.__val[0] = res.stat.f_fsid.__val[0];
    buf->f_fsid.__val[1] = res.stat.f_fsid.__val[1];
    buf->f_namelen = res.stat.f_namelen;

    clnt_destroy(clnt);
    return res.res;
}

int chmod_c(char *ds_svr, char *path, mode_t mode)
{
    chmod_req req;
    chmod_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.mode = mode;

    ret = chmod_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int chown_c(char *ds_svr, char *path, uid_t uid, gid_t gid)
{
    chown_req req;
    chown_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.uid = uid;
    req.gid = gid;

    ret = chown_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int link_c(char *ds_svr, char *old, char *new)
{
    link_req req;
    link_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.old = old;
    req.new = new;

    ret = link_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int symlink_c(char *ds_svr, char *old, char * new)
{
    symlink_req req;
    symlink_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.old = old;
    req.new = new;

    ret = symlink_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    clnt_destroy(clnt);
    return res.res;
}

int readlink_c(char *ds_svr, char *path, char *buf, size_t bufsize)
{
    readlink_req req;
    readlink_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
        clnt_pcreateerror(ds_svr);
        return(res.res);
    }

    req.name = path;
    req.bufsize = bufsize;

    ret = readlink_ds_1(&req,&res,clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
    }

    if (res.res  < 0) {
        errno = -(res.res);
        return (res.res);
    }

    /*
     * Copy the result back to the buffer.
     */
    strcpy(buf, res.buf);

    clnt_destroy(clnt);
    return res.res;
}


/*
int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	dsprog_1 (host);
exit (0);
}
*/
