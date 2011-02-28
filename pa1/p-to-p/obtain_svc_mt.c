#include "ind.h"
#include "obtain.h"
#include <dirent.h>
#include <errno.h>
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

char dir[MAXPATHLEN];
char *sharedir;

typedef	union argument {
		request obtain_1_arg;
} argument_t ;

typedef union result {
		readfile_res obtain_1_res;
} result_t;

/*
 * Struct to encapsulate the args to the threaded service routine.
 */
typedef struct tdata {
    struct svc_req  *rqstp;
    SVCXPRT         *transp;
    bool_t (*local)(char *, void *, struct svc_req *);
    argument_t      argument;
    result_t        result;
    xdrproc_t       _xdr_argument;
    xdrproc_t       _xdr_result;
} tdata_t;

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
    if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) argument)) {
        fprintf (stderr, "%s", "unable to free arguments");
        exit (1);
    }

    if (!indsrvprog_1_freeresult (transp, _xdr_result, (caddr_t) result))
        fprintf (stderr, "%s", "unable to free results");
    */

    /*
     * Free the data buffer which was allocated by the dispatcher.
     */
    free(data);
    return;
}

pthread_t threadp;
pthread_attr_t attr;

/*
 * Modified dispatch routine. Outline of the code :
 * - This routine is called by svc_run() when a new rpc request arrives.
 * - This routine spawns a new thread for every incoming and hands it (request)
 *   out to that thread to service it.
 */
static void
obtainprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
    tdata_t *datap = (tdata_t *)malloc(sizeof (tdata_t));

#ifdef DEBUG
    printf("obtainprog_1 entered \n");
#endif

    /*
     * If we fail to allocate memory we quit.
     */
    if (datap == NULL) {
        printf("Failed to allocate memory for the request args !\n");
        exit(1);
    }

    datap->rqstp = rqstp;
    datap->transp = transp;

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case obtain:
		datap->_xdr_argument = (xdrproc_t) xdr_request;
		datap->_xdr_result = (xdrproc_t) xdr_readfile_res;
		datap->local = (bool_t (*) (char *, void *,  struct svc_req *))obtain_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&(datap->argument), 0, sizeof (datap->argument));
	if (!svc_getargs (transp, (xdrproc_t) datap-> _xdr_argument, (caddr_t) &(datap->argument))) {
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

/*
 * This routine registers all the files in the directory <dirname>
 * with the index server against the peer.
 */
int
register_files(char *peer, char *index_svr, char *dirname)
{
    CLIENT *clnt;
    DIR *dirp;
    struct dirent *entp;
    registry_rec rec;
    bool_t ret;
    int res;

    if ((dirp = opendir(dirname)) == NULL) {
        printf("opendir(%s) failed with errno %d\n", dirname, errno);
        return (errno);
    }

    if ((clnt = clnt_create(index_svr, INDSRVPROG, INDSRVVERS, "tcp")) == NULL) {
        clnt_pcreateerror(index_svr);
        return(-1);
    }

    while ((entp = readdir(dirp)) != NULL) {
        /*
         * Skip "." and ".."
         */
        if (strcmp(entp->d_name, ".") == 0 || strcmp(entp->d_name, "..") == 0)
            continue;
        printf("Registering file : %s to the index-server : %s\n", entp->d_name, index_svr);

        rec.peer = peer;
        rec.fname = entp->d_name;
        ret = registry_1(&rec, &res, clnt);
        if (res != RPC_SUCCESS) {
            printf("Failed to register : res = %d\n", res);
            return (res);
        }
    }

    closedir(dirp);
    clnt_destroy(clnt);
    return (0);
}

/*
 * usage
 */
void
usage(char *name) {
    printf(" Usage : %s <hostname> <index-server-name> <share-dir>\n\n", name);
    printf(" hostname : Local hostname of the machine\n");
    printf(" index-server-name : Hostname of the index server\n");
    printf(" share-dir : Directory that you would like to share\n");
}


int
main (int argc, char **argv)
{
    char *peer;
    register SVCXPRT *transp;

    if (argc != 4 || strlen(argv[1]) == 0 || strlen(argv[2]) == 0 || strlen(argv[3]) == 0) {
        usage(argv[0]);
        return (1);
    }

    /*
     * Register the files in the given directory with the index-server.
     */
    if (register_files(argv[1], argv[2], argv[3]) != 0) {
        printf("Failed to register with the index server on %s\n", argv[2]);
        printf("Quitting :(\n");
        return (1);
    }

    sharedir = argv[3];

    pmap_unset (OBTAINPROG, OBTAINVER);

    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf (stderr, "%s", "cannot create udp service.");
        exit(1);
    }
    if (!svc_register(transp, OBTAINPROG, OBTAINVER, obtainprog_1, IPPROTO_UDP)) {
        fprintf (stderr, "%s", "unable to register (OBTAINPROG, OBTAINVER, udp).");
        exit(1);
    }

    transp = svctcp_create(RPC_ANYSOCK, 0, 0);
    if (transp == NULL) {
        fprintf (stderr, "%s", "cannot create tcp service.");
        exit(1);
    }
    if (!svc_register(transp, OBTAINPROG, OBTAINVER, obtainprog_1, IPPROTO_TCP)) {
        fprintf (stderr, "%s", "unable to register (OBTAINPROG, OBTAINVER, tcp).");
        exit(1);
    }
    printf("Now ready to serve them\n\n");

    svc_run ();
    fprintf (stderr, "%s", "svc_run returned");
    exit (1);
    /* NOTREACHED */
}
