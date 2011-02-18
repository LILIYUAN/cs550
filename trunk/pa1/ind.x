
const MAXNAME = 128;
const MAXCOUNT = 16;

struct registry_rec {
    string peer<MAXNAME>;
    string fname<MAXNAME>;
};

program INDSRVPROG {
    version INDSRVVERS{
        int registry(registry_rec) = 1;
    } = 1;
} = 0x20000001;
