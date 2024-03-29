/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "obtain.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
obtain_1(request *argp, readfile_res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, obtain,
		(xdrproc_t) xdr_request, (caddr_t) argp,
		(xdrproc_t) xdr_readfile_res, (caddr_t) clnt_res,
		TIMEOUT));
}
