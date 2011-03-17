/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ds.h"
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
	getattr_req  getattr_1_arg;
	enum clnt_stat retval_2;
	readdir_res result_2;
	readdir_req  readdir_1_arg;
	enum clnt_stat retval_3;
	mkdir_res result_3;
	mkdir_req  mkdir_1_arg;
	enum clnt_stat retval_4;
	unlink_res result_4;
	unlink_req  unlink_1_arg;
	enum clnt_stat retval_5;
	rmdir_res result_5;
	rmdir_req  rmdir_1_arg;
	enum clnt_stat retval_6;
	rename_res result_6;
	rename_req  rename_1_arg;
	enum clnt_stat retval_7;
	mknod_res result_7;
	mknod_req  mknod_1_arg;
	enum clnt_stat retval_8;
	create_res result_8;
	create_req  create_1_arg;
	enum clnt_stat retval_9;
	open_res result_9;
	open_req  open_1_arg;
	enum clnt_stat retval_10;
	close_res result_10;
	close_req  close_1_arg;
	enum clnt_stat retval_11;
	read_res result_11;
	read_req  read_1_arg;
	enum clnt_stat retval_12;
	write_res result_12;
	write_req  write_1_arg;
	enum clnt_stat retval_13;
	lookup_res result_13;
	lookup_req  lookup_1_arg;
	enum clnt_stat retval_14;
	truncate_res result_14;
	truncate_req  truncate_1_arg;
	enum clnt_stat retval_15;
	statfs_res result_15;
	statfs_req  statfs_1_arg;
	enum clnt_stat retval_16;
	chmod_res result_16;
	chmod_req  chmod_1_arg;
	enum clnt_stat retval_17;
	chown_res result_17;
	chown_req  chown_1_arg;
	enum clnt_stat retval_18;
	link_res result_18;
	link_req  link_1_arg;
	enum clnt_stat retval_19;
	symlink_res result_19;
	symlink_req  symlink_1_arg;
	enum clnt_stat retval_20;
	readlink_res result_20;
	readlink_req  readlink_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DSPROG, DSVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	retval_1 = getattr_1(&getattr_1_arg, &result_1, clnt);
	if (retval_1 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_2 = readdir_1(&readdir_1_arg, &result_2, clnt);
	if (retval_2 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_3 = mkdir_1(&mkdir_1_arg, &result_3, clnt);
	if (retval_3 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_4 = unlink_1(&unlink_1_arg, &result_4, clnt);
	if (retval_4 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_5 = rmdir_1(&rmdir_1_arg, &result_5, clnt);
	if (retval_5 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_6 = rename_1(&rename_1_arg, &result_6, clnt);
	if (retval_6 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_7 = mknod_1(&mknod_1_arg, &result_7, clnt);
	if (retval_7 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_8 = create_1(&create_1_arg, &result_8, clnt);
	if (retval_8 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_9 = open_1(&open_1_arg, &result_9, clnt);
	if (retval_9 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_10 = close_1(&close_1_arg, &result_10, clnt);
	if (retval_10 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_11 = read_1(&read_1_arg, &result_11, clnt);
	if (retval_11 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_12 = write_1(&write_1_arg, &result_12, clnt);
	if (retval_12 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_13 = lookup_1(&lookup_1_arg, &result_13, clnt);
	if (retval_13 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_14 = truncate_1(&truncate_1_arg, &result_14, clnt);
	if (retval_14 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_15 = statfs_1(&statfs_1_arg, &result_15, clnt);
	if (retval_15 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_16 = chmod_1(&chmod_1_arg, &result_16, clnt);
	if (retval_16 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_17 = chown_1(&chown_1_arg, &result_17, clnt);
	if (retval_17 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_18 = link_1(&link_1_arg, &result_18, clnt);
	if (retval_18 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_19 = symlink_1(&symlink_1_arg, &result_19, clnt);
	if (retval_19 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_20 = readlink_1(&readlink_1_arg, &result_20, clnt);
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

	if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
		clnt_pcreateerror(ds_svr);
		return(-1);
    	}

	req.name = path;

	ret = getattr_1(&req,&res,clnt);

	if (ret != RPC_SUCCESS) {
		printf("ret = %d\n",ret);
		clnt_perror(clnt, "call failed");
	}

	if (res.res  < 0) {
		errno = -(res.res);
		return (-1);
	}

	// individually copy the items
	//*buf = res.sbuf;

	clnt_destroy(clnt);
	return res.res;
}

int readdir_c(char *ds_svr, char *path, int offset, struct dirent *dentry)
{
        readdir_req req;
        readdir_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.d_off = offset;

        ret = readdir_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        // individually copy the items
        //*dentry = res.dent;

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
                return(-1);
        }

        req.name = path;
	req.mode = mode;

        ret = mkdir_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
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
                return(-1);
        }

        req.name = path;

        ret = unlink_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
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
                return(-1);
        }

        req.name = path;

        ret = rmdir_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
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
                return(-1);
        }

        req.old = oldpath;
	req.new = newpath;

        ret = rename_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
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
                return(-1);
        }

        req.name = path;
	req.mode = mode;
	req.dev = dev;

        ret = mknod_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int create_c(char *ds_svr, char *path, mode_t mode, dev_t dev)
{
        create_req req;
        create_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.mode = mode;
	req.dev = dev;

        ret = create_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
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
                return(-1);
        }

        req.name = path;
	req.flags = flags;
	req.mode = mode;

        ret = open_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
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
                return(-1);
        }

        req.name = path;

        ret = close_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int read(char *ds_svr, char *path, int offset, int count, char *buf, int *bytes)
{
        read_req req;
        read_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.offset = offset;
	req.count = count;

        ret = read_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        // individually copy the items
        //*buf = res.data;
	//*bytes = res.bytes;

        clnt_destroy(clnt);
        return res.res;
}

int write(char *ds_svr, char *path, char *data, int offset, int count)
{
        write_req req;
        write_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.data =  data;
	req.offset = offset;
	req.count = count;

        ret = write_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int lookup(char *ds_svr, char *path)
{
        lookup_req req;
        lookup_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;

        ret = lookup_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int truncate(char *ds_svr, char *path, int length)
{
        truncate_req req;
        truncate_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.len = length;

        ret = truncate_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int statfs(char *ds_svr, char *path, struct statfs *buf)
{
        statfs_req req;
        statfs_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;

        ret = statfs_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        // individually copy the items
        *buf = res.stat;

        clnt_destroy(clnt);
        return res.res;
}

int chmod(char *ds_svr, char *path, mode_t mode)
{
        chmod_req req;
        chmod_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;

        ret = chmod_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int chown(char *ds_svr, char *path, uid_t uid, gid_t gid)
{
        chown_req req;
        chown_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.uid = uid;
	req.gid = gid;

        ret = chown_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int link(char *ds_svr, char *old, char *new)
{
        link_req req;
        link_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.old = old;
	req.new = new;

        ret = link_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int symlink(char *ds_svr, char *old, char * new)
{
        symlink_req req;
        symlink_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.old = old;
	req.new = new;

        ret = symlink_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        clnt_destroy(clnt);
        return res.res;
}

int readlink(char *ds_svr, char *path, int bufsize, char *buf)
{
        readlink_req req;
        readlink_res res;
        CLIENT *clnt;
        bool_t ret;

        if ((clnt = clnt_create(ds_svr, DSPROG, DSVERS, "tcp")) == NULL) {
                clnt_pcreateerror(ds_svr);
                return(-1);
        }

        req.name = path;
	req.bugsize = bufsize;

        ret = readlink_1(&req,&res,clnt);

        if (ret != RPC_SUCCESS) {
                printf("ret = %d\n",ret);
                clnt_perror(clnt, "call failed");
        }

        if (res.res  < 0) {
                errno = -(res.res);
                return (-1);
        }

        *buf = res.buf;

        clnt_destroy(clnt);
        return res.res;
}




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
