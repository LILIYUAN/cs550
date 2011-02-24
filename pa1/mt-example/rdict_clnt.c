/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rdict.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
initw_1(void *argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, INITW,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
insertw_1(char **argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, INSERTW,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
deletew_1(char **argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, DELETEW,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
lookupw_1(char **argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, LOOKUPW,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}
