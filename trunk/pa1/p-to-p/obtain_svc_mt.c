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

static void
obtainprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		request obtain_1_arg;
	} argument;
	union {
		readfile_res obtain_1_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

    printf("obtainprog_1 entered \n");

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case obtain:
		_xdr_argument = (xdrproc_t) xdr_request;
		_xdr_result = (xdrproc_t) xdr_readfile_res;
		local = (bool_t (*) (char *, void *,  struct svc_req *))obtain_1_svc;
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
    printf("Calling service routine \n");
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
    printf("service routine  completed\n");
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	if (!obtainprog_1_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "unable to free results");

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
        printf("registering file : %s\n", entp->d_name);

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
    printf("Usage : %s <peername> <index-server-name> <share-dir>\n", name);
    printf(" hostname : Local Hostname of the peer machine which is running this server\n");
    printf(" inder-server-name : Hostname of the index server\n");
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
    register_files(argv[1], argv[2], argv[3]);
    printf("Registered files\n");

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
    printf("Now ready to serve them\n");

    svc_run ();
    fprintf (stderr, "%s", "svc_run returned");
    exit (1);
    /* NOTREACHED */
}
