#include <sys/types.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <unistd.h>
#include <errno.h> 
#include "ds.h"

typedef struct ds_struct {
    char    md_server[MAXNAMELEN];
    char    dir[MAXPATHLEN];
    fsid_t  fsid;
} ds_t;

typedef struct mds_struct {
    char    md_server[MAXNAMELEN];
    char    dir[MAXPATHLEN];
    fsid_t  fsid;
    char    *ds[MAXDS];
} mds_t;

#define DEBUG 1
