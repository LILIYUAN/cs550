#include <rpc/rpc.h>
#include "obtain.h"
#include <stdio.h>
#include <string.h>

extern __thread int errno;

int get_file(char *host, char *name)
{
    CLIENT *clnt;
    int total_bytes = 0, write_bytes;
    readfile_res *result;
    request req;
    FILE *file;

    req.name = name;
    req.start = 0;
    /*
     * Create client handle used for calling FTPPROG on
     * the server designated on the command line. Use
     * the tcp protocol when contacting the server.
     */
    clnt = clnt_create(host, OBTAINPROG, OBTAINVER, "tcp");
    if (clnt == NULL) {
        /*
         * Couldn't establish connection with server.
         * Print error message and stop.
         */
         clnt_pcreateerror(host);
         exit(1);
    }

    file = fopen("/tmp/name", "wb");

    /*
     * Call the remote procedure readdir on the server
     */
    while (1) {
        req.start = total_bytes;
        result = obtain_1(&req, clnt);
        if (result == NULL) {
            /*
             * An RPC error occurred while calling the server.
             * Print error message and stop.
             */
            clnt_perror(clnt, host);
            exit(1);
        }

        /*
         * Okay, we successfully called the remote procedure.
         */
        if (result->errno != 0) {
            /*
             * A remote system error occurred.
             * Print error message and stop.
             */
            errno = result->errno;
            perror(name);
            exit(1);
        }
        /*
         * Successfully got a chunk of the file.
         * Write into our local file.
         */
        write_bytes = fwrite(result->readfile_res_u.chunk.data, 1, result->readfile_res_u.chunk.bytes, file);
        total_bytes += result->readfile_res_u.chunk.bytes;
        if (result->readfile_res_u.chunk.bytes < SIZE) 
            break;
    }

    fclose(file);

    return 0;
}


int main(int argc, char *argv[])
{
   int result;

   if (argc != 3) {
        fprintf(stderr, "usage: %s host filepath\n", argv[0]);
        exit(1);
   }
   result = get_file(argv[1], argv[2]);

   return 0;
}
