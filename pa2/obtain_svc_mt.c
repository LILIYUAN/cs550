#include "obtain_misc.h"
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
char localhost[MAXHOSTNAME * 2];
char *localhostname = localhost;

peers_t peers;
pending_req_t pending;

extern void *reaper_thread(void *);

typedef	union argument {
		request             obtain_1_arg;
        query_req           search_1_arg;
        b_query_req         b_query_1_arg;
        b_hitquery_reply    b_hitquery_1_arg;
} argument_t ;

typedef union result {
        readfile_res    obtain_1_res;
        query_rec       search_1_res; 
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
#ifdef DEBUG
    printf("Returned from the service routine\n");
#endif

    /*
    if (retval > 0 && tdata_p->rqstp->rq_proc != b_query 
            && tdata_p->rqstp->rq_proc != b_hitquery
            && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)result)) {
        svcerr_systemerr (transp);
    }
    */
    if (retval > 0 && local != (bool_t (*) (char *, void *,  struct svc_req *))b_query_1_svc
            && local != (bool_t (*) (char *, void *,  struct svc_req *))b_hitquery_1_svc
            && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)result)) {
        svcerr_systemerr (transp);
    }

#ifdef DEBUG
    printf("Completed the sending the reply\n");
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

    case search:
        datap->_xdr_argument = (xdrproc_t) xdr_query_req;
        datap->_xdr_result = (xdrproc_t) xdr_query_rec;
        datap->local = (bool_t (*) (char *, void *, struct svc_req *))search_1_svc;
        break;

    case b_query:
        datap->_xdr_argument = (xdrproc_t) xdr_b_query_req;
        datap->_xdr_result = (xdrproc_t) xdr_int;
        datap->local = (bool_t (*) (char *, void *, struct svc_req *))b_query_1_svc;
        break;

    case b_hitquery:
        datap->_xdr_argument = (xdrproc_t) xdr_b_hitquery_reply;
        datap->_xdr_result = (xdrproc_t) xdr_int;
        datap->local = (bool_t (*) (char *, void *, struct svc_req *))b_hitquery_1_svc;
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
 * We use a simple registry for now by using dir/files as our index table.
 * For every file registered we create a file under "/tmp/indsvr/" (if it does
 * not exist already). And append the name of the peer-node to that file.
 */
