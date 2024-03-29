/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "ind.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
registry_1(registry_rec *argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, registry,
		(xdrproc_t) xdr_registry_rec, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
search_1(query_req *argp, query_rec *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, search,
		(xdrproc_t) xdr_query_req, (caddr_t) argp,
		(xdrproc_t) xdr_query_rec, (caddr_t) clnt_res,
		TIMEOUT));
}
