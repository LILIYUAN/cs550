/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _IND_H_RPCGEN
#define _IND_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXNAME 128
#define MAXCOUNT 16

struct registry_rec {
	char *peer;
	char *fname;
};
typedef struct registry_rec registry_rec;

#define INDSRVPROG 0x20000001
#define INDSRVVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define registry 1
extern  int * registry_1(registry_rec *, CLIENT *);
extern  int * registry_1_svc(registry_rec *, struct svc_req *);
extern int indsrvprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define registry 1
extern  int * registry_1();
extern  int * registry_1_svc();
extern int indsrvprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_registry_rec (XDR *, registry_rec*);

#else /* K&R C */
extern bool_t xdr_registry_rec ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_IND_H_RPCGEN */