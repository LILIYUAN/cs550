#include "obtain.h"
#include <rpc/rpc.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern __thread int errno;

extern char *sharedir;

bool_t
obtain_1_svc(request *argp, readfile_res *result, struct svc_req *rqstp)
{
    FILE *file;
    int bytes;
    char filepath[MAXPATHLEN];

    printf("obtain_1_svc() : Entered : filepath : %s/%s\n", sharedir, argp->name);
    sprintf(filepath, "%s/%s", sharedir, argp->name);
    file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("Failed to open(%s) : errno %d\n", filepath, errno);
        result->errno = errno;
        return (FALSE);
    }

    fseek (file, argp->seek_bytes, SEEK_SET);
    bytes = fread(result->readfile_res_u.chunk.data, 1, SIZE, file);
    result->readfile_res_u.chunk.bytes = bytes;
    result->errno = 0;
    fclose(file);

    printf("obtain_1_svc() : Read %d bytes from %s:%d\n", bytes, filepath, argp->seek_bytes);
    return (TRUE);
}

int
obtainprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
