#include "obtain.h"

typedef struct peers_s {
    int count;
    char *peer[MAXCOUNT];
    CLIENT *clnt[MAXCOUNT];
} peers_t;

typedef struct query_node {
    b_query_req req;
    time_t      ts;
    int sent;
    int recv;
    struct query_node *next;
} query_node_t;

typedef pending_req {
    query_node_t *head;
    query_noed_t *tail;
    pthread_mutex_t lock;
    int count;
} pending_req_t;

#define MAXTTL  5
