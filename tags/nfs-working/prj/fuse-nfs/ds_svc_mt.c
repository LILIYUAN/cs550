/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ds_misc.h"
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

typedef	union argument {
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
} argument_t;

typedef	union result {
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
} result_t;

/*
 *  * Struct to encapsulate the args to the threaded service routine.
 *   */
typedef struct tdata {
    struct svc_req  *rqstp;
    SVCXPRT         *transp;
    bool_t (*local)(char *, void *, struct svc_req *);
    argument_t      argument;
    result_t        result;
    xdrproc_t       _xdr_argument;
    xdrproc_t       _xdr_result;
} tdata_t;

mds_t   mds;
ds_t    ds;

/*
 * Modified service routine. This is the routine executed by the service threads
 * spawned by the dispatcher routine.
 * Logic outline :
 * - It extracts the args from the void poineter passed to it.
 * - It called the necessary server method and replies to the client with the
 *   results.
 */
void *
service_request(void *data )
{
    tdata_t *tdata_p;
    argument_t *argument;
    result_t *result;
    bool_t retval;
    xdrproc_t _xdr_argument, _xdr_result;
    bool_t (*local)(char *, void *, struct svc_req *);
    struct svc_req *rqstp;
    register SVCXPRT *transp;

#ifdef DEBUG
    printf("service_request() : Entered\n");
#endif

    /*
     * Extract the args from the argument passed.
     */
    tdata_p = (tdata_t *) data;
    rqstp = tdata_p->rqstp;
    transp = tdata_p->transp;
    local = tdata_p->local;
    argument = &(tdata_p->argument);
    result = &(tdata_p->result);
    _xdr_result = tdata_p->_xdr_result;

#ifdef DEBUG
    printf("rq_proc = %d\n", (int)rqstp->rq_proc);
    printf("Calling the service routine\n");
#endif

    retval = (bool_t) (*local)((char *)argument, (void *)result, rqstp);
    if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)result)) {
        svcerr_systemerr (transp);
    }
#ifdef DEBUG
    printf("Completed the service routine\n");
#endif

    /*
     * Free the data buffer which was allocated by the dispatcher.
     */
    free(data);
    return;
}


pthread_t threadp;
pthread_attr_t attr;

static void
dsprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
    tdata_t *datap = (tdata_t *)malloc(sizeof (tdata_t));

    /*
     * If we fail to allocate memory we quit.
     */
    if (datap == NULL) {
        printf("Failed to allocate memory for the request args !\n");
        exit(1);
    }

    datap->rqstp = rqstp;
    datap->transp = transp;

#ifdef DEBUG
    printf("dsprog_1 : Got a call for rq_proc = %d\n", (int)rqstp->rq_proc);
