const MAXLEN = 1024;
const SIZE = 4096;
const MAXNAME = 128;
const MAXCOUNT = 16;
const MAXHOSTNAME = 16;
const BUFSIZE = 512; /* MAXHOSTNAME * MAXCOUNT */

/*
 * Type for storing path . Assuming max file path length to be 1024
 */
typedef string filename<MAXLEN>;

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
typedef string filedata<SIZE>;

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

union readfile_res switch (int errno) {
    case 0:
        datareceived chunk;
    default:
        void;
};

/*
 * Structure that is used to place the request
 * We query for the list of hosts servring the
 * file name
 */
struct query_req {
    string fname<MAXNAME>;
    int count;
};


/*
 * Structure that is recieved from the remote 
 * call. It will have the file name, number of
 * hosts serving the file and the lists of hosts
 */
struct query_rec {
    char fname[MAXNAME];
    int count;
    char peers[BUFSIZE];
};


/*
 */
program OBTAINPROG {
    version OBTAINVER {
        readfile_res obtain(request *) = 1;
	query_rec search(query_req) = 2;
    } = 1;
} = 0x20000011;
