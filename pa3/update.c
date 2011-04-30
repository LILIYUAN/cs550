/*
 * This code is used to update the local obtain_server to similate the
 * modification of a file and hence increment the revision number of the file.
 */
#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "obtain.h"

char localhostname[MAXHOSTNAME + 2];

int
update_file(char *fname)
{
    update_req req;
    update_res res;
    CLIENT *clnt;
    enum clnt_stat ret;

    if ((clnt = clnt_create(localhostname, OBTAINPROG, OBTAINVER, "tcp")) == NULL) {
        clnt_pcreateerror(localhostname);
        return(-1);
    }

    printf("Created the client\n");
    /*
     * Copy the requested filename into the query record.
     */
    req.fname = fname;

    printf("Requesting an update of file(%s) \n", req.fname);
    ret = update_1(&req,&res,clnt);


    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n", ret);
        clnt_perror (clnt, "call failed");
    }

    printf("result = %d\n", res.res);

    clnt_destroy(clnt);

    return(res.res);
}

/*
 * usage
 */
void usage(char *name) {
    printf(" Usage : %s <file-name>\n", name);
    printf(" file-name : name of the file that you want to update\n");
}

int main(int argc, char *argv[])
{
    int result;
    int fopt = 0;
    int opt;

    if (argc != 2) {
        usage(argv[0]);
        return (1);
    }

    if ( gethostname(localhostname, sizeof(localhostname)) != 0) {
        printf("Unable to get the local hostname ! errno = %d\n", errno);
        return (1);
    }

    result = update_file(argv[1]);

    return 0;
}