#endif
	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case getattr_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_getattr_req;
		datap->_xdr_result = (xdrproc_t) xdr_getattr_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))getattr_ds_1_svc;
		break;

	case readdir_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_readdir_req;
		datap->_xdr_result = (xdrproc_t) xdr_readdir_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))readdir_ds_1_svc;
		break;

	case mkdir_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_mkdir_req;
		datap->_xdr_result = (xdrproc_t) xdr_mkdir_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))mkdir_ds_1_svc;
		break;

	case unlink_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_unlink_req;
		datap->_xdr_result = (xdrproc_t) xdr_unlink_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))unlink_ds_1_svc;
		break;

	case rmdir_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_rmdir_req;
		datap->_xdr_result = (xdrproc_t) xdr_rmdir_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))rmdir_ds_1_svc;
		break;

	case rename_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_rename_req;
		datap->_xdr_result = (xdrproc_t) xdr_rename_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))rename_ds_1_svc;
		break;

	case mknod_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_mknod_req;
		datap->_xdr_result = (xdrproc_t) xdr_mknod_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))mknod_ds_1_svc;
		break;

	case create_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_create_req;
		datap->_xdr_result = (xdrproc_t) xdr_create_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))create_ds_1_svc;
		break;

	case open_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_open_req;
		datap->_xdr_result = (xdrproc_t) xdr_open_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))open_ds_1_svc;
		break;

	case close_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_close_req;
		datap->_xdr_result = (xdrproc_t) xdr_close_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))close_ds_1_svc;
		break;

	case read_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_read_req;
		datap->_xdr_result = (xdrproc_t) xdr_read_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))read_ds_1_svc;
		break;

	case write_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_write_req;
		datap->_xdr_result = (xdrproc_t) xdr_write_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))write_ds_1_svc;
		break;

	case lookup_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_lookup_req;
		datap->_xdr_result = (xdrproc_t) xdr_lookup_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))lookup_ds_1_svc;
		break;

	case truncate_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_truncate_req;
		datap->_xdr_result = (xdrproc_t) xdr_truncate_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))truncate_ds_1_svc;
		break;

	case statfs_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_statfs_req;
		datap->_xdr_result = (xdrproc_t) xdr_statfs_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))statfs_ds_1_svc;
		break;

	case chmod_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_chmod_req;
		datap->_xdr_result = (xdrproc_t) xdr_chmod_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))chmod_ds_1_svc;
		break;

	case chown_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_chown_req;
		datap->_xdr_result = (xdrproc_t) xdr_chown_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))chown_ds_1_svc;
		break;

	case link_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_link_req;
		datap->_xdr_result = (xdrproc_t) xdr_link_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))link_ds_1_svc;
		break;

	case symlink_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_symlink_req;
		datap->_xdr_result = (xdrproc_t) xdr_symlink_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))symlink_ds_1_svc;
		break;

	case readlink_ds:
		datap->_xdr_argument = (xdrproc_t) xdr_readlink_req;
		datap->_xdr_result = (xdrproc_t) xdr_readlink_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))readlink_ds_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&datap->argument, 0, sizeof (datap->argument));
	if (!svc_getargs (transp, (xdrproc_t) datap->_xdr_argument, (caddr_t) &(datap->argument))) {
		svcerr_decode (transp);
		return;
	}

    /*
     * We want the service threads to be reaped automatically.
     */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /*
     * Spawn a new thread and pass it the rpc request for it to process it.
     */
#ifdef DEBUG
    printf("Spawning a new thread\n");
#endif
    pthread_create(&threadp, &attr, service_request, (void *)datap);
#ifdef DEBUG
    printf("Spawned a new thread\n");
#endif

	return;
}

int
init_ds(char *dir, char *mds_name, fsid_t fsid)
{
    struct stat sbuf;
    int ret;

    strcpy(ds.md_server, mds_name);
    strcpy(ds.dir, dir);
    ds.fsid = fsid;
    strcpy(mds.md_server, mds_name);
    strcpy(mds.dir, dir);

    ret = stat(dir, &sbuf);

    if (ret != 0) {
        printf("Cannot stat the directory %s errno : %d\n", dir, errno);
        return (errno);
    }

    if (!S_ISDIR(sbuf.st_mode)) {
        printf("%s is not a directory\n", dir);
        return (ENOTDIR);
    }

    return (0);
}

void
usage(char *exec)
{
    printf("Usage: %s -d <share-dir> -s <mds-server> -i fsid\n", exec);
    printf(" <share-dir>    : The directory that is being shared\n");
    printf(" <mds-server>   : The name of the mds-server for this filesystem\n");
    printf(" <fsid>         : The fsid of the filesystem being served (provided by mds-server for this filesystem\n");
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;
    char *dir, *mds;
    fsid_t fsid;

    if (argc != 7) {
        usage(argv[0]);
        return (1);
    }

    /*
     * TODO :
     * write getopt code to fetch the opts.
     */
    dir = argv[2];
    mds = argv[4];
    fsid.__val[0] = atoi(argv[6]);
    if (init_ds(dir, mds, fsid) != 0) {
        return (1);
    }

	pmap_unset (DSPROG, DSVERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
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
	if (!svc_register(transp, DSPROG, DSVERS, dsprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DSPROG, DSVERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
