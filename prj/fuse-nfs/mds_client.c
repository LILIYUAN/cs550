/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "mds.h"
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>


void
mdprog_1(char *host)
{
	CLIENT *clnt;
	enum clnt_stat retval_1;
	getattr_res result_1;
	getattr_req  getattr_mds_1_arg;
	enum clnt_stat retval_2;
	readdir_res result_2;
	readdir_req  readdir_mds_1_arg;
	enum clnt_stat retval_3;
	mkdir_res result_3;
	mkdir_req  mkdir_mds_1_arg;
	enum clnt_stat retval_4;
	unlink_res result_4;
	unlink_req  unlink_mds_1_arg;
	enum clnt_stat retval_5;
	rmdir_res result_5;
	rmdir_req  rmdir_mds_1_arg;
	enum clnt_stat retval_6;
	rename_res result_6;
	rename_req  rename_mds_1_arg;
	enum clnt_stat retval_7;
	mknod_res result_7;
	mknod_req  mknod_mds_1_arg;
	enum clnt_stat retval_8;
	create_res result_8;
	create_req  create_mds_1_arg;
	enum clnt_stat retval_9;
	open_res result_9;
	open_req  open_mds_1_arg;
	enum clnt_stat retval_10;
	close_res result_10;
	close_req  close_mds_1_arg;
	enum clnt_stat retval_11;
	read_res result_11;
	read_req  read_mds_1_arg;
	enum clnt_stat retval_12;
	write_res result_12;
	write_req  write_mds_1_arg;
	enum clnt_stat retval_13;
	lookup_res result_13;
	lookup_req  lookup_mds_1_arg;
	enum clnt_stat retval_14;
	truncate_res result_14;
	truncate_req  truncate_mds_1_arg;
	enum clnt_stat retval_15;
	statfs_res result_15;
	statfs_req  statfs_mds_1_arg;
	enum clnt_stat retval_16;
	chmod_res result_16;
	chmod_req  chmod_mds_1_arg;
	enum clnt_stat retval_17;
	chown_res result_17;
	chown_req  chown_mds_1_arg;
	enum clnt_stat retval_18;
	link_res result_18;
	link_req  link_mds_1_arg;
	enum clnt_stat retval_19;
	symlink_res result_19;
	symlink_req  symlink_mds_1_arg;
	enum clnt_stat retval_20;
	readlink_res result_20;
	readlink_req  readlink_mds_1_arg;
	enum clnt_stat retval_21;
	mount_res result_21;
	mount_req  mount_mds_1_arg;
	enum clnt_stat retval_22;
	getlayout_res result_22;
	getlayout_req  getlayout_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, MDPROG, MDVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	retval_1 = getattr_mds_1(&getattr_mds_1_arg, &result_1, clnt);
	if (retval_1 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_2 = readdir_mds_1(&readdir_mds_1_arg, &result_2, clnt);
	if (retval_2 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_3 = mkdir_mds_1(&mkdir_mds_1_arg, &result_3, clnt);
	if (retval_3 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_4 = unlink_mds_1(&unlink_mds_1_arg, &result_4, clnt);
	if (retval_4 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_5 = rmdir_mds_1(&rmdir_mds_1_arg, &result_5, clnt);
	if (retval_5 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_6 = rename_mds_1(&rename_mds_1_arg, &result_6, clnt);
	if (retval_6 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_7 = mknod_mds_1(&mknod_mds_1_arg, &result_7, clnt);
	if (retval_7 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_8 = create_mds_1(&create_mds_1_arg, &result_8, clnt);
	if (retval_8 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_9 = open_mds_1(&open_mds_1_arg, &result_9, clnt);
	if (retval_9 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_10 = close_mds_1(&close_mds_1_arg, &result_10, clnt);
	if (retval_10 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_11 = read_mds_1(&read_mds_1_arg, &result_11, clnt);
	if (retval_11 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_12 = write_mds_1(&write_mds_1_arg, &result_12, clnt);
	if (retval_12 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_13 = lookup_mds_1(&lookup_mds_1_arg, &result_13, clnt);
	if (retval_13 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_14 = truncate_mds_1(&truncate_mds_1_arg, &result_14, clnt);
	if (retval_14 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_15 = statfs_mds_1(&statfs_mds_1_arg, &result_15, clnt);
	if (retval_15 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_16 = chmod_mds_1(&chmod_mds_1_arg, &result_16, clnt);
	if (retval_16 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_17 = chown_mds_1(&chown_mds_1_arg, &result_17, clnt);
	if (retval_17 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_18 = link_mds_1(&link_mds_1_arg, &result_18, clnt);
	if (retval_18 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_19 = symlink_mds_1(&symlink_mds_1_arg, &result_19, clnt);
	if (retval_19 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_20 = readlink_mds_1(&readlink_mds_1_arg, &result_20, clnt);
	if (retval_20 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_21 = mount_mds_1(&mount_mds_1_arg, &result_21, clnt);
	if (retval_21 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_22 = getlayout_1(&getlayout_1_arg, &result_22, clnt);
	if (retval_22 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int getlayout_c(char *mds_svr, char *fname, off_t off, size_t len, int op, size_t *sz, layout_rec *rec)
{
    getlayout_req req;
    getlayout_res res;
    CLIENT *clnt;
    bool_t ret;

    if ((clnt = clnt_create(mds_svr, MDPROG, MDVERS, "tcp")) == NULL) {
        clnt_pcreateerror(mds_svr);
        return(-EIO);
    }

    req.fname = fname;
    req.offset = off;
    req.len = len;
    req.op = op;

    ret = getlayout_1(&req, &res, clnt);

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n",ret);
        clnt_perror(clnt, "call failed");
        return (-EIO);
    }

    /*
     * TODO :
     * For now we just copy the first extent as that is the one which maps into
     * the range that was asked for.
     *
     * As an optimization we could make pnfs_read() query the entire range that
     * it needs instead of STRIPE_SZ.
     */
    if (res.cnt) {
        rec->off = res.recs[0].off;
        rec->len = res.recs[0].len;
        strcpy(rec->dsname, res.recs[0].dsname);
        strcpy(rec->extname, res.recs[0].extname);
        *sz = res.sz;
    }
    return (0);
}