int add_peer (char *fname, char *peername)
{
    FILE *fh;
    char filepath[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
    int ret, found = 0;
    int fd;
    static init_done = 0;

    /*
     * Create the server index directory for the first time.
     */
    if (init_done == 0) {
        ret = mkdir(SERVER_DIR, 0755);

        /*
         * If we failed to create the index directory and failed for any other
         * reason other than EEXIST we exit.
         */
        if (ret == -1 && errno != EEXIST) {
            char errorstr[512];
            sprintf(errorstr, "Failed to create the index directory : %s", SERVER_DIR);
            perror(errorstr);
        }
        close(ret);
        init_done = 1;
    }


    /*
     * Try to open the name of the file under the index diorectory. If it
     * already exists we open it else we create a new one.
     */
    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fh = fopen(filepath, "a+");
    if (fh == NULL) {
        printf("index-server : Failed to make an entry : errno = %d : %s\n", errno, strerror(errno));
        return (errno);
    }

    fd = fileno(fh);
    /*
     * Lock the file in exclusive mode so that other contending threads don't
     * modify it while we are searching.
     */
    flock(fd, LOCK_EX);

    /*
     * Search through the file to make sure the peer is not already registered.
     * If it is already registered do nothing. Else, append the peers name to
     * the file.
     */
#ifdef DEBUG
    printf("Walking through current entries for %s: ", fname);
#endif

    while ((fgets(peer, MAXHOSTNAME+2, fh)) != NULL) {
        /*
         * Truncate the '\n' from the string.
         */
        peer[strlen(peer) - 1] = '\0';
#ifdef DEBUG
        printf("peer %s strlen = %d\n", peer, strlen(peer));
#endif

        if (strcmp(peer, peername) == 0) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        fprintf(fh, "%s\n", peername);
        printf("Registering file : %s from peer %s\n", fname, peername);
    }

    flock(fd, LOCK_UN);
    fclose(fh);

    return (0);
}

/*
 * This routine registers all the files in the directory <dirname>
 * with the index server against the peer.
 */
int
register_files(char *localhostname, char *dirname)
{
    DIR *dirp;
    struct dirent *entp;
    bool_t ret;
    int res;

    if ((dirp = opendir(dirname)) == NULL) {
        printf("opendir(%s) failed with errno %d\n", dirname, errno);
	printf("Please check if the directory %s exists and is accessible\n",dirname);
        return (errno);
    }

    while ((entp = readdir(dirp)) != NULL) {
        /*
         * Skip "." and ".."
         */
        if (strcmp(entp->d_name, ".") == 0 || strcmp(entp->d_name, "..") == 0)
            continue;
        printf("Registering file : %s to the index-server : %s\n", entp->d_name, localhostname);

        ret = add_peer(entp->d_name, localhostname);
    }

    closedir(dirp);
    return (0);
}

int
parse_peers(char *peerfile)
{
	FILE *fh;
	char tmp[MAXHOSTNAME+2];
	peers.count = 0;

	/*
	 * Build the peerlist structure.
	 */
	fh = fopen(peerfile, "r");
	if (fh == NULL) {
		printf("Failed to open the peerlist file : %s\n", peerfile);
		return (1);
	}

	peers.count = 0;
	while ((fgets(tmp, MAXHOSTNAME+2, fh)) != NULL) {
        /*
         * Truncate the '\n' from the string.
         */
        tmp[strlen(tmp) - 1] = '\0';
		peers.peer[peers.count] = malloc(MAXHOSTNAME+2 * sizeof(char));	
		if (peers.peer == NULL) {
				printf("Failed to allocate memory. Quitting !\n");
				fclose(fh);
				return (1);
		}
		strcpy(peers.peer[peers.count], tmp);
        peers.clnt[peers.count] = NULL;
#ifdef DEBUG
        printf("%s : strlen = %d\n", peers.peer[peers.count], strlen(peers.peer[peers.count]));
#endif
		peers.count++;
 	}

	fclose(fh);
	return (0);
}

/*
 * usage
 */
void
usage(char *name) {
    printf(" Usage : %s <peer-list-file> <share-dir>\n\n", name);
    printf(" peer-list-file : file containing the Hostnames of the peers\n");
    printf(" share-dir : Directory that you would like to share\n\n");
}

extern char *optarg;
extern int optind;

int
main (int argc, char **argv)
{
    char *peerfile;
    register SVCXPRT *transp;
	FILE *fd;
	int i, ret;
	char tmp[MAXHOSTNAME+2];
    pthread_t reaper;
	

    if (argc != 3) {
        usage(argv[0]);
        return (1);
    }

	if ( gethostname(localhostname, sizeof(localhost)) != 0) {
        printf("Unable to get the local hostname ! errno = %d\n", errno);
        return (1);
    }

	peerfile = argv[1];
	sharedir = argv[2];

    if (strlen(peerfile) == 0 || strlen(sharedir) == 0) {
        usage(argv[0]);
        return (1);
    }

#ifdef DEBUG
    printf("localhostname : %s\n", localhostname);
#endif

	if (parse_peers(peerfile) != 0) {
		printf("Failed to parse the peers file. Quitting !\n");
		return (1);
	}

    /*
     * Initialize the pending queue mutex.
     */
    pthread_mutex_init(&(pending.lock), NULL);

    /*
     * Create the reaper_thread.
     */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&reaper, &attr, reaper_thread, NULL);

    /*
     * Register the files in the given directory with the index-server.
     */
    if (register_files(localhostname, sharedir) != 0) {
        printf("Failed to register with the index server on %s\n", argv[2]);
        printf("Quitting :(\n");
        return (1);
    }


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
