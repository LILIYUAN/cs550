/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "nfs.h"
#ifndef _KERNEL
#include <stdio.h>
#include <stdlib.h> /* getenv, exit */
#endif /* !_KERNEL */

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

int *
read_1(argp, clnt)
	rd_wr_t *argp;
	CLIENT *clnt;
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof (clnt_res));
	if (clnt_call(clnt, READ,
		(xdrproc_t) xdr_rd_wr_t, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
write_1(argp, clnt)
	rd_wr_t *argp;
	CLIENT *clnt;
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof (clnt_res));
	if (clnt_call(clnt, WRITE,
		(xdrproc_t) xdr_rd_wr_t, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
