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
    int fd;
    char filepath[MAXPATHLEN];
    char peer[MAXNAME+2];
    int ret;

    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fd = open(filepath, O_CREAT|O_APPEND);
    if (fd < 0) {
        printf("Failed to make an entry : errno = %d : %s\n", errno, strerror(errno));
        return (errno);
    }

    strncpy(peer, peername, MAXNAME);
    peer[MAXNAME] = '\0';
    peer[MAXNAME+1] = '\n';

    printf("file = %s peer = %s\n", fname, peer);

    ret = write(fd, peer, MAXNAME+2);

    printf("write() ret = %d : %s\n", ret, strerror(ret));
    close(fd);
    return (0);
}

int ret;
/*
 * This call registers an entry that the file fname is available on peer.
 */
int * registry_1_svc(registry_rec *rec, struct svc_req *req)
{
    /*
    if (strlen((const char *)rec->fname) > MAXNAME || strlen((const char *)rec->fname == 0) ||
            strlen(rec->peer) > MAXNAME || strlen(rec->peer) == 0) {
        ret = EINVAL;
        return (&ret);
    }*/
    ret = add_peer(rec->fname, rec->peer);
    return(&ret);
}

