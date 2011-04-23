/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "mds_ds.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

static void
mdprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		getattr_req getattr_mds_1_arg;
		readdir_req readdir_mds_1_arg;
		mkdir_req mkdir_mds_1_arg;
		unlink_req unlink_mds_1_arg;
		rmdir_req rmdir_mds_1_arg;
		rename_req rename_mds_1_arg;
		mknod_req mknod_mds_1_arg;
		create_req create_mds_1_arg;
		open_req open_mds_1_arg;
		close_req close_mds_1_arg;
		read_req read_mds_1_arg;
		write_req write_mds_1_arg;
		lookup_req lookup_mds_1_arg;
		truncate_req truncate_mds_1_arg;
		statfs_req statfs_mds_1_arg;
		chmod_req chmod_mds_1_arg;
		chown_req chown_mds_1_arg;
		link_req link_mds_1_arg;
		symlink_req symlink_mds_1_arg;
		readlink_req readlink_mds_1_arg;
		mount_req mount_mds_1_arg;
		getlayout_req getlayout_1_arg;
	} argument;
	union {
		getattr_res getattr_mds_1_res;
		readdir_res readdir_mds_1_res;
		mkdir_res mkdir_mds_1_res;
		unlink_res unlink_mds_1_res;
		rmdir_res rmdir_mds_1_res;
		rename_res rename_mds_1_res;
		mknod_res mknod_mds_1_res;
		create_res create_mds_1_res;
		open_res open_mds_1_res;
		close_res close_mds_1_res;
		read_res read_mds_1_res;
		write_res write_mds_1_res;
		lookup_res lookup_mds_1_res;
		truncate_res truncate_mds_1_res;
		statfs_res statfs_mds_1_res;
		chmod_res chmod_mds_1_res;
		chown_res chown_mds_1_res;
		link_res link_mds_1_res;
		symlink_res symlink_mds_1_res;
		readlink_res readlink_mds_1_res;
		mount_res mount_mds_1_res;
		getlayout_res getlayout_1_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case getattr_mds:
		_xdr_argument = (xdrproc_t) xdr_getattr_req;
		_xdr_result = (xdrproc_t) xdr_getattr_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))getattr_mds_1_svc;
		break;

	case readdir_mds:
		_xdr_argument = (xdrproc_t) xdr_readdir_req;
		_xdr_result = (xdrproc_t) xdr_readdir_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))readdir_mds_1_svc;
		break;

	case mkdir_mds:
		_xdr_argument = (xdrproc_t) xdr_mkdir_req;
		_xdr_result = (xdrproc_t) xdr_mkdir_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))mkdir_mds_1_svc;
		break;

	case unlink_mds:
		_xdr_argument = (xdrproc_t) xdr_unlink_req;
		_xdr_result = (xdrproc_t) xdr_unlink_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))unlink_mds_1_svc;
		break;

	case rmdir_mds:
		_xdr_argument = (xdrproc_t) xdr_rmdir_req;
		_xdr_result = (xdrproc_t) xdr_rmdir_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))rmdir_mds_1_svc;
		break;

	case rename_mds:
		_xdr_argument = (xdrproc_t) xdr_rename_req;
		_xdr_result = (xdrproc_t) xdr_rename_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))rename_mds_1_svc;
		break;

	case mknod_mds:
		_xdr_argument = (xdrproc_t) xdr_mknod_req;
		_xdr_result = (xdrproc_t) xdr_mknod_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))mknod_mds_1_svc;
		break;

	case create_mds:
		_xdr_argument = (xdrproc_t) xdr_create_req;
		_xdr_result = (xdrproc_t) xdr_create_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))create_mds_1_svc;
		break;

	case open_mds:
		_xdr_argument = (xdrproc_t) xdr_open_req;
		_xdr_result = (xdrproc_t) xdr_open_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))open_mds_1_svc;
		break;

	case close_mds:
		_xdr_argument = (xdrproc_t) xdr_close_req;
		_xdr_result = (xdrproc_t) xdr_close_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))close_mds_1_svc;
		break;

	case read_mds:
		_xdr_argument = (xdrproc_t) xdr_read_req;
		_xdr_result = (xdrproc_t) xdr_read_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))read_mds_1_svc;
		break;

	case write_mds:
		_xdr_argument = (xdrproc_t) xdr_write_req;
		_xdr_result = (xdrproc_t) xdr_write_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))write_mds_1_svc;
		break;

	case lookup_mds:
		_xdr_argument = (xdrproc_t) xdr_lookup_req;
		_xdr_result = (xdrproc_t) xdr_lookup_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))lookup_mds_1_svc;
		break;

	case truncate_mds:
		_xdr_argument = (xdrproc_t) xdr_truncate_req;
		_xdr_result = (xdrproc_t) xdr_truncate_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))truncate_mds_1_svc;
		break;

	case statfs_mds:
		_xdr_argument = (xdrproc_t) xdr_statfs_req;
		_xdr_result = (xdrproc_t) xdr_statfs_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))statfs_mds_1_svc;
		break;

	case chmod_mds:
		_xdr_argument = (xdrproc_t) xdr_chmod_req;
		_xdr_result = (xdrproc_t) xdr_chmod_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))chmod_mds_1_svc;
		break;

	case chown_mds:
		_xdr_argument = (xdrproc_t) xdr_chown_req;
		_xdr_result = (xdrproc_t) xdr_chown_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))chown_mds_1_svc;
		break;

	case link_mds:
		_xdr_argument = (xdrproc_t) xdr_link_req;
		_xdr_result = (xdrproc_t) xdr_link_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))link_mds_1_svc;
		break;

	case symlink_mds:
		_xdr_argument = (xdrproc_t) xdr_symlink_req;
		_xdr_result = (xdrproc_t) xdr_symlink_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))symlink_mds_1_svc;
		break;

	case readlink_mds:
		_xdr_argument = (xdrproc_t) xdr_readlink_req;
		_xdr_result = (xdrproc_t) xdr_readlink_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))readlink_mds_1_svc;
		break;

	case mount_mds:
		_xdr_argument = (xdrproc_t) xdr_mount_req;
		_xdr_result = (xdrproc_t) xdr_mount_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))mount_mds_1_svc;
		break;

	case getlayout:
		_xdr_argument = (xdrproc_t) xdr_getlayout_req;
		_xdr_result = (xdrproc_t) xdr_getlayout_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))getlayout_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	if (!mdprog_1_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "unable to free results");

	return;
}

