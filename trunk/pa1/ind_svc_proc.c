#include "ind.h"
#include <rpc/rpc.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SERVER_DIR "/tmp/indsvr/"

/*
 * For now a dummy routine. We may not need to do anything special here.
 */
int indsrvprog_1_freeresult (SVCXPRT *xprt, xdrproc_t xdrp, caddr_t addr)
{
    return (0);
}
/*
 * We use a simple registry for now by using dir/files as our index table.
 * For every file registered we create a file (if it already does not exist).
 * And append the name of the peer-node to that file.
 */
int add_peer (char *fname, char *peername)
{
    FILE *fh;
    char filepath[MAXPATHLEN];
    char peer[MAXNAME+2];
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
    while ((fgets(peer, MAXNAME+2, fh)) != NULL) {
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

int ret;
/*
 * This call registers an entry that the file fname is available on peer.
 */
bool_t registry_1_svc(registry_rec *rec, int *ret, struct svc_req *req)
{
    /*
    if (strlen((const char *)rec->fname) > MAXNAME || strlen((const char *)rec->fname == 0) ||
            strlen(rec->peer) > MAXNAME || strlen(rec->peer) == 0) {
        ret = EINVAL;
        return (&ret);
    }*/
    rec->ret = add_peer(rec->fname, rec->peer);

    *ret = rec->ret;

    return (TRUE);
}

/*
 * This call will search for the filename and find the peers that are serving
 * it.
 */

bool_t search_1_svc(query_rec *rec, query_rec *ret_rec, struct svc_req *req)
{
    FILE *fh;
    int cnt = 0;
    char filepath[MAXPATHLEN];
    char *p;

    sprintf(filepath, "%s/%s", SERVER_DIR, rec->fname);
    fh = fopen(filepath, "r");
    if (fh == NULL) {
        ret_rec->count = 0;
        return (TRUE);
    }

    p = ret_rec->peers;

    while (cnt < rec->count && fgets(p, MAXNAME, fh) != NULL) {
        p[strlen(p) - 1] = '\0';
        p += MAXNAME;
        cnt++;
    }
    /*
     * Pass back the count of peers that are serving this file.
     */
    ret_rec->count = cnt;

    fclose(fh);

    return (TRUE); 
}


