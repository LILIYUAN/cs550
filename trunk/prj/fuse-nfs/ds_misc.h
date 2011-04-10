#include <sys/types.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <unistd.h>
#include <errno.h> 
#include "ds.h"

typedef struct ds_struct {
    char    md_server[MAXNAMELEN];  /* Name of the md server */
    char    dir[MAXPATHLEN];        /* Name of the Directory being shared */ 
    fsid_t  fsid;                   /* fsid of the directory */
} ds_t;

typedef struct mds_struct {
    char    md_server[MAXNAMELEN];  /* Name of the md server */
    char    dir[MAXPATHLEN];        /* Name of the directory being shared */
    fsid_t  fsid;                   /* fsid of the directory */
    char    *ds[MAXDS];             /* pointers to the data-servers names */
    int     ds_cnt;
} mds_t;

#define DEBUG 1