static void
dsprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		getattr_req getattr_ds_1_arg;
		readdir_req readdir_ds_1_arg;
		mkdir_req mkdir_ds_1_arg;
		unlink_req unlink_ds_1_arg;
		rmdir_req rmdir_ds_1_arg;
		rename_req rename_ds_1_arg;
		mknod_req mknod_ds_1_arg;
		create_req create_ds_1_arg;
		open_req open_ds_1_arg;
		close_req close_ds_1_arg;
		read_req read_ds_1_arg;
		write_req write_ds_1_arg;
		lookup_req lookup_ds_1_arg;
		truncate_req truncate_ds_1_arg;
		statfs_req statfs_ds_1_arg;
		chmod_req chmod_ds_1_arg;
		chown_req chown_ds_1_arg;
		link_req link_ds_1_arg;
		symlink_req symlink_ds_1_arg;
		readlink_req readlink_ds_1_arg;
		mount_req mount_ds_1_arg;
	} argument;
	union {
		getattr_res getattr_ds_1_res;
		readdir_res readdir_ds_1_res;
		mkdir_res mkdir_ds_1_res;
		unlink_res unlink_ds_1_res;
		rmdir_res rmdir_ds_1_res;
		rename_res rename_ds_1_res;
		mknod_res mknod_ds_1_res;
		create_res create_ds_1_res;
		open_res open_ds_1_res;
		close_res close_ds_1_res;
		read_res read_ds_1_res;
		write_res write_ds_1_res;
		lookup_res lookup_ds_1_res;
		truncate_res truncate_ds_1_res;
		statfs_res statfs_ds_1_res;
		chmod_res chmod_ds_1_res;
		chown_res chown_ds_1_res;
		link_res link_ds_1_res;
		symlink_res symlink_ds_1_res;
		readlink_res readlink_ds_1_res;
		mount_res mount_ds_1_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case getattr_ds:
		_xdr_argument = (xdrproc_t) xdr_getattr_req;
		_xdr_result = (xdrproc_t) xdr_getattr_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))getattr_ds_1_svc;
		break;

	case readdir_ds:
		_xdr_argument = (xdrproc_t) xdr_readdir_req;
		_xdr_result = (xdrproc_t) xdr_readdir_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))readdir_ds_1_svc;
		break;

	case mkdir_ds:
		_xdr_argument = (xdrproc_t) xdr_mkdir_req;
		_xdr_result = (xdrproc_t) xdr_mkdir_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))mkdir_ds_1_svc;
		break;

	case unlink_ds:
		_xdr_argument = (xdrproc_t) xdr_unlink_req;
		_xdr_result = (xdrproc_t) xdr_unlink_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))unlink_ds_1_svc;
		break;

	case rmdir_ds:
		_xdr_argument = (xdrproc_t) xdr_rmdir_req;
		_xdr_result = (xdrproc_t) xdr_rmdir_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))rmdir_ds_1_svc;
		break;

	case rename_ds:
		_xdr_argument = (xdrproc_t) xdr_rename_req;
		_xdr_result = (xdrproc_t) xdr_rename_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))rename_ds_1_svc;
		break;

	case mknod_ds:
		_xdr_argument = (xdrproc_t) xdr_mknod_req;
		_xdr_result = (xdrproc_t) xdr_mknod_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))mknod_ds_1_svc;
		break;

	case create_ds:
		_xdr_argument = (xdrproc_t) xdr_create_req;
		_xdr_result = (xdrproc_t) xdr_create_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))create_ds_1_svc;
		break;

	case open_ds:
		_xdr_argument = (xdrproc_t) xdr_open_req;
		_xdr_result = (xdrproc_t) xdr_open_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))open_ds_1_svc;
		break;

	case close_ds:
		_xdr_argument = (xdrproc_t) xdr_close_req;
		_xdr_result = (xdrproc_t) xdr_close_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))close_ds_1_svc;
		break;

	case read_ds:
		_xdr_argument = (xdrproc_t) xdr_read_req;
		_xdr_result = (xdrproc_t) xdr_read_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))read_ds_1_svc;
		break;

	case write_ds:
		_xdr_argument = (xdrproc_t) xdr_write_req;
		_xdr_result = (xdrproc_t) xdr_write_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))write_ds_1_svc;
		break;

	case lookup_ds:
		_xdr_argument = (xdrproc_t) xdr_lookup_req;
		_xdr_result = (xdrproc_t) xdr_lookup_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))lookup_ds_1_svc;
		break;

	case truncate_ds:
		_xdr_argument = (xdrproc_t) xdr_truncate_req;
		_xdr_result = (xdrproc_t) xdr_truncate_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))truncate_ds_1_svc;
		break;

	case statfs_ds:
		_xdr_argument = (xdrproc_t) xdr_statfs_req;
		_xdr_result = (xdrproc_t) xdr_statfs_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))statfs_ds_1_svc;
		break;

	case chmod_ds:
		_xdr_argument = (xdrproc_t) xdr_chmod_req;
		_xdr_result = (xdrproc_t) xdr_chmod_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))chmod_ds_1_svc;
		break;

	case chown_ds:
		_xdr_argument = (xdrproc_t) xdr_chown_req;
		_xdr_result = (xdrproc_t) xdr_chown_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))chown_ds_1_svc;
		break;

	case link_ds:
		_xdr_argument = (xdrproc_t) xdr_link_req;
		_xdr_result = (xdrproc_t) xdr_link_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))link_ds_1_svc;
		break;

	case symlink_ds:
		_xdr_argument = (xdrproc_t) xdr_symlink_req;
		_xdr_result = (xdrproc_t) xdr_symlink_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))symlink_ds_1_svc;
		break;

	case readlink_ds:
		_xdr_argument = (xdrproc_t) xdr_readlink_req;
		_xdr_result = (xdrproc_t) xdr_readlink_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))readlink_ds_1_svc;
		break;

	case mount_ds:
		_xdr_argument = (xdrproc_t) xdr_mount_req;
		_xdr_result = (xdrproc_t) xdr_mount_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))mount_ds_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	if (!dsprog_1_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "unable to free results");

	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (MDPROG, MDVERS);
	pmap_unset (DSPROG, DSVERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, MDPROG, MDVERS, mdprog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (MDPROG, MDVERS, udp).");
		exit(1);
	}
	if (!svc_register(transp, DSPROG, DSVERS, dsprog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DSPROG, DSVERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, MDPROG, MDVERS, mdprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (MDPROG, MDVERS, tcp).");
		exit(1);
	}
	if (!svc_register(transp, DSPROG, DSVERS, dsprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DSPROG, DSVERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}