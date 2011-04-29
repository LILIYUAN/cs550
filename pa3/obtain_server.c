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
extern pending_req_t    pending;
extern char             *localhostname;
extern char             *sharedir;
/*extern __thread int errno;*/

int seqno;
pthread_mutex_t seqno_lock = PTHREAD_MUTEX_INITIALIZER;

/*
 * This zero timeout used for one-way RPC calls.
 */
static struct timeval zero_timeout = {0, 0};

int
insert_node(query_node_t *p)
{
    if (!p) {
        return (FAILED);
    }

    /*
     * Add the timestamp.
     */
    (void) time(&(p->ts));
    pthread_mutex_lock(&(pending.lock));
    /*
     * Add the node to the tail of the list.
     * This will help us keep the nodes sorted by the timestamp.
     * i.e. the newer nodes will at the tail of the list.
     */
    if (pending.tail) {
        pending.tail->next = p;
    }
    pending.tail = p; 
    if (pending.head == NULL) {
        pending.head = p;
    }
    pending.count++;
    pthread_mutex_unlock(&(pending.lock));

    return (SUCCESS);
}

/*
 * remove_node:
 * - This searches for the node with the msg_id == m.
 *   If found, locks the node and pulls it out of the linkedlist and returns the
 *   node locked.
 */
query_node_t *remove_node(msg_id *m)
{
    query_node_t *p, *prev = NULL;
    pthread_mutex_lock(&(pending.lock));
    p = pending.head;

    if (!p) {
        pthread_mutex_unlock(&(pending.lock));
        return (NULL);
    }

    /*
     * Handle the head as a special case.
     */
    if (p->req.id.hostid == m->hostid && p->req.id.seqno == m->seqno) {
        /*
         * Make sure no one else is operating on this node.
         */
        pthread_mutex_lock(&p->node_lock);

        pending.head = pending.head->next;

        if (p == pending.tail) {
            pending.tail = prev;
        }

        pending.count--;
        pthread_mutex_unlock(&(pending.lock));
        return (p);
    }

    prev = pending.head;
    p = p->next;

    while (p && (p->req.id.hostid != m->hostid || p->req.id.seqno != m->seqno)) {
        prev = p;
        p = p->next;
    }

    /* 
     * We found a matching node.
     */
    if (p) {
        prev->next = p->next;

        if (p == pending.tail) {
            pending.tail = prev;
        }

        pending.count--;

        /*
         * Make sure that no one is operating on this node.
         */
        pthread_mutex_lock(&p->node_lock);
    }
    pthread_mutex_unlock(&(pending.lock));
    return (p);
}

/*
 * find_node():
 * - Searches the node with id == m and if found returns the locked node.
 *   (The difference between this and remove_node() is that remove_node()
 *   deletes the node from the linked list, whereas find_node() leaves the node
 *   on the linked list.
 */
query_node_t *
find_node(msg_id *m) 
{
    query_node_t *p = NULL;

    pthread_mutex_lock(&(pending.lock));
    p = pending.head;

    while (p && (p->req.id.hostid != m->hostid || p->req.id.seqno != m->seqno)) {
        p = p->next;
    }

    if (p) {
        pthread_mutex_lock(&p->node_lock);
    }
    pthread_mutex_unlock(&(pending.lock));
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
    FILE *fh;
    int fd;
    CLIENT *clnt;
    enum clnt_stat ret;
    int tmp;

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
query_node_t *
b_query_propagate(b_query_req *argp, int flag)
{
	bool_t retval = TRUE;
    query_node_t *node;
    b_query_req  req;
    peers_t my_cache;
    CLIENT *clnt;
    int i, cnt;
    enum clnt_stat stat;
    int ret;

    node = find_node(&argp->id);

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

    node = (query_node_t *)malloc(sizeof(query_node_t));
    if (node == NULL) {
        printf("Failed to allocate query_node_t. Hence not processing this request.\n");
        printf("Hoping the reaper thread will reap some memory\n");
        return (NULL);
    }

    node->req.id = argp->id;
    strcpy(node->req.uphost, argp->uphost);
    strcpy(node->req.fname, argp->fname);
    node->req.ttl = argp->ttl - 1;  /* Decrement the TTL by one */
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

    (void) insert_node(node);

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
valid_rec(file_rec *rec)
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
    query_node_t *node;
    file_rec rec, *p;
	char fname[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
	int i, fd;
    FILE *fh;
	peers_t resp;
    int ret;
    struct timeval now;
    struct timespec timeout;

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

    strcpy(result->fname, argp->fname);
    result->count = 0;
    p = &result->recs[result->count]; 
    
    while (!feof(fh)) {
        fscanf(fh, IND_REC_FMT, &rec.rev, &rec.pflag, &rec.ttr, rec.hostname);

        if (!valid_rec(&rec)) {
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
    query_node_t *node;
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
    node = find_node(&argp->id);

    /* 
     * If the query request is found on the local queue and we are not the
     * uphost relay the response back.
     * Else, the response is late (beyond 60 secs) and hence the reaper thread
     * has possibly reaped the query. Hence, do nothing.
     */
    if (node && strcmp(node->req.uphost, localhostname) != 0) {
        /*
         * We have the query details. Bubble up this response to the upstream
         * host.
         */
        clnt = clnt_create(node->req.uphost, OBTAINPROG, OBTAINVER, "tcp");
        if (clnt == NULL) {
            clnt_pcreateerror(node->req.uphost);
            printf("b_hitquery_1_svc() : Failed to relay the response to : %s\n", node->req.uphost);
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

bool_t
invalidate_1_svc(invalidate_req *argp, void *result, struct svc_req *rqstp)
{
}

/*
 * This a request to update a file revision.
 * This could be called by a client app. Or could be triggered internally.
 * We make sure we are the primary server for the file and then update it.
 */
bool_t
update_1_svc(update_req *argp, update_res *result, struct svc_req *rqstp)
{
    
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
reaper_thread(void *unused)
{
    query_node_t *p, *del_list = NULL;
    time_t ts;

    /*
     * Get the current timestamp.
     */
    time(&ts);

    while (TRUE) {
        sleep(INTERVAL);
        pthread_mutex_lock(&pending.lock);

        p = pending.head;

        /*
         * Build the delete list.
         */
        while (pending.head && (ts - pending.head->ts) > TIMEOUT) {
            p = pending.head;
            pending.head = pending.head->next;

            /*
             * If this is the last node make sure the tail of updated as well.
             */
            if (pending.tail == p){
                pending.tail = pending.head;
            }

            p->next = NULL;
            pthread_mutex_unlock(&pending.lock);

            /*
             * Wait for the any active users to drain out.
             */
            pthread_mutex_lock(&p->node_lock);
            free(p);
            pthread_mutex_lock(&pending.lock);
        }
        pthread_mutex_unlock(&pending.lock);
    }
}
