/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "obtain_misc.h"
#include <errno.h>

#define SUCCESS    0
#define FAILED    1

#define UNLOCKED    0
#define LOCKED      1

#define WAITTIME    1

extern peers_t          peers;
extern pending_req_t    qpending;
extern pending_req_t    ipending;
extern char             *localhostname;
extern char             *sharedir;
extern int push;
extern int pull;
/*extern __thread int errno;*/

int seqno;
pthread_mutex_t seqno_lock = PTHREAD_MUTEX_INITIALIZER;

/*
 * This zero timeout used for one-way RPC calls.
 */
static struct timeval zero_timeout = {0, 0};

int
insert_node(pending_req_t *pending, node_t *p)
{
    if (!p) {
        return (FAILED);
    }

    /*
     * Add the timestamp.
     */
    (void) time(&(p->ts));
    pthread_mutex_lock(&(pending->lock));
    /*
     * Add the node to the tail of the list.
     * This will help us keep the nodes sorted by the timestamp.
     * i.e. the newer nodes will at the tail of the list.
     */
    if (pending->tail) {
        pending->tail->next = p;
    }
    pending->tail = p; 
    if (pending->head == NULL) {
        pending->head = p;
    }
    pending->count++;
    pthread_mutex_unlock(&(pending->lock));

    return (SUCCESS);
}

/*
 * remove_node:
 * - This searches for the node with the msg_id == m.
 *   If found, locks the node and pulls it out of the linkedlist and returns the
 *   node locked.
 */
node_t *remove_node(pending_req_t *pending, msg_id *m)
{
    node_t *p, *prev = NULL;
    pthread_mutex_lock(&(pending->lock));
    p = pending->head;

    if (!p) {
        pthread_mutex_unlock(&(pending->lock));
        return (NULL);
    }

    /*
     * Handle the head as a special case.
     */
    if (p->id.hostid == m->hostid && p->id.seqno == m->seqno) {
        /*
         * Make sure no one else is operating on this node.
         */
        pthread_mutex_lock(&p->node_lock);

        pending->head = pending->head->next;

        if (p == pending->tail) {
            pending->tail = prev;
        }

        pending->count--;
        pthread_mutex_unlock(&(pending->lock));
        return (p);
    }

    prev = pending->head;
    p = p->next;

    while (p && (p->id.hostid != m->hostid || p->id.seqno != m->seqno)) {
        prev = p;
        p = p->next;
    }

    /* 
     * We found a matching node.
     */
    if (p) {
        prev->next = p->next;

        if (p == pending->tail) {
            pending->tail = prev;
        }

        pending->count--;

        /*
         * Make sure that no one is operating on this node.
         */
        pthread_mutex_lock(&p->node_lock);
    }
    pthread_mutex_unlock(&(pending->lock));
    return (p);
}

/*
 * find_node():
 * - Searches the node with id == m and if found returns the locked node.
 *   (The difference between this and remove_node() is that remove_node()
 *   deletes the node from the linked list, whereas find_node() leaves the node
 *   on the linked list.
 */
node_t *
find_node(pending_req_t *pending, msg_id *m) 
{
    node_t *p = NULL;

    printf("find_node: waiting for pending->lock\n");
    pthread_mutex_lock(&(pending->lock));
    p = pending->head;

    while (p && (p->id.hostid != m->hostid || p->id.seqno != m->seqno)) {
        p = p->next;
    }

    if (p) {
        pthread_mutex_lock(&p->node_lock);
    }
    pthread_mutex_unlock(&(pending->lock));
    printf("find_node: Done\n");
    return (p);
}

bool_t
obtain_1_svc(request *argp, readfile_res *result, struct svc_req *rqstp)
{
    FILE *file;
    int bytes;
    char filepath[MAXPATHLEN];

#ifdef DEBUG
    printf("obtain_1_svc() %s  : Entered : filepath : %s/%s\n", localhostname, sharedir, argp->name);
#endif

    sprintf(filepath, "%s/%s", sharedir, argp->name);
    file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("obtain_1_svc: Failed to open(%s) : errno %d\n", filepath, errno);
        result->error = errno;
        return (FALSE);
    }

    fseek (file, argp->seek_bytes, SEEK_SET);
    bytes = fread(result->readfile_res_u.chunk.data, 1, SIZE, file);
    result->readfile_res_u.chunk.bytes = bytes;
    result->error = 0;
    fclose(file);

