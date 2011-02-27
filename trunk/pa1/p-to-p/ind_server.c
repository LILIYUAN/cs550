#include "ind.h"
#include "obtain.h"
#include <stdio.h>
#include <errno.h>
#include <rpc/rpc.h>
#include <sys/file.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define SERVER_DIR "/tmp/indsvr/"

/* #define DEBUG 1 */

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
        printf("%s : strlen = %d\n", peer, strlen(peer));

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

bool_t
registry_1_svc(registry_rec *argp, int *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;

    *result = add_peer(argp->fname, argp->peer);
#ifdef SLEEP
    printf("Sleeping for 5 secs\n");
    sleep(5);
    printf("Woke up after sleeping for 5 secs\n");
#endif /* SLEEP */

	return retval;
}

bool_t
search_1_svc(query_req *argp, query_rec *result, struct svc_req *rqstp)
{
    FILE *fh;
    int cnt = 0;
    char filepath[MAXPATHLEN];
    char *p;
    int fd;

    sprintf(filepath, "%s/%s", SERVER_DIR, argp->fname);
    fh = fopen(filepath, "r");
    if (fh == NULL) {
        result->count = 0;
        return (TRUE);
    }

    /*
     * If we have reached here there is possibly a peer which is serving this
     * file.
     */
    fd = fileno(fh);

    strcpy(result->fname, argp->fname);

    /*
     * Obtain a shared lock on the file while we are reading the contents.
     * This would block any modifications to the file while we are searching.
     * However, other searches can continue to access it.
     */
    flock(fd, LOCK_SH);

    p = result->peers;

    while (cnt < argp->count && fgets(p, MAXHOSTNAME + 2, fh) != NULL) {
        p[strlen(p) - 1] = '\0';
        p += MAXHOSTNAME;
        cnt++;
    }
    /*
     * Pass back the count of peers that are serving this file.
     */
    result->count = cnt;

    flock(fd, LOCK_UN);
    fclose(fh);

#ifdef DEBUG
    {
        int i;
        printf("Peers serving %s = %d \n", argp->fname, result->count);
        printf("peers %s\n", result->peers);
        for (i = 0; i < result->count; i++) {
            printf("hostname : %s\n", result->peers+(i * MAXHOSTNAME));
        }
    }
#endif /* DEBUG */

	return (TRUE);
}

int
indsrvprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	return 1;
}
