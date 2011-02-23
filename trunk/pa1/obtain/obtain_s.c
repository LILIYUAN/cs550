#include <rpc/rpc.h>
#include <stdio.h>
#include "obtain.h"

extern __thread int errno;

readfile_res* obtain_1_svc(request *req, struct svc_req *rqstp)
{
    FILE *file;
    char data[1024];
    int bytes;
    static readfile_res res;

    file = fopen(req->name, "rb");
	printf("hello ");
    if (file == NULL) {
        res.errno = errno;
        return (&res);
    }

    fseek (file, req->start, SEEK_SET);
    bytes = fread(data, 1, 1024, file);

    res.readfile_res_u.chunk.data = data;
    res.readfile_res_u.chunk.bytes = bytes;

    /*
     * Return the result
     */
    res.errno = 0;
    fclose(file);
    return (&res);
}
