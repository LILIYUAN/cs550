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
#define MAXCOUNT 16
#define MAXHOSTNAME 32
#define BUFSIZE 512
#define PRIMARY 0
#define CACHED 1

typedef u_long my_time_t;

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
	int error;
	union {
		datareceived chunk;
	} readfile_res_u;
};
typedef struct readfile_res readfile_res;

struct file_rec {
	char hostname[MAXNAME];
	int pflag;
	int rev;
	my_time_t ttr;
};
typedef struct file_rec file_rec;

struct query_req {
	char *fname;
	int count;
};
typedef struct query_req query_req;

struct query_rec {
	char fname[MAXNAME];
	int count;
	file_rec recs[MAXCOUNT];
	my_time_t mtime[MAXCOUNT];
	int eof;
};
typedef struct query_rec query_rec;

struct msg_id {
	long hostid;
	int seqno;
};
typedef struct msg_id msg_id;

struct b_query_req {
	msg_id id;
	int ttl;
	char uphost[MAXHOSTNAME];
	char fname[MAXNAME];
};
typedef struct b_query_req b_query_req;

struct b_hitquery_reply {
	msg_id id;
	int cnt;
	char fname[MAXNAME];
	file_rec recs[MAXCOUNT];
};
typedef struct b_hitquery_reply b_hitquery_reply;

struct invalidate_req {
	msg_id id;
	char originsvr[MAXHOSTNAME];
	char fname[MAXNAME];
	int ver;
	int ttl;
	int ttr;
};
typedef struct invalidate_req invalidate_req;

struct invalidate_res {
	int res;
};
typedef struct invalidate_res invalidate_res;

struct update_req {
	filename fname;
};
typedef struct update_req update_req;

struct update_res {
	int res;
};
typedef struct update_res update_res;

#define OBTAINPROG 0x20000011
#define OBTAINVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define obtain 1
extern  enum clnt_stat obtain_1(request *, readfile_res *, CLIENT *);
extern  bool_t obtain_1_svc(request *, readfile_res *, struct svc_req *);
#define search 2
extern  enum clnt_stat search_1(query_req *, query_rec *, CLIENT *);
extern  bool_t search_1_svc(query_req *, query_rec *, struct svc_req *);
#define b_query 3
extern  enum clnt_stat b_query_1(b_query_req *, void *, CLIENT *);
extern  bool_t b_query_1_svc(b_query_req *, void *, struct svc_req *);
#define b_hitquery 4
extern  enum clnt_stat b_hitquery_1(b_hitquery_reply *, void *, CLIENT *);
extern  bool_t b_hitquery_1_svc(b_hitquery_reply *, void *, struct svc_req *);
#define invalidate 5
extern  enum clnt_stat invalidate_1(invalidate_req *, void *, CLIENT *);
extern  bool_t invalidate_1_svc(invalidate_req *, void *, struct svc_req *);
#define update 6
extern  enum clnt_stat update_1(update_req *, update_res *, CLIENT *);
extern  bool_t update_1_svc(update_req *, update_res *, struct svc_req *);
extern int obtainprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define obtain 1
extern  enum clnt_stat obtain_1();
extern  bool_t obtain_1_svc();
#define search 2
extern  enum clnt_stat search_1();
extern  bool_t search_1_svc();
#define b_query 3
extern  enum clnt_stat b_query_1();
extern  bool_t b_query_1_svc();
#define b_hitquery 4
extern  enum clnt_stat b_hitquery_1();
extern  bool_t b_hitquery_1_svc();
#define invalidate 5
extern  enum clnt_stat invalidate_1();
extern  bool_t invalidate_1_svc();
#define update 6
extern  enum clnt_stat update_1();
extern  bool_t update_1_svc();
extern int obtainprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_my_time_t (XDR *, my_time_t*);
extern  bool_t xdr_filename (XDR *, filename*);
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_filedata (XDR *, filedata);
extern  bool_t xdr_datareceived (XDR *, datareceived*);
extern  bool_t xdr_datareceived (XDR *, datareceived*);
extern  bool_t xdr_readfile_res (XDR *, readfile_res*);
extern  bool_t xdr_file_rec (XDR *, file_rec*);
extern  bool_t xdr_query_req (XDR *, query_req*);
extern  bool_t xdr_query_rec (XDR *, query_rec*);
extern  bool_t xdr_msg_id (XDR *, msg_id*);
extern  bool_t xdr_b_query_req (XDR *, b_query_req*);
extern  bool_t xdr_b_hitquery_reply (XDR *, b_hitquery_reply*);
extern  bool_t xdr_invalidate_req (XDR *, invalidate_req*);
extern  bool_t xdr_invalidate_res (XDR *, invalidate_res*);
extern  bool_t xdr_update_req (XDR *, update_req*);
extern  bool_t xdr_update_res (XDR *, update_res*);

#else /* K&R C */
extern bool_t xdr_my_time_t ();
extern bool_t xdr_filename ();
extern bool_t xdr_request ();
extern bool_t xdr_request ();
extern bool_t xdr_filedata ();
extern bool_t xdr_datareceived ();
extern bool_t xdr_datareceived ();
extern bool_t xdr_readfile_res ();
extern bool_t xdr_file_rec ();
extern bool_t xdr_query_req ();
extern bool_t xdr_query_rec ();
extern bool_t xdr_msg_id ();
extern bool_t xdr_b_query_req ();
extern bool_t xdr_b_hitquery_reply ();
extern bool_t xdr_invalidate_req ();
extern bool_t xdr_invalidate_res ();
extern bool_t xdr_update_req ();
extern bool_t xdr_update_res ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_OBTAIN_H_RPCGEN */
