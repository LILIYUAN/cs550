#include "ind.h"
#include <rpc/rpc.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_DIR "/tmp/indsvr/"

/*
 * We use a simple registry for now by using dir/files as our index table.
 * For every file registered we create a file (if it already does not exist).
 * And append the name of the peer-node to that file.
 */
int add_peer (char *fname, char *peername)
{
    FILE *fh;
    char filepath[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
    int ret, found = 0;

    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fh = fopen(filepath, "a+");
    if (fh == NULL) {
        printf("Failed to make an entry : errno = %d : %s\n", errno, strerror(errno));
        return (errno);
    }

    /*
     * Search through the file to make sure the peer is not already registered.
     */
    printf("Walking through current entries for %s: ", fname);
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
        printf("Registering file : %s peer %s\n", fname, peername);
    }
    fclose(fh);

    return (0);
}

bool_t
registry_1_svc(registry_rec *argp, int *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;

    *result = add_peer(argp->fname, argp->peer);

	return retval;
}

bool_t
search_1_svc(query_req *argp, query_rec *result, struct svc_req *rqstp)
{
    FILE *fh;
    int cnt = 0;
    char filepath[MAXPATHLEN];
    char *p;

    sprintf(filepath, "%s/%s", SERVER_DIR, argp->fname);
    fh = fopen(filepath, "r");
    if (fh == NULL) {
        result->count = 0;
        return (TRUE);
    }

    strcpy(result->fname, argp->fname);

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

    fclose(fh);

    {
        int i;
        printf("Peers serving %s = %d \n", argp->fname, result->count);
        printf("peers %s\n", result->peers);
        for (i = 0; i < result->count; i++) {
            printf("hostname : %s\n", result->peers+(i * MAXHOSTNAME));
        }
    }

	return (TRUE);
}

int
indsrvprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	return 1;
}
