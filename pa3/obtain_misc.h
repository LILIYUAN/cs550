#include "obtain.h"
#include <stdio.h>
#include <errno.h>
#include <rpc/rpc.h>
#include <sys/file.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct peers_s {
    int     count;
    char    *peer[MAXCOUNT];
    CLIENT  *clnt[MAXCOUNT];
} peers_t;

typedef enum bcast {
    QUERY,
    INVALIDATE
} bcast_t;

typedef struct query_node {
    bcast_t             type;
    union {
        b_query_req q_req;
        invalidate_req  i_req;
    } data;
    time_t              ts;
    msg_id              id;
    int                 sent;
    int                 recv;
    pthread_cond_t      allhome_cv;
    pthread_mutex_t     node_lock;
    struct query_node   *next;
} node_t;

typedef struct pending_req {
    node_t    *head;
    node_t    *tail;
    pthread_mutex_t lock;
    int count;
} pending_req_t;

#define MAXTTL 4 
#define SERVER_DIR "/tmp/indsvr/"
#define CACHE_DIR "/tmp/cachedir/"

/*
 * Index record in the index file.
 * <revnumber> <primaryflag> <TTR> <hostname>
 */
#define IND_REC_FMT "%4d %2d %10lu %s\n"

#define DEBUG 1 
