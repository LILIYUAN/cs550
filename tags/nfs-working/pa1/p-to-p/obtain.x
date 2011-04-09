const SIZE = 4096;
const MAXNAME = 128;

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

union readfile_res switch (int errno) {
    case 0:
        datareceived chunk;
    default:
        void;
};

/*
 */
program OBTAINPROG {
    version OBTAINVER {
        readfile_res obtain(request *) = 1;
    } = 1;
} = 0x20000011;
