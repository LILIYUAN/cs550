/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _IND_H_RPCGEN
#define _IND_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAXNAME 128
#define MAXCOUNT 16
#define MAXHOSTNAME 16
#define BUFSIZE 512

struct registry_rec {
	char *peer;
	char *fname;
	int bw;
};
typedef struct registry_rec registry_rec;

struct query_req {
	char *fname;
	int count;
};
typedef struct query_req query_req;

struct query_rec {
	char fname[MAXNAME];
	int count;
	char peers[BUFSIZE];
	int bw[MAXCOUNT];
};
typedef struct query_rec query_rec;

#define INDSRVPROG 0x20000001
#define INDSRVVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define registry 1
extern  enum clnt_stat registry_1(registry_rec *, int *, CLIENT *);
extern  bool_t registry_1_svc(registry_rec *, int *, struct svc_req *);
#define search 2
extern  enum clnt_stat search_1(query_req *, query_rec *, CLIENT *);
extern  bool_t search_1_svc(query_req *, query_rec *, struct svc_req *);
extern int indsrvprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define registry 1
extern  enum clnt_stat registry_1();
extern  bool_t registry_1_svc();
#define search 2
extern  enum clnt_stat search_1();
extern  bool_t search_1_svc();
extern int indsrvprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_registry_rec (XDR *, registry_rec*);
extern  bool_t xdr_query_req (XDR *, query_req*);
extern  bool_t xdr_query_rec (XDR *, query_rec*);

#else /* K&R C */
extern bool_t xdr_registry_rec ();
extern bool_t xdr_query_req ();
extern bool_t xdr_query_rec ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_IND_H_RPCGEN */
