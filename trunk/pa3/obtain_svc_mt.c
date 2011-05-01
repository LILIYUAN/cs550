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
char localhost[MAXHOSTNAME + 2];
char *localhostname = localhost;

peers_t peers;
pending_req_t qpending;
pending_req_t ipending;
int push;
int pull;
int ttrtime;

extern void *reaper_thread(void *);
extern void *validate_thread(void *);

typedef	union argument {
		request             obtain_1_arg;
        query_req           search_1_arg;
        addcache_req        addcache_1_req;
        b_query_req         b_query_1_arg;
        b_hitquery_reply    b_hitquery_1_arg;
        invalidate_req      invalidate_1_arg;
        update_req 	    update_1_arg;
        validate_req validate_1_arg;
} argument_t ;

typedef union result {
        readfile_res    obtain_1_res;
        query_rec       search_1_res; 
        addcache_res    addcache_1_res;
        update_res      update_1_res;
        validate_res    validate_1_res;
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
    printf("Calling the service routine : rq_proc = %d\n", (int)rqstp->rq_proc);
#endif

    retval = (bool_t) (*local)((char *)argument, (void *)result, rqstp);
#ifdef DEBUG
    printf("Returned from the service routine : rq_proc = %d\n", (int)rqstp->rq_proc);
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

#ifdef DEBUG
    printf("obtainprog_1: service routine : rq_proc = %d\n", (int)rqstp->rq_proc);
#endif
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
 
    case addcache:
        datap->_xdr_argument = (xdrproc_t) xdr_addcache_req;
        datap->_xdr_result = (xdrproc_t) xdr_addcache_res;
        datap->local = (bool_t (*) (char *, void *,  struct svc_req *))addcache_1_svc;
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

    case invalidate:
        datap->_xdr_argument = (xdrproc_t) xdr_invalidate_req;
        datap->_xdr_result = (xdrproc_t) xdr_void;
        datap->local = (bool_t (*) (char *, void *,  struct svc_req *))invalidate_1_svc;
        break;

    case update:
         datap->_xdr_argument = (xdrproc_t) xdr_update_req;
         datap->_xdr_result = (xdrproc_t) xdr_update_res;
         datap->local = (bool_t (*) (char *, void *,  struct svc_req *))update_1_svc;
         break;

    case validate:
        datap->_xdr_argument = (xdrproc_t) xdr_validate_req;
        datap->_xdr_result = (xdrproc_t) xdr_validate_res;
        datap->local = (bool_t (*) (char *, void *,  struct svc_req *))validate_1_svc;
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
int add_peer (char *fname, char *peername, int primary_flag, int newrev, my_time_t ttr)
{
    FILE *fh;
    char filepath[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
    int ret, found = 0;
    int fd;
    int oldrev, oldpflag;
    my_time_t   oldttr;
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

    while (!feof(fh)) {
        fscanf(fh, IND_REC_FMT, &oldrev, &oldpflag, &oldttr, peer);
#ifdef DEBUG
        printf("rev=%d pflag=%d peer=%s\n", oldrev, oldpflag, peer);
#endif

        if (strcmp(peer, peername) == 0) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        fprintf(fh, IND_REC_FMT, newrev, primary_flag, ttr, peername);
        printf("Registering file : %s from peer %s newrev=%d primary_flag=%d ttr=%lu\n",
                fname, peername, newrev, primary_flag, ttr);
    }

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);

    return (0);
}

/*
 * Searches in the fname for a record against <peername> and updates it.
 *
 * If newrev is -1 :
 *  - Increment the current rev by 1 and write it back.
 *
 * Return value :
 * 0 - If could not find a record
 * 1 - If it successfully updates the record.
 */
int
update_rec(char *fname, char *peername, int newpflag, int newrev, my_time_t newttr)
{
    FILE *fh;
    char filepath[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
    int ret, found = 0;
    int fd;
    int oldrev, oldpflag;
    my_time_t   oldttr;
    long pos = 0;

    /*
     * Try to open the name of the file under the index directory. If it
     * already exists we open it else we create a new one.
     */
    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fh = fopen(filepath, "r+");
    if (fh == NULL) {
        printf("index-server : Failed to make an entry : errno = %d : %s\n", errno, strerror(errno));
        return (-errno);
    }

    fd = fileno(fh);
    /*
     * Lock the file in exclusive mode so that other contending threads don't
     * modify it while we are searching.
     */
    flock(fd, LOCK_EX);

    /*
     * Search through the file to search for the entry and update it else
     * add the new entry.
     */
#ifdef DEBUG
    printf("update_rec: Walking through current entries for %s: ", fname);
#endif

    while (!feof(fh)) {
        pos = ftell(fh);
        fscanf(fh, IND_REC_FMT, &oldrev, &oldpflag, &oldttr, peer);
#ifdef DEBUG
        printf("rev=%d pflag=%d peer=%s\n", oldrev, oldpflag, peer);
#endif

        if (strcmp(peer, peername) == 0) {
            found = 1;

            /*
             * Check if this is a request to update the rev.
             */
            if (newrev == -1) {
                newrev = oldrev + 1;
            }

            /*
             * We use the same oldttr if newttr is -1.
             */
            if (newttr == -1) {
                newttr = oldttr;
            }

            fseek(fh, SEEK_SET, pos);
            fprintf(fh, IND_REC_FMT, newrev, newpflag, newttr, peer);
            break;
        }
    }

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);

    return (newrev);
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

        ret = add_peer(entp->d_name, localhostname, PRIMARY, 0, ttrtime);
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
    printf(" Usage : %s [-u] [-l <ttrtime>] <peer-list-file> <share-dir>\n\n", name);
    printf(" -u : push the updates to peers\n");
    printf(" -l <ttrtime> : pull the updates from peers. ttrtime is the time-to-refresh in secs\n");
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
    pthread_t ireaper;
    pthread_t qreaper;
    pthread_t validate_thr;
    int opt;
	

    if (argc < 3 || argc > 5) {
        usage(argv[0]);
        return (1);
    }

    while ((opt = getopt(argc, argv, "ul:")) != -1) {
        switch (opt) {
            case 'u':
                push = 1;
                break;
            case 'l':
                pull = 1;
                ttrtime = atoi(optarg);
                printf("ttrtime = %d\n", ttrtime);
                break;
            default:
                usage(argv[0]);
                return (1);
        }
    }

	if ( gethostname(localhostname, sizeof(localhost)) != 0) {
        printf("Unable to get the local hostname ! errno = %d\n", errno);
        return (1);
    }

	peerfile = argv[optind];
	sharedir = argv[optind + 1];
    printf("peerfile %s sharedir %s\n", peerfile, sharedir);

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
    pthread_mutex_init(&(qpending.lock), NULL);
    pthread_mutex_init(&(ipending.lock), NULL);

    /*
     * Create the reaper_threads for ipending and qpending lists.
     */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&qreaper, &attr, reaper_thread, (void *)&qpending);
    pthread_create(&ireaper, &attr, reaper_thread, (void *)&ipending);

    if (pull) {
        pthread_create(&validate_thr, &attr, validate_thread, (void *)&ipending);
    }

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
