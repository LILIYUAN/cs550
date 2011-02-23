const MAXLEN = 1024;
const SIZE = 8192;

/*
 * Type for storing path
 */
typedef string filename<MAXLEN>;

/*
 * Structure for sending request. Expects the path of the file
 * and the byte number at which to start reading the file from
 */
struct request {
    filename name;
    int start;
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
typedef string filechunk<SIZE>;

/*
 * Response sent by the server to the client as a response
 * to remote procedure call, containing the filechunk for
 * the current call and number of bytes actually read
 */
struct chunkreceive {
    filechunk data;
    int bytes;
};

/*
 * Type that represents the structure for file's chunks
 * to be received from the server
 */
typedef struct chunkreceive chunkreceive;

union readfile_res switch (int errno) {
    case 0:
        chunkreceive chunk;
    default:
        void;
};

/*
 * Remote procedure defined in the Interface Definition Language
 * of SUN RPC, contains PROGRAM and VERSION name definitions and
 * the remote procedure signature
 */
program OBTAINPROG {
    version OBTAINVER {
        readfile_res obtain(request *) = 1;
    } = 1;
} = 0x20000011;
