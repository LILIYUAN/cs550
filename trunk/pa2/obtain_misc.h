#include "obtain.h"

typedef struct peers_s {
    int count;
    char *peer[MAXCOUNT];
} peers_t;

typedef struct query_node {
    b_query_req req;
    int sent;
    int recv;
    struct query_node *next;
} query_node_t;

typedef pending_req {
    query_node_t *head;
    pthread_mutex_t lock;
    int count;
} pending_req_t;
