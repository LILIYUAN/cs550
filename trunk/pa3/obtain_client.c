/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */
#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "obtain.h"

char localhostname[MAXHOSTNAME + 2];

/*
 * This routine queries the index-server to find the list of peers serving the
 * file rec->fname.
 */
int query_and_fetch(char *fname, char *index_svr, char *dest_dir, int fopt)
{
    query_req req;
    query_rec res_rec;
    CLIENT *clnt;
    bool_t ret;
    int res, i, attempts;
    time_t start_time, end_time;
    addcache_req ac_req;
    addcache_res ac_res;

    if ((clnt = clnt_create(index_svr, OBTAINPROG, OBTAINVER, "tcp")) == NULL) {
        clnt_pcreateerror(index_svr);
        return(-1);
    }

    printf("Created the client\n");
    /*
     * Copy the requested filename into the query record.
     */
    req.fname = fname;
    req.count = MAXCOUNT;

    printf("searching(%s) \n", req.fname);
    time(&start_time);
    ret = search_1(&req,&res_rec,clnt);
    time(&end_time);

    printf("Time taken by index server = %ld secs\n", (long) difftime(end_time, start_time));

    if (ret != RPC_SUCCESS) {
        printf("ret = %d\n", ret);
        clnt_perror (clnt, "call failed");
    }

    if (res_rec.count == 0) {
        printf("Failed to find any peers serving file : %s\n", req.fname);
        return (-1);
    }

    /*
     * Continue until the user enters a valid choice.
     */
    printf("Total number of peers serving %s = %d\n", res_rec.fname, res_rec.count);
    printf("Peers serving the file are :\n");
    for (i = 0; i < res_rec.count; i++) {
        printf("\t%d : %s\n", i, res_rec.recs[i].hostname);
    }

    if (fopt == 0) {
        printf("Pick the peer from which you want to fetch from : ");
        scanf("%d", &i);
        while (i < 0 || i >= res_rec.count) {
            printf("Pick a valid peer number : ");
            scanf("%d", &i);
        }
    } else {
        i = 0;
    }


    /*
     * We try to fetch the file untill we succeed or have tried all the servers.
     */
    attempts = 0;
    time(&start_time);
    while (get_file(res_rec.recs[i].hostname, fname, dest_dir) != 0 &&
        attempts < res_rec.count) {

        printf("Failed to fetch the file from host:%s\nTrying next server\n",
                res_rec.recs[i].hostname);

        i = (i + 1) % res_rec.count;
        attempts++;
        time(&start_time);
    }
    time(&end_time);

    if (attempts == res_rec.count) {
        printf("Failed to fetch the file from any of the listed peers\n");
    } else {
        printf("Time taken to fetch the file = %ld secs\n", (long) difftime(end_time, start_time));


        // build the addcache_req object
        ac_req.fname = fname;
        ac_req.ver = res_rec.recs[i].rev;
        ac_req.path = dest_dir;
        ac_req.ttr = res_rec.recs[i].ttr;

        // make the RPC call
        addcache_1(&ac_req,&ac_res,clnt);
        if (ret != RPC_SUCCESS) {
            printf("ret = %d\n", ret);
            clnt_perror (clnt, "addcache_1 failed");
        }

    }

    clnt_destroy(clnt);

    return (0);
}

/*
 * This routine fetches the file *name from the host *host and copies it to
 * directory *dest_dir.
 *
 * Return values :
 * 0 : On success
 * 1 : Failure
 */
int get_file(char *host, char *name, char *dest_dir)
{
    CLIENT *clnt;
    int total_bytes = 0, write_bytes;
    readfile_res result;
    request req;
    FILE *file;
    int ret = 1;
    char filepath[MAXPATHLEN];
    req.name = name;
    req.seek_bytes = 0;

#ifdef DEBUG
    printf("host : %s name : %s\n", host, name);
#endif
    /*
     * Create client handle used for calling FTPPROG on
     * the server designated on the command line. Use
     * the tcp protocol when contacting the server.
     */
    clnt = clnt_create(host, OBTAINPROG, OBTAINVER, "tcp");
    if (clnt == NULL) {
        /*
         * establish connection failed with the server.
         */
        clnt_pcreateerror(host);
        return (1);
    }

    sprintf(filepath, "%s/%s", dest_dir, name);
    file = fopen(filepath, "wb");

    /*
     * Call the remote procedure readdir on the server
     */
    while (1) {
        req.seek_bytes = total_bytes;
        ret = obtain_1(&req,&result,clnt);
        if (ret != RPC_SUCCESS) {
            /*
             * An RPC error occurred while calling the server.
             * Print error message and stop.
             */
            clnt_perror(clnt, host);
            clnt_destroy(clnt);
            return (1);
        }

        /*
         * Okay, we successfully called the remote procedure.
         */
        if (result.error != 0) {
            /*
             * A remote system error occurred.
             * Print error message and stop.
             */
            errno = result.error;
            perror(name);
            clnt_destroy(clnt);
            return (1);
        }

        /*
         * Successfully got a chunk of the file.
         * Write into our local file.
         */

        //printf("\n read %d \t %s", result.readfile_res_u.chunk.bytes,result.readfile_res_u.chunk.data);
        write_bytes = fwrite(result.readfile_res_u.chunk.data, 1, result.readfile_res_u.chunk.bytes, file);

        //printf("\n  write %d \t %s", result.readfile_res_u.chunk.bytes, result.readfile_res_u.chunk.data);


        // lets print the total number of bytes read and written in each cycle
#ifdef DEBUG
        printf(" \n read %d written %d ",result.readfile_res_u.chunk.bytes,write_bytes);
#endif
        total_bytes += result.readfile_res_u.chunk.bytes;
        if (result.readfile_res_u.chunk.bytes < SIZE )
            break;
    }

    fclose(file);
    clnt_destroy(clnt);
    return 0;
}


/*
 * usage
 */
void usage(char *name) {
    printf(" Usage : %s [-f] <file-name> <dest-dir>\n\n", name);
    printf(" -f : With this option it fetches the file from the first available peer\n");
    printf(" file-name : name of the file that you are searching \n");
    printf(" dest-dir : Destination directory where you want to copy the fetched file\n");
}

int main(int argc, char *argv[])
{
    int result;
    int fopt = 0;
    int opt;

    if (argc < 3 || argc > 4) {
        usage(argv[0]);
        return (1);
    }

    while ((opt = getopt(argc, argv, "f")) != -1) {
        switch (opt) {
            case 'f':
                fopt = 1;
                break;
            default:
                usage(argv[0]);
                return (1);
        }
    }

    if (strlen(argv[fopt + 1]) == 0 || strlen(argv[fopt + 2]) == 0 ) {
        usage(argv[0]);
        return (1);
    }

    if ( gethostname(localhostname, sizeof(localhostname)) != 0) {
        printf("Unable to get the local hostname ! errno = %d\n", errno);
        return (1);
    }

    if (argv[fopt + 2][0] != '/') {
        printf("obtain_client : dest-dir %s : is not an absolute path !\n", argv[fopt+2]);
        printf("obtain_client : Please provide an absolute path for <dest-dir>\n");
        usage(argv[0]);
        return (1);
    }


    result = query_and_fetch(argv[fopt + 1], localhostname, argv[fopt + 2], fopt);

    return 0;
}
