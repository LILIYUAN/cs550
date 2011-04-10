#include <sys/types.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <unistd.h>
#include <errno.h> 
#include "mds.h"

typedef struct mds_struct {
    char    md_server[MAXNAMELEN];  /* Name of the md server */
    char    dir[MAXPATHLEN];        /* Name of the directory being shared */
    fsid_t  fsid;                   /* fsid of the directory */
    char    *ds[MAXDS];             /* pointers to the data-servers names */
    int     ds_cnt;                 /* Count of the data servers for this filesystem. */
    int     nxt_alloc_ds;           /* Index of the ds server to pick for extent allocation */
    int     nxt_create_ds;          /* Index of the ds server to pick for file creation */
} mds_t;

#define DEBUG 1
