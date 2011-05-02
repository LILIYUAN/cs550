const SIZE = 4096;
const MAXNAME = 128;
const MAXCOUNT = 1;
const MAXHOSTNAME = 32;
const BUFSIZE = 512; /* MAXHOSTNAME * MAXCOUNT */
const PRIMARY = 0;  /* Indicates a primary server */
const CACHED = 1;   /* Indicates a peer which has a cached entry */


typedef unsigned long my_time_t;

/*
 * Type for storing path . Assuming max file path length to be 1024
 */
typedef string filename<MAXNAME>;

/*
 * This is the structure for sending request. It has the path of 
 * the file name on the server and the byte number from where
 * the data should be read.
 */
struct request {
    filename name;
    int seek_bytes;
};

/*
 * Type that represents the structute for request
 */
typedef struct request request;

/*
 * Type for storing a chunk of the file that is being
 * sent from the server to the client in the current
 * remote procedure call
 */
typedef opaque filedata[SIZE];

/*
 * Response sent by the server to the client as a response
 * to remote procedure call, containing the filechunk for
 * the current call and number of bytes actually read
 */
struct datareceived {
    filedata data;
    int bytes;
};

/*
 * Type that represents the structure for file's chunks
 * to be received from the server
 */
typedef struct datareceived datareceived;

union readfile_res switch (int error) {
    case 0:
        datareceived chunk;
    default:
        void;
};

struct file_rec {
    int         ver;
    int         pflag;
    my_time_t   ttr;
    my_time_t   mtime;
    char        hostname[MAXNAME];
};

struct query_req {
    string fname<MAXNAME>;
    int count;
    long off;
};

struct query_rec {
    char        fname[MAXNAME];
    int         count;
    char        peers[BUFSIZE]; 
    int         pflags[MAXCOUNT];
    int         vers[MAXCOUNT];
    my_time_t   ttrs[MAXCOUNT];
    my_time_t   mtimes[MAXCOUNT];
    long        off;
    int         eof;
};

struct msg_id {
	long	hostid;
	int		seqno;
};

struct b_query_req {
	msg_id	id;
	int		ttl;
    char    uphost[MAXHOSTNAME];
	char	fname[MAXNAME];
};

struct b_hitquery_reply {
	msg_id	    id;
	int		    cnt;
    int         pflags[MAXCOUNT];
    int         vers[MAXCOUNT];
    my_time_t   ttrs[MAXCOUNT];
    my_time_t   mtimes[MAXCOUNT];
    char        fname[MAXNAME];
    char        hosts[BUFSIZE];
};

struct invalidate_req {
    msg_id  id;
    char    originsvr[MAXHOSTNAME];
    char    fname[MAXNAME];
    int     ver;
    int     ttl;
    int     ttr;
};

struct invalidate_res {
    int res;
};

struct update_req {
    filename    fname;
};

struct update_res {
    int res;
};

struct addcache_req {
    filename fname;
    filename path;
    int ver;
    my_time_t ttr;
};

struct addcache_res {
    int res;
};

struct validate_req {
    filename    fname;
    int         ver;
};

struct validate_res {
    char        fname[MAXPATHLEN];
    file_rec    frec;
    int         res;
};

/*
 */
program OBTAINPROG {
    version OBTAINVER {
        readfile_res	obtain(request *) = 1;
        query_rec   	search(query_req) = 2;
	addcache_res    addcache(addcache_req) = 3; 
		/*
		 * The following are one-way RPC calls.
		 */
        void            b_query(b_query_req) = 4;
        void            b_hitquery(b_hitquery_reply) = 5;
        void            invalidate(invalidate_req) = 6;
        update_res      update(update_req) = 7;
        validate_res    validate(validate_req) = 8;
    } = 1;
} = 0x20000011;
