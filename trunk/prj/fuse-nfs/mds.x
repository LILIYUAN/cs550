
const MAXNAME = 128;
const MAXCOUNT = 16;
const MAXHOSTNAME = 16;
const BUFSIZE = 512; /* MAXHOSTNAME * MAXCOUNT */

struct registry_rec {
    string  peer<MAXNAME>;
    string  fname<MAXNAME>;
    int     ret;
};

struct layout_rec {
    char    dsname[MAXHOSTNAME];
    int     offset;
    int     len;
};

struct getlayout_req {
    string  fname<MAXNAME>;
    int     offset;
};

struct getlayout_res {
    int             offset;
    layout_rec_t    recs[MAXCOUNT];
    int             more_recs;
};

program MDPROG {
    version MDVERS{
        getlayout_res   getlayout(getlayout_req)    = 1;
        access_res      access(access_req)          = 2;
        create_res      create(create_req)          = 3;

        query_rec   search(query_req) = 2;
    } = 1;
} = 0x20000001;