#ifdef DEBUG
    printf("obtain_1_svc() : Served %d bytes from %s at offset : %d\n", bytes, filepath, argp->seek_bytes);
#endif
    return (TRUE);

}

int
build_peers_from_cache(char *fname, peers_t *resp)
{
    FILE *fh;
    int cnt = 0;
    char filepath[MAXPATHLEN];
    char *p;
    int fd;
    char host[MAXHOSTNAME+2];
    int pflag, rev; 
    my_time_t ttr;

#ifdef DEBUG
    printf("build_peers_from_cache %s : Processing query for file : %s\n", localhostname, fname);
#endif

    resp->count = 0;
    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fh = fopen(filepath, "r");
    if (fh == NULL) {
        return (cnt);
    }

    /*
     * If we have reached here there is possibly a peer which is serving this
     * file.
     */
    fd = fileno(fh);

    /*
     * Obtain a shared lock on the file while we are reading the contents.
     * This would block any modifications to the file while we are searching.
     * However, other searches can continue to access it.
     */
    flock(fd, LOCK_SH);

    while (cnt < MAXCOUNT && !feof(fh)) {
        fscanf(fh, IND_REC_FMT, &rev, &pflag, &ttr, host);
        resp->peer[cnt] = malloc((MAXHOSTNAME + 2) * sizeof(char));
        if (resp->peer[cnt] == NULL) {
            printf("search_cache: Out of memory !! Quitting !\n");
            exit (1);	
        }
        strcpy(resp->peer[cnt], host);
        cnt++;
    }

    /*
     * Pass back the count of peers that are serving this file.
     */
	resp->count = cnt;

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);

#ifdef DEBUG
    {
        int i;
        printf("Peers serving %s = %d \n", fname, resp->count);
        for (i = 0; i < resp->count; i++) {
            printf("hostname : %s\n", resp->peer[i]);
        }
    }
#endif /* DEBUG */

	return (cnt);
}

bool_t
peer_in_cache(peers_t *cache, char *host)
{
    int i, j;

    for (i = 0; i < cache->count; i++) {
        if (strcmp(cache->peer[i], host) == 0)
            return (TRUE);
    }
    return (FALSE);
}

/*
 * Generate a unique sequence number for this peer. 
 */
int getseqno(void)
{
    int ret;
    pthread_mutex_lock(&(seqno_lock));
	seqno++;
    ret = seqno;
    pthread_mutex_unlock(&(seqno_lock));
	return(ret);
}

bool_t
find_origin_rec(char *fname, file_rec *rec)
{
    char name[MAXPATHLEN];
    file_rec tmp;
    FILE *fh;
    int fd;

    sprintf(name, "%s/%s", SERVER_DIR, fname);

    fh = fopen(name, "r");
    if (fh == NULL) {
        printf("find_origin_rec: Failed to open filename %s : errno = %d\n", fname, errno);
        return TRUE;
    }

    fd = fileno(fh);
    flock(fd, LOCK_SH);

    while (!feof(fh)) {
        fscanf(fh, IND_REC_FMT, &tmp.rev, &tmp.pflag, &tmp.ttr, tmp.hostname);

        if (tmp.pflag == PRIMARY) {
            *rec = tmp;
            return TRUE;
        }
    }

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);
    return FALSE;
}

/*
 * This routine looks for the file in the local index directory
 * ("/tmp/indsvr/<filename>") and sends back the host names to uphost.
 *
 * It sends one RPC call with MAXCOUNT hosts in each of them.
 */
