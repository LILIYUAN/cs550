const SIZE = 4096;
const MAXNAME = 128;
const MAXCOUNT = 16;
const MAXHOSTNAME = 16;
const BUFSIZE = 512; /* MAXHOSTNAME * MAXCOUNT */

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

struct query_req {
    string fname<MAXNAME>;
    int count;
};

struct query_rec {
    char    fname[MAXNAME];
    int     count;
    char    peers[BUFSIZE];
    int     eof;
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
	msg_id	id;
	int		cnt;
	char	fname[MAXNAME];
	char	hosts[BUFSIZE];
};
	
/*
 */
program OBTAINPROG {
    version OBTAINVER {
        readfile_res	obtain(request *) = 1;
        query_rec   	search(query_req) = 2;
		/*
		 * The following are one-way RPC calls.
		 */
        void            b_query(b_query_req) = 3;
        void            b_hitquery(b_hitquery_reply) = 4;
    } = 1;
} = 0x20000011;


