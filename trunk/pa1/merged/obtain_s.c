#include "obtain.h"
#include <rpc/rpc.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern __thread int errno;

#define SERVER_DIR "/tmp/srvdir"

bool_t obtain_1_svc(request *req, readfile_res *res,struct svc_req *rqstp) {

	FILE *file;
	int bytes;
        static char data[SIZE];

        file = fopen(req->name, "rb");
        if (file == NULL) {
        	res->errno = errno;
	        return (FALSE); 
        }

        fseek (file, req->seek_bytes, SEEK_SET);
        bytes = fread(data, 1, SIZE, file);
        res->readfile_res_u.chunk.data = data;
        res->readfile_res_u.chunk.bytes = bytes;

        res->errno = 0;
        fclose(file);
        return (TRUE);
}

bool_t search_1_svc(query_req *argp, query_rec *result, struct svc_req *rqstp) {
	FILE *fh;
	int cnt = 0;
	char filepath[MAXPATHLEN];
	char *p;

	sprintf(filepath, "%s/%s", SERVER_DIR, argp->fname);
	fh = fopen(filepath, "r");
	if (fh == NULL) {
        	result->count = 0;
	        return (FALSE);
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
      	int i;
        printf("Peers serving %s = %d \n", argp->fname, result->count);
        printf("peers %s\n", result->peers);
       	for (i = 0; i < result->count; i++) {
        	printf("hostname : %s\n", result->peers+(i * MAXHOSTNAME));
	}

        return (TRUE);
}

int
obtainprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
        xdr_free (xdr_result, result);

        return 1;
}