int
send_local_cache(char *fname_req, msg_id id, char *uphost)
{
    b_hitquery_reply res;
    char fname[MAXPATHLEN];
    file_rec *p;
    file_rec orig_rec;
    FILE *fh;
    int fd;
    CLIENT *clnt;
    enum clnt_stat ret;
    int tmp;
    bool_t orig = FALSE;

    if (!fname_req || !uphost) {
        return (SUCCESS);
    }

    sprintf(fname, "%s/%s", SERVER_DIR, fname_req);

    fh = fopen(fname, "r");
    if (fh == NULL) {
        printf("send_local_cache: Failed to open filename %s : errno = %d\n", fname, errno);
        return SUCCESS;
    }

    fd = fileno(fh);

    /*
     * Fetch the origin server record if there is one.
     */
    orig = find_origin_rec(fname_req, &orig_rec);

    clnt = clnt_create(uphost, OBTAINPROG, OBTAINVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(uphost);
        fclose(fh);
        close(fd);
        printf("send_local_cache(): Failed to contact hitquery to : %s\n", uphost);
        return FAILED;
    }

    if (clnt_control(clnt, CLSET_TIMEOUT, (char *)&zero_timeout) == FALSE) {
        printf("Failed to set the timeout value to zero\n");
        printf("Cannot make one-way RPC call :-(\n");
    }

    flock(fd, LOCK_SH);

    res.id = id;
    strcpy(res.fname, fname_req);
    res.cnt = 0;
    p = &res.recs[res.cnt]; 
    
    while (!feof(fh)) {
        fscanf(fh, IND_REC_FMT, &p->rev, &p->pflag, &p->ttr, p->hostname);
#ifdef DEBUG
        printf("send_local_cache: read rec : rev=%d pflag=%d ttr=%lu hostname=%s for file %s\n",
                p->rev, p->pflag, (unsigned long)p->ttr, p->hostname, res.fname);
#endif
            ret = b_hitquery_1(&res, &tmp, clnt);
        /*
         * If we found a origin server rec (orig_rec) then we compare the current records
         * rev with that of orig_rec.  If they are different we don't add that
         * record to the reply list.
         */
        if (orig && p->rev != orig_rec.rev) {
            continue;
        }
        res.cnt++;
        if (res.cnt == MAXCOUNT) {
            flock(fd, LOCK_UN);
            /*
             * Make one-way RPC call to send the response back.
             */
#ifdef DEBUG
            printf("send_local_cache: Sending response to %s for file %s\n", uphost, res.fname);
#endif
            ret = b_hitquery_1(&res, &tmp, clnt);
            if (ret != RPC_SUCCESS && ret != RPC_TIMEDOUT) {
                clnt_perror(clnt, "b_hitquery failed");
            }
            res.cnt = 0;
            flock(fd, LOCK_SH);
        }
        p = &res.recs[res.cnt];
    }

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);

#ifdef DEBUG
            printf("send_local_cache: Sending response to %s for file %s\n", uphost, res.fname);
#endif
    ret = b_hitquery_1(&res, &tmp, clnt);
    if (ret != RPC_SUCCESS && ret != RPC_TIMEDOUT) {
        clnt_perror(clnt, "b_hitquery failed");
    }

    clnt_destroy(clnt);
}

/*
 * b_query_propagate :
 * This routine is used by both search_svc_1() and b_query_svc_1() to propagate
 * the query to the peers.
 * 
 * RETURN VALUE :
 * If it relays the requests to its peers then it adds this request to a
 * local pending queue and returns a pointer to that request.
 *
 * Outline of the routine: 
 * - Checks if we already have received this query (check on the pending list
 *   for the msg_id of the received message.
 *      - If we already have processed this don't do anything.
 *      - Decrement the TTL. If TTL is zero after that don't relay it anymore but
 *        do the following :  
 *        - Look at the local cache and call b_hitquery() with the results to
 *          the uphost.
 *      - If we have not processed it we do the following :
 *          - Create a new query_req. Add it to the pending list.
 *          - Walk the list of peers and do the following :
 *              - Check if the cached index file already has the name of the
 *                peer.
 *              - If the peer name is not in the cache send it a b_query()
 *                request.
 *          - Look at the local cache and call b_hitquery() with the results to
 *            the uphost.
 */
