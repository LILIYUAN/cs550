#include <rpc/rpc.h>
#include "obtain.h"
#include <stdio.h>
#include <string.h>

extern __thread int errno;

/*
 * This routine queries the index-server to find the list of peers serving the
 * file rec->fname.
 */
int query_and_fetch(char *fname, char *index_svr) {
	query_req req;
        query_rec res_rec;
        CLIENT *clnt;
        bool_t ret;
        int res, i;

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
        ret = search_1(&req,&res_rec,clnt);

        if (ret != RPC_SUCCESS) {
        	printf("ret = %d\n", ret);
	        clnt_perror (clnt, "call failed");
        }

        if (res_rec.count == 0) {
        	printf("Failed to find any peers serving file : %s\n", req.fname);
	        return (-1);
        }

        printf("Peers serving %s = %d\n", res_rec.fname, res_rec.count);
        printf("peers %s\n", res_rec.peers);
        for (i = 0; i < res_rec.count; i++) {
		printf("hostname : %s\n", res_rec.peers+(i * MAXHOSTNAME));
   	}

	return (0);
}

int get_file(char *host, char *name) {

	CLIENT *clnt;
	int total_bytes = 0, write_bytes;
	readfile_res result;
	request req;
	FILE *file;
	int ret = 1;
	req.name = name;
	req.seek_bytes = 0;

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
	        exit(1);
   	}

	//currently hardcoded to this as I am testing it on the same box....
        file = fopen("/tmp/name", "wb");

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
		        exit(1);
       		}

	        /*
 	        * Okay, we successfully called the remote procedure.
         	*/
	        if (result.errno != 0) {
          		/*
	         	* A remote system error occurred.
	   		* Print error message and stop.
	                */
        		errno = result.errno;
		        perror(name);
		        exit(1);
        	}
        	/*
	        * Successfully got a chunk of the file.
	        * Write into our local file.
        	*/

		//printf("\n read %d \t %s", result.readfile_res_u.chunk.bytes,result.readfile_res_u.chunk.data);
        	write_bytes = fwrite(result.readfile_res_u.chunk.data, 1, result.readfile_res_u.chunk.bytes, file);

		//printf("\n  write %d \t %s", result.readfile_res_u.chunk.bytes, result.readfile_res_u.chunk.data);


		// lets print the total number of bytes read and written in each cycle
		printf(" \n read %d written %d ",result.readfile_res_u.chunk.bytes,write_bytes);        
        	total_bytes += result.readfile_res_u.chunk.bytes;
		if (result.readfile_res_u.chunk.bytes < SIZE ) 
                break;
	}

    	fclose(file);

	return 0;
}


/*
 * usage
 */
void usage(char *name) {
    printf("Usage : %s <file-name> <index-server-name> \n", name);
    printf("\tfile-name - name of the file that you are searching \n");
    printf("\tinder-server-name - Hostname of the index server\n");
    printf("\tshare-dir - Directory that you would like to share\n");
}

int main(int argc, char *argv[])
{
	int result;


	if (argc != 3 || strlen(argv[1]) == 0 || strlen(argv[2]) == 0 ) {
        	usage(argv[0]);
	        return (1);
   	}

        result = get_file(argv[1], argv[2]);

        return 0;
}
