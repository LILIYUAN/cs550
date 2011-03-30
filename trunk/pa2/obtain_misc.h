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

typedef struct query_node {
    b_query_req req;
    time_t              ts;
    int                 sent;
    int                 recv;
    pthread_cond_t      allhome_cv;
    pthread_mutex_t     node_lock;
    struct query_node   *next;
} query_node_t;

typedef struct pending_req {
    query_node_t    *head;
    query_node_t    *tail;
    pthread_mutex_t lock;
    int count;
} pending_req_t;

#define MAXTTL 4 
#define SERVER_DIR "/tmp/indsvr/"

#define DEBUG 1 
