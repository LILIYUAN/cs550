#include "ind.h"
#include <dirent.h>
#include <rpc/rpc.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SERVER_DIR "/tmp/indsvr/"

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
    int *ret;

    if ((dirp = opendir(dirname)) == NULL) {
        printf("opendir(%s) failed with errno %d\n", dirname, errno);
        return (errno);
    }

    if ((clnt = clnt_create(index_svr, INDSRVPROG, INDSRVVERS, "tcp")) == NULL) {
        clnt_pcreateerror(index_svr);
        return(-1);
    }

    while ((entp = readdir(dirp)) != NULL) {
        printf("registering file : %s\n", entp->d_name);

        /*
         * Skip "." and ".."
         */
        if (strcmp(entp->d_name, ".") == 0 || strcmp(entp->d_name, "..") == 0)
            continue;
        rec.peer = peer;
        rec.fname = entp->d_name;
        ret = registry_1(&rec, clnt);
        if (*ret != 0) {
            printf("Failed to register : ret = %d\n", *ret);
            return (*ret);
        }
    }

    closedir(dirp);
    return (0);
}

/*
 * usage
 */
void
usage(char *name)
{
    printf("Usage : %s <peername> <index-server-name> <share-dir>\n", name);
    printf("\tpeername - Local Hostname of the peer machine which is running this server\n");
    printf("\tinder-server-name - Hostname of the index server\n");
    printf("\tshare-dir - Directory that you would like to share\n");
}

int
main(int argc, char *argv[])
{
    char *dirp;
    char *peer;

    if (argc != 4 || strlen(argv[1]) == 0 || strlen(argv[2]) == 0 || strlen(argv[3]) == 0) {
        usage(argv[0]);
        return (1);
    }

    /*
     * Register the files in the given directory with the index-server.
     */
    register_files(argv[1], argv[2], argv[3]);
    return (0);
}