node_t *
b_query_propagate(b_query_req *argp, int flag)
{
	bool_t retval = TRUE;
    node_t *node;
    b_query_req  req;
    peers_t my_cache;
    CLIENT *clnt;
    int i, cnt;
    enum clnt_stat stat;
    int ret;

#ifdef DEBUG
    printf("b_query_propagate: fname %s \n", argp->fname);
#endif

    node = find_node(&qpending, &argp->id);

    /*
     * We already have processed msg_id. Hence, we have nothing to do now.
     */
    if (node) {
        pthread_mutex_unlock(&node->node_lock);
#ifdef DEBUG
        printf("b_query_propagate: This request for file %s from %s is already processed\n", argp->fname, argp->uphost);
#endif
        return (NULL);
    }

    /*
     * We did not find a matching node. So, this is a new request and we need to
     * process it.
     */

    /*
     * Check if this request should be relayed to the peers.
     */
    if (argp->ttl <= 1) {
        /*
         * We don't need to relay this to the peers. 
         */
        return (NULL);
    }

    node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL) {
        printf("Failed to allocate node_t. Hence not processing this request.\n");
        printf("Hoping the reaper thread will reap some memory\n");
        return (NULL);
    }

    node->type = QUERY;
    node->data.q_req.id = argp->id;
    node->id = argp->id;
    strcpy(node->data.q_req.uphost, argp->uphost);
    strcpy(node->data.q_req.fname, argp->fname);
    node->data.q_req.ttl = argp->ttl - 1;  /* Decrement the TTL by one */
    node->sent = 0; node->recv = 0;
    node->next = NULL;
    pthread_mutex_init(&node->node_lock, NULL);
    pthread_cond_init(&node->allhome_cv, NULL);

    /*
     * Build the request that we need to send.
     */
    req.id = argp->id;
    strcpy(req.uphost, localhostname);
    strcpy(req.fname, argp->fname);
    req.ttl = argp->ttl - 1;

#ifdef DEBUG
    printf("b_query_propagate: before insert_node()\n");
#endif
    (void) insert_node(&qpending, node);

#ifdef DEBUG
    printf("b_query_propagate: insert_node() done\n");
#endif

    /*
     * Lock the node. This is to avoid processing of responses
     * even before we are done with the propagation of requests to all the peers.
     */
    pthread_mutex_lock(&node->node_lock);

    /*
     * Get the peers list from the cache.
     */
    cnt = build_peers_from_cache(argp->fname, &my_cache);

#ifdef DEBUG
    printf("b_query_propagate: my_cache.count = %d peers.count = %d\n", my_cache.count, peers.count);
#endif

    /*if (my_cache.count < peers.count) { */
    {
        /*
         * We have some peers to whom we need to relay the request.
         */
        for (i = 0; i < peers.count; i++) {
            /*
             * Check if we have already an entry for this peer cached.
             * If yes, continue to the next peer.
             * Also, Skip the uphost from whom we received this query.
             */
            if (strcmp(peers.peer[i], argp->uphost) == 0) {
#ifdef DEBUG
                printf("b_query_propagate: Skipping the uphost %s\n", argp->uphost);
#endif
                continue;
            }
#ifdef DEBUG
            printf("b_query_propagate: Looking for %s in my_cache\n", peers.peer[i]);
#endif
            if (peer_in_cache(&my_cache, peers.peer[i])) {
#ifdef DEBUG
                printf("b_query_propagate: peer_in_cache(%s) return TRUE\n", peers.peer[i]);
#endif
                continue;
            }
            /*
             * Use the cached client handler to make a call. If not create
             * one.
             */
#ifdef DEBUG
            printf("b_query_propagate(): Relaying query to %s for file %s\n", peers.peer[i], argp->fname);
            printf("Creating clnt handle for peer[%s]\n", peers.peer[i]);
#endif
            clnt = clnt_create(peers.peer[i], OBTAINPROG, OBTAINVER, "tcp");
            if (clnt == NULL) {
                clnt_pcreateerror (peers.peer[i]);
                /*
                 * Make a call only if we have a valid handle. We try to create
                 * a handle above. Ideally that should succeed. But, if we
                 * failed to create a client handle possible the peer is having
                 * problems. Hence ignore it and continue.
                 */
                continue;
            }
            /*
             * Now make a one-way RPC call to relay the message.
             */
            if (clnt_control(clnt, CLSET_TIMEOUT, (char *)&zero_timeout) == FALSE) {
                printf("Failed to set the timeout value to zero\n");
                printf("Cannot make oneway RPC calls and hence behaviour could be unpredictable\n");
            }
            stat = b_query_1(&req, &ret, clnt);
            if (stat != RPC_SUCCESS && stat != RPC_TIMEDOUT) {
                clnt_perror(clnt, "b_query failed");
                continue;
            }
            clnt_destroy(clnt);
#ifdef DEBUG
            printf("Called the b_query(%s)\n", peers.peer[i]);
#endif
            node->sent++;
        }
    }

    /*
     * Free up memory from my_cache.
     */
    for (i = 0; i < my_cache.count; i++) {
        free(my_cache.peer[i]);
    }

    /*
     * If the caller does not wanted the node locked.
     */
    if (flag == UNLOCKED) {
        pthread_mutex_unlock(&node->node_lock);
    }

    return (node);
}

