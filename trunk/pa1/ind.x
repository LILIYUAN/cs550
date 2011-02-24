
const MAXNAME = 128;
const MAXCOUNT = 16;
const MAXHOSTNAME = 16;
const BUFSIZE = 512; /* MAXHOSTNAME * MAXCOUNT */

struct registry_rec {
    string  peer<MAXNAME>;
    string  fname<MAXNAME>;
    int     ret;
};

struct query_req {
    string fname<MAXNAME>;
    int count;
};

struct query_rec {
    char fname[MAXNAME];
    int count;
    char peers[BUFSIZE];
};

program INDSRVPROG {
    version INDSRVVERS{
        int         registry(registry_rec) = 1;
        query_rec   search(query_req) = 2;
    } = 1;
} = 0x20000001;
