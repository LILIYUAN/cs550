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

enum clnt_stat 
search_1(query_req *argp, query_rec *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, search,
		(xdrproc_t) xdr_query_req, (caddr_t) argp,
		(xdrproc_t) xdr_query_rec, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
addcache_1(addcache_req *argp, addcache_res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, addcache,
		(xdrproc_t) xdr_addcache_req, (caddr_t) argp,
		(xdrproc_t) xdr_addcache_res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
b_query_1(b_query_req *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, b_query,
		(xdrproc_t) xdr_b_query_req, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
b_hitquery_1(b_hitquery_reply *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, b_hitquery,
		(xdrproc_t) xdr_b_hitquery_reply, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
invalidate_1(invalidate_req *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, invalidate,
		(xdrproc_t) xdr_invalidate_req, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
update_1(update_req *argp, update_res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, update,
		(xdrproc_t) xdr_update_req, (caddr_t) argp,
		(xdrproc_t) xdr_update_res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
validate_1(validate_req *argp, validate_res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, validate,
		(xdrproc_t) xdr_validate_req, (caddr_t) argp,
		(xdrproc_t) xdr_validate_res, (caddr_t) clnt_res,
		TIMEOUT));
}
