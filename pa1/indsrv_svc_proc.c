#include <rpc/rpc.h>
#include <errno.h>
#include "ind.h"

#define SERVER_DIR "/tmp/indsvr/"

/*
 * We use a simple registry for now by using dir/files as our index table.
 * For every file registered we create a file (if it already does not exist).
 * And append the name of the peer-node to that file.
 */
int register(char *fname, char *peername)
{
    int fd;
    char filepath[MAXPATH];
    char peer[MAXNAME+2];

    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fd = open(filepath, O_CREATE|O_APPEND);
    if (fd < 0) {
        printf("Failed to make an entry : errno = %d\n", errno);
        return (errno);
    }

    strncpy(peer, peername, MAXNAME);
    peer[MAXNAME] = '\n';
    peer[MAXNAME] = '\0';
    write(fd, peername, strlen(peer)+1);
    close(fd);
    return (0);
}

int ret;
/*
 * This call registers an entry that the file fname is available on peer.
 */
int * registry_1(registry_rec *rec)
{
    /*
    if (strlen((const char *)rec->fname) > MAXNAME || strlen((const char *)rec->fname == 0) ||
            strlen(rec->peer) > MAXNAME || strlen(rec->peer) == 0) {
        ret = EINVAL;
        return (&ret);
    }*/
    ret = register(rec->fname, rec->peer);
    return(&ret);
}