/*
 * This routine decides if the given record of a file is valid.
 * The record is valid if the current version of the file is insync with origin
 * server.
 *
 * If it is a local cache record then :
 * - It is valid only if its TTR has not expired.
 */
bool_t
valid_rec(file_rec *orig, file_rec *rec)
{
    /*
     * TODO : Need to implement the validation.
     *
     * For now we assume that all records are valid.
     */
    return (TRUE);
}

bool_t
search_1_svc(query_req *argp, query_rec *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
	b_query_req *query;
    node_t *node;
    file_rec rec, *p;
	char fname[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
	int i, fd;
    FILE *fh;
	peers_t resp;
    int ret;
    struct timeval now;
    struct timespec timeout;
    file_rec orig_rec;
    int orig;

#ifdef DEBUG
    printf("search_1_svc() %s  : Received request for file : %s\n", localhostname, argp->fname);
#endif

    /*
     * Build the b_query_req for this request.
     */
    if ((query = (b_query_req *) malloc(sizeof(b_query_req))) == NULL) {
        printf("Failed to allocate memory !\n");
        printf("Hoping the reaper thread will free some memory !\n");
        goto send_result;
    }

	query->id.hostid = gethostid();
	query->id.seqno = getseqno(); 
    query->ttl = MAXTTL;
    strcpy(query->uphost, localhostname);
    strcpy(query->fname, argp->fname);

    /*
     * Now propagate the query to the peers.
     */
    node = b_query_propagate(query, LOCKED);

    /*
     * If we propagated to some peers then we should wait for some time for the
     * results to arrive and send the results.
     */
    if (node) { 
        if (node->sent) {
            /*
             * We now wait for a max of WAITTIME (1 second) on the CV (allhome_cv).
             * And the b_hitquery_reply() signals the CV when all the
             * peers that we had queried have reponded back. However, if no one
             * responds back we bail out in 1 secs.
             *
             * NOTE : This timeout may be short for large number of nodes.
             * However, for the current set up of upto to 12 nodes this is
             * reasonable.
             */
            gettimeofday(&now, NULL);
            timeout.tv_sec = now.tv_sec + WAITTIME;
            timeout.tv_nsec = now.tv_usec *1000;

            pthread_cond_timedwait(&node->allhome_cv, &node->node_lock, &timeout);
        }
        pthread_mutex_unlock(&node->node_lock);
    }

send_result:
    /*
     * At this point we should have received results from our peers and their
     * peers and the local cache should have been updated. So we now send our
     * hits from the local cache.
     */
    sprintf(fname, "%s/%s", SERVER_DIR, argp->fname);

    fh = fopen(fname, "r");
    if (fh == NULL) {
        printf("search_1_svc:Failed to open filename %s : errno = %d\n", fname, errno);
        result->count = 0;
        return retval;
    }

    fd = fileno(fh);
    flock(fd, LOCK_SH);

    /*
     * Fetch the origin server record if there is one.
     */
    orig = find_origin_rec(argp->fname, &orig_rec);

    strcpy(result->fname, argp->fname);
    result->count = 0;
    p = &result->recs[result->count]; 
    
    while (!feof(fh)) {
        fscanf(fh, IND_REC_FMT, &rec.rev, &rec.pflag, &rec.ttr, rec.hostname);

        /*
         * If we have a valid origin-server record makes sure the rev of this record is the
         * same. Else, we don't add this record to the response.
         */
        if (orig && orig_rec.rev != rec.rev) {
            continue;
        }

        /*
         * Copy the record into the result.
         */
        *p = rec;
        result->count++;

        /* 
         * We have filled up the response with MAXCOUNT results.
         * Send it back.
         */
        if (result->count == MAXCOUNT) {
            flock(fd, LOCK_UN);
            fclose(fh);
            close(fd);
            result->eof = 0;
            return retval;
        }
        p = &result->recs[result->count]; 
    }

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);
    result->eof = 1;
#ifdef DEBUG
    printf("search_1_svc: Done. count = %d\n", result->count);
#endif
	return retval;
}

