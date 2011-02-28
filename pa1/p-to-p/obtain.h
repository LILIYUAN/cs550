/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _OBTAIN_H_RPCGEN
#define _OBTAIN_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SIZE 4096
#define MAXNAME 128

typedef char *filename;

struct request {
	filename name;
	int seek_bytes;
};
typedef struct request request;


typedef char filedata[SIZE];

struct datareceived {
	filedata data;
	int bytes;
};
typedef struct datareceived datareceived;


struct readfile_res {
	int errno;
	union {
		datareceived chunk;
	} readfile_res_u;
};
typedef struct readfile_res readfile_res;

#define OBTAINPROG 0x20000011
#define OBTAINVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define obtain 1
extern  enum clnt_stat obtain_1(request *, readfile_res *, CLIENT *);
extern  bool_t obtain_1_svc(request *, readfile_res *, struct svc_req *);
extern int obtainprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define obtain 1
extern  enum clnt_stat obtain_1();
extern  bool_t obtain_1_svc();
extern int obtainprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_filename (XDR *, filename*);
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_filedata (XDR *, filedata);
extern  bool_t xdr_datareceived (XDR *, datareceived*);
extern  bool_t xdr_datareceived (XDR *, datareceived*);
extern  bool_t xdr_readfile_res (XDR *, readfile_res*);

#else /* K&R C */
extern bool_t xdr_filename ();
extern bool_t xdr_request ();
extern bool_t xdr_request ();
extern bool_t xdr_filedata ();
extern bool_t xdr_datareceived ();
extern bool_t xdr_datareceived ();
extern bool_t xdr_readfile_res ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_OBTAIN_H_RPCGEN */