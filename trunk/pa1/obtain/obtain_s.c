#include <rpc/rpc.h>
#include <stdio.h>
#include "obtain.h"

extern __thread int errno;

readfile_res* obtain_1_svc(request *req, struct svc_req *rqstp)
{
    FILE *file;
    int bytes;
    static readfile_res res;
    static char data[SIZE];

    file = fopen(req->name, "rb");
	printf("hello ");
    if (file == NULL) {
        res.errno = errno;
        return (&res);
    }

    fseek (file, req->seek_bytes, SEEK_SET);
    bytes = fread(data, 1, SIZE, file);
    res.readfile_res_u.chunk.data = data;
    res.readfile_res_u.chunk.bytes = bytes;

    /*
     * Return the result
     */
    res.errno = 0;
    fclose(file);
    return (&res);
}