bool_t
b_query_1_svc(b_query_req *argp, void *result, struct svc_req *rqstp)
{
    bool_t retval = TRUE;

#ifdef DEBUG
    printf("b_query_1_svc() : Received query for %s from %s\n", argp->fname, argp->uphost);
#endif

    /*
     * Propagate the query to the peers if they are not already in the local
     * cache.
     */
    (void) b_query_propagate(argp, UNLOCKED);

    /*
     * Send back the current contents of the local cache.
     */
    send_local_cache(argp->fname, argp->id, argp->uphost);

    return (retval);
}

/*
 * This routine handles the b_hitquery(). It does the following :
 *  - Look for the msg_id in the pending list.
 *  - If found :
 *      - Call b_hitquery() to the uphost.
 *      - Add the b_hitquery_reply->host to the local cache.
 *  - If not found :
 *      - This hitquery() came quite late and the local cache entry from pending
 *        has been freed. Hence, ignore the response.
 * NOTE : We have a reaper_thread() which wakes up every minute and frees all
 * pending requests which are older than a minute.
 */
bool_t
b_hitquery_1_svc(b_hitquery_reply *argp, void *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
    node_t *node;
    b_hitquery_reply req;
    CLIENT *clnt;
    int i;
    char *p;
    enum clnt_stat stat;
    int ret;
    int broadcast = 0;

#ifdef DEBUG
    printf("b_hitquery_1_svc() : Received b_hitquery for %s\n", argp->fname);
#endif
    /*
     * Search for the msg_id in the pending queue.
     */
    node = find_node(&qpending, &argp->id);

    /* 
     * If the query request is found on the local queue and we are not the
     * uphost relay the response back.
     * Else, the response is late (beyond 60 secs) and hence the reaper thread
     * has possibly reaped the query. Hence, do nothing.
     */
    if (node && strcmp(node->data.q_req.uphost, localhostname) != 0) {
        /*
         * We have the query details. Bubble up this response to the upstream
         * host.
         */
        clnt = clnt_create(node->data.q_req.uphost, OBTAINPROG, OBTAINVER, "tcp");
        if (clnt == NULL) {
            clnt_pcreateerror(node->data.q_req.uphost);
            printf("b_hitquery_1_svc() : Failed to relay the response to : %s\n", node->data.q_req.uphost);
        } else {
            if (clnt_control(clnt, CLSET_TIMEOUT, (char *)&zero_timeout) == FALSE) {
                printf("Failed to set the timeout value to zero\n");
                printf("Cannot make oneway RPC calls and hence behaviour could be unpredictable\n");
            }

            req.id = argp->id;
            req.cnt = argp->cnt;
            strcpy(req.fname, argp->fname);
            memcpy(req.recs, argp->recs, sizeof(argp->recs));

            stat = b_hitquery_1(&req, &ret, clnt);
            if (stat != RPC_TIMEDOUT && stat != RPC_SUCCESS) {
                clnt_perror(clnt, "b_hitquery failed");
            }
            clnt_destroy(clnt);
        }
    }


    /*
     * Record the results in the local cache (/tmp/indsvr/) so that we can reuse
     * this info for the next queries for this file.
     */
    for (i = 0; i < argp->cnt; i++) {
        add_peer(argp->fname, argp->recs[i].hostname, argp->recs[i].pflag,
                argp->recs[i].rev, argp->recs[i].ttr);
    }

    if (node) {
        node->recv++;
#ifdef DEBUG
        printf("b_hitquery_1_svc:recv = %d sent = %d\n", node->recv, node->sent);
#endif
        /*
         * Add code to signal the search_1_svc() which is wait for all the
         * responses to arrive.
         */
        if (node->recv >= node->sent) {
#ifdef DEBUG
            printf("broadcasting : so that search_1_svc() can respond back\n");
#endif
            pthread_cond_broadcast(&node->allhome_cv);
        }
        pthread_mutex_unlock(&node->node_lock);
    }

#ifdef DEBUG
    printf("b_hitquery_1_svc: Done for file %s\n", argp->fname);
#endif
	return retval;
}

/*
 * Find the record for peername in the index file. 
 */
int
is_origin_server(char *fname, char *peername, file_rec *rec) 
{
    FILE *fh;
    int fd;
    file_rec    tmp;
    int found = 0;
    char filepath[MAXPATHLEN];

    /*
     * Try to open the name of the file under the index diorectory. If it
     * already exists we open it else we create a new one.
     */
    sprintf(filepath, "%s/%s", SERVER_DIR, fname);
    fh = fopen(filepath, "a+");
    if (fh == NULL) {
        printf("index-server : Failed to make an entry : errno = %d : %s\n", errno, strerror(errno));
        return (-errno);
    }

    fd = fileno(fh);
    /*
     * Lock the file in shared mode so that other contending threads don't
     * modify it while we are searching.
     */
    flock(fd, LOCK_SH);

    /*
     * Search through the contents for the matching record and see if it is the
     * origin server.
     */
    while (!feof(fh)) {
        fscanf(fh, IND_REC_FMT, &tmp.rev, &tmp.pflag, &tmp.ttr, tmp.hostname);
#ifdef DEBUG
        printf("rev=%d pflag=%d peer=%s\n", tmp.rev, tmp.pflag, tmp.hostname);
#endif

        if (strcmp(tmp.hostname, peername) == 0) {
            found = 1;
            rec->rev = tmp.rev;
            rec->pflag = tmp.pflag;
            rec->ttr = tmp.ttr;
            strcpy(rec->hostname, tmp.hostname); 
            break;
        }
    }

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);

    if (found == 1 && rec->pflag == PRIMARY) {
        return (0);
    }

    return (-1);
}

/*
 *
 */
addcache_1_svc(addcache_req *req, addcache_res *res, struct svc_req *rqstp)
{


    char src[MAXPATHLEN], dest[MAXPATHLEN];
    FILE *in, *out;
    int bytes_in = 0, bytes_out = 0;
    char buf[SIZE];

    sprintf(src, "%s/%s",req->path, req->fname);
    sprintf(dest, "%s/%s",CACHE_DIR, req->fname);

    in = fopen (src, "rb");
    if (in == NULL) {
      perror (src);
    }
    out = fopen (dest, "wb");
    if (out == NULL) {
      perror (dest);
    }

    while ((bytes_in = fread (buf, 1, SIZE, in)) > 0) {
      bytes_out = fwrite (buf, 1, bytes_in, out);

      if (bytes_out != bytes_in) {
         perror ("Fatal write error.");
      }
    }    

    // call add peer
    add_peer( req->fname, localhostname, CACHED, req->ver, req->ttr);

}



/*
 * This routine does the following :
 *  - Adds the current request to the pending list and locks the entry.
 *  - Now, sends the message to all the peers.
 */
void
propagate_invalidate(invalidate_req *inval) 
{
    node_t *node = NULL;
    invalidate_req *req;
    invalidate_res res;
    int i=0;
    CLIENT *clnt;
    enum clnt_stat stat;

#ifdef DEBUG
        printf("propagate_invalidate: file %s originsvr %s \n", inval->fname, inval->originsvr);
#endif

    node = find_node(&ipending, &inval->id);

    if (node) {
        pthread_mutex_unlock(&node->node_lock);
#ifdef DEBUG
        printf("propagate_invalidate: This request for file %s is already processed\n", inval->fname);
#endif
        return;
    }

    node = malloc(sizeof(node_t));
    if (node == NULL) {
        printf("propagate_invalidate: Failed to allocate memory for invalidate request !\n");
        return ;
    }

    node->type = INVALIDATE;
    node->data.i_req.id = inval->id;
    node->data.i_req.ver = inval->ver;
    node->data.i_req.ttl = inval->ttl - 1;
    strcpy(node->data.i_req.originsvr, inval->originsvr);
    strcpy(node->data.i_req.fname, inval->fname);
    node->next = NULL;
    pthread_mutex_init(&node->node_lock, NULL);
    pthread_cond_init(&node->allhome_cv, NULL);

    (void) insert_node(&ipending, node);

    req = &(node->data.i_req);

    /*
     * Lock the node. This is to avoid processing of responses
     * even before we are done with the propagation of
     * requests to all the peers.
     */
    pthread_mutex_lock(&node->node_lock);
    
    /*
     * Now send this message to all the neighbors.
     */
    for (i = 0; i < peers.count; i++) {

        clnt = clnt_create(peers.peer[i], OBTAINPROG, OBTAINVER, "tcp");
        if (clnt == NULL) {
            clnt_pcreateerror (peers.peer[i]);
            /*
             * Make a call only if we have a valid handle. We try to create
             * a handle above. Ideally that should succeed. But, if we
             * failed to create a client handle possible the peer is having
             * problems. Hence ignore it and continue.
             */
            continue;
        }
        /*
         * Now make a one-way RPC call to relay the message.
         */
        if (clnt_control(clnt, CLSET_TIMEOUT, (char *)&zero_timeout) == FALSE) {
            printf("Failed to set the timeout value to zero\n");
            printf("Cannot make oneway RPC calls and hence behaviour could be unpredictable\n");
        }

        stat = invalidate_1(req, &res, clnt);
#ifdef DEBUG
        printf("propagate_invalidate: invalidate_1(fname=%s, originsvr=%s, ttl=%d, rev=%d) to %s\n",
                req->fname, req->originsvr, req->ttl, req->ver, peers.peer[i]);
#endif

        if (stat != RPC_SUCCESS && stat != RPC_TIMEDOUT) {
            clnt_perror(clnt, "b_query failed");
            continue;
        }
        clnt_destroy(clnt);
    }
    pthread_mutex_unlock(&node->node_lock);
}

/*
 * This a request to update a file revision.
 * This could be called by a client app. Or could be triggered internally.
 * We make sure we are the primary server for the file and then update it.
 */
bool_t
update_1_svc(update_req *argp, update_res *result, struct svc_req *rqstp)
{
    bool_t retval = TRUE;
    invalidate_req *inval;
    file_rec rec;
    int ret = 0;

#ifdef DEBUG
    printf("update_1_svc: file=%s\n", argp->fname);
#endif
    
    /*
     * Check this host is the origin server.
     * If not fail the request.
     */
    ret = is_origin_server(argp->fname, localhostname, &rec);

    if (ret != 0 || rec.pflag != PRIMARY) {
        result->res = ret;
        return retval;
    }

    inval = malloc(sizeof(invalidate_req));
    if (inval == NULL) {
        printf("update_1_svc: Failed to allocate memory for invalidate request !\n");
        result->res = ENOMEM;
        return retval;
    }

    inval->id.hostid = gethostid();
    inval->id.seqno = getseqno();
    inval->ttl = MAXTTL;
    strcpy(inval->originsvr, localhostname);
    strcpy(inval->fname, argp->fname);

    inval->ver = update_rec(argp->fname, localhostname, PRIMARY, -1, -1);

        /*
         * If rev returned a negative value something is wrong.
         * The file disappeared or someone removed my record.
         */
    if (inval->ver < 0) {
        result->res = inval->ver;
        free(inval);
        return retval;
    }

    /*
     * Now propagate it to the peers.
     */
    propagate_invalidate(inval);
    free(inval);

    return retval;
}

bool_t
invalidate_1_svc(invalidate_req *argp, void *result, struct svc_req *rqstp)
{
    int retval = TRUE;

    propagate_invalidate(argp);

    /*
     * Now, update the local index record.
     */
    update_rec(argp->fname, argp->originsvr, PRIMARY, argp->ver, argp->ttr);
}

int
obtainprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}

#define INTERVAL 30
#define TIMEOUT     60

/*
 * This is a reaper thread which walks the nodes of the pending list and frees
 * those nodes which are older than a minute.
 */
void *
reaper_thread(void *ptr)
{
    pending_req_t *pending = ptr;
    node_t *p, *del_list = NULL;
    time_t ts;

    /*
     * Get the current timestamp.
     */
    time(&ts);

    while (TRUE) {
        sleep(INTERVAL);
        pthread_mutex_lock(&pending->lock);

        p = pending->head;

        /*
         * Build the delete list.
         */
        while (pending->head && (ts - pending->head->ts) > TIMEOUT) {
            p = pending->head;
            pending->head = pending->head->next;

            /*
             * If this is the last node make sure the tail of updated as well.
             */
            if (pending->tail == p){
                pending->tail = pending->head;
            }

            p->next = NULL;
            pthread_mutex_unlock(&pending->lock);

            /*
             * Wait for the any active users to drain out.
             */
            pthread_mutex_lock(&p->node_lock);
            free(p);
            pthread_mutex_lock(&pending->lock);
        }
        pthread_mutex_unlock(&pending->lock);
    }
}
