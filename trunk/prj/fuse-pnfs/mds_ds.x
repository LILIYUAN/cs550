%#include <sys/vfs.h>
%#include <sys/types.h>
%#include <sys/stat.h>
%#include <fcntl.h>
%#include <dirent.h>
%#include <unistd.h>

const MAXHOSTNAME = 32;
const MAXNAMELEN = 128;
const SIZE = 4096;
const STRIPE_SZ = 16384;
const MAXDS = 16;
const MAXCOUNT = 32;
const OPREAD = 0;
const OPWRITE = 1;

/*
 * Type for storing path . Assuming max file path length to be 1024
 */
typedef string filename<MAXNAMELEN>;
typedef string pathname<MAXPATHLEN>;
typedef opaque filedata[SIZE];

typedef unsigned long my_dev_t;
typedef unsigned long my_ino_t;
typedef unsigned int my_mode_t;
typedef unsigned int my_uid_t;
typedef unsigned int my_gid_t;
typedef long my_off_t;
typedef long my_size_t;
typedef unsigned long my_blksize_t;
typedef long my_blkcnt_t;
typedef unsigned long my_time_t;
typedef unsigned long my_nlink_t;

struct nfs_fsid {
    int __val[2];
};

struct my_stat {
       my_dev_t     stat_dev;     /* ID of device containing file */
       my_ino_t     stat_ino;     /* inode number */
       my_mode_t    stat_mode;    /* protection */
       my_nlink_t   stat_nlink;   /* number of hard links */
       my_uid_t     stat_uid;     /* user ID of owner */
       my_gid_t     stat_gid;     /* group ID of owner */
       my_dev_t     stat_rdev;    /* device ID (if special file) */
       my_off_t     stat_size;    /* total size, in bytes */
       my_blksize_t stat_blksize; /* blocksize for file system I/O */
       my_blkcnt_t  stat_blocks;  /* number of 512B blocks allocated */
       my_time_t    stat_atime;   /* time of last access */
       my_time_t    stat_mtime;   /* time of last modification */
       my_time_t    stat_ctime;   /* time of last status change */
};

struct my_statfs {
       long    f_type;     /* type of file system (see below) */
       long    f_bsize;    /* optimal transfer block size */
       long    f_blocks;   /* total data blocks in file system */
       long    f_bfree;    /* free blocks in fs */
       long    f_bavail;   /* free blocks avail to non-superuser */
       long    f_files;    /* total file nodes in file system */
       long    f_ffree;    /* free file nodes in fs */
       nfs_fsid  f_fsid;     /* file system id */
       long    f_namelen;  /* maximum length of filenames */
};

struct my_dirent {
	my_ino_t          d_ino;       /* inode number */
	my_off_t          d_off;       /* offset to the next dirent */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file; not supported
				       by all file system types */
	char           d_name[256]; /* filename */
};

struct getattr_res {
	struct my_stat sbuf;	
	int res;
};

struct getattr_req {
	pathname name;
};

struct readdir_res {
	struct my_dirent dent;
	int eof;
	int res;
};

struct readdir_req {
	pathname name;
	my_off_t d_off;
};

struct mkdir_res {
	int res;

};

struct mkdir_req {
	pathname name;
	my_mode_t mode;
};

struct unlink_res {
	int res;
};

struct unlink_req {
	pathname name;
};

struct rmdir_res {
	int res;
};

struct rmdir_req {
	pathname name;
};

struct rename_res {
	int res;
};

struct rename_req {
	pathname old;
	pathname new;

};

struct mknod_res {
	int res;
};

struct mknod_req {
	pathname name;
	my_mode_t mode;
	my_dev_t dev;
};


struct create_res {
	int res;
};

struct create_req {
	pathname name;
	my_mode_t mode;
};

struct open_res {
	int res;
};

struct open_req {
	pathname name;
	int flags;
	my_mode_t mode;
};

struct close_res {
	int res;
};

struct close_req {
	pathname name;
};

struct read_res {
	filedata data;
	int bytes;
	int res;
};

struct read_req {
	pathname name;
	my_off_t offset;
	my_size_t count;
};

struct write_res {
	int res;

};

struct write_req {
	pathname name;
	filedata data;
	my_size_t count;
	my_off_t offset;
};

struct lookup_res {
	int res;
};

struct lookup_req {
	pathname name;
};

struct truncate_res {
	int res;
};

struct truncate_req {
	pathname name;
	my_off_t len;
};

struct statfs_res {
	struct my_statfs stat;
	int res;
};

struct statfs_req {
	pathname name;
};

struct chmod_res {
	int res;
};

struct chmod_req {
	pathname name;
	my_mode_t mode;
};

struct chown_res {
	int res;
};

struct chown_req {
	pathname name;
	my_uid_t uid;
	my_gid_t gid;
};

struct link_res {
	int res;
};

struct link_req {
	pathname old;
	pathname new;
};

struct symlink_res {
	int res;
};

struct symlink_req {
	pathname old;
	pathname new;
};

struct readlink_res {
	char buf[MAXPATHLEN];
	int res;
};

struct readlink_req {
	pathname name;
	int bufsize;
};

struct mount_req {
    pathname name;
};

struct mount_res {
    int         res;
    nfs_fsid    fsid;
};

/*
 * Metadata Server request and result data structures.
 */
struct layout_rec {
    my_off_t    off;
    my_size_t   len;
    char        dsname[MAXHOSTNAME];
    char        extname[MAXNAMELEN];
};

struct getlayout_req {
    string      fname<MAXNAMELEN>;
    my_off_t    offset;
    my_size_t   len;
    int         op;
};

struct getlayout_res {
    int             cnt;
    layout_rec      recs[MAXCOUNT];
    int             more_recs;
    my_size_t       sz;
};

program MDPROG {
    version MDVERS {
	getattr_res	getattr_mds(getattr_req *)	        = 1;
	readdir_res	readdir_mds(readdir_req *)	        = 2;
	mkdir_res	mkdir_mds(mkdir_req *) 	            = 3;
	unlink_res	unlink_mds(unlink_req *) 	        = 4;
	rmdir_res	rmdir_mds(rmdir_req *) 	            = 5;
	rename_res	rename_mds(rename_req *) 	        = 6;
	mknod_res	mknod_mds(mknod_req *) 	            = 7;

	create_res	create_mds(create_req *) 	        = 8;
	open_res 	open_mds(open_req *) 	            = 9;
	close_res 	close_mds(close_req *) 	            = 10;
	read_res	read_mds(read_req *) 	            = 11;	
	write_res	write_mds(write_req *) 	            = 12;	
	lookup_res	lookup_mds(lookup_req *) 	        = 13;

	truncate_res	truncate_mds(truncate_req *)    = 14;
	
	statfs_res	statfs_mds(statfs_req *) 	        = 15;
	chmod_res	chmod_mds(chmod_req *)	            = 16;
	chown_res	chown_mds(chown_req *)	            = 17;
	link_res	link_mds(link_req *)	            = 18;
	symlink_res	symlink_mds(symlink_req *)	        = 19;
	readlink_res	readlink_mds(readlink_req *)    = 20;
    mount_res       mount_mds(mount_req *)          = 21;
    getlayout_res   getlayout(getlayout_req *)      = 22;
    } = 1;
} = 0x20000001;

program DSPROG {
    version DSVERS {
	getattr_res	getattr_ds(getattr_req *)	= 1;
	readdir_res	readdir_ds(readdir_req *)	= 2;
	mkdir_res	mkdir_ds(mkdir_req *) 	= 3;
	unlink_res	unlink_ds(unlink_req *) 	= 4;
	rmdir_res	rmdir_ds(rmdir_req *) 	= 5;
	rename_res	rename_ds(rename_req *) 	= 6;
	mknod_res	mknod_ds(mknod_req *) 	= 7;

	create_res	create_ds(create_req *) 	= 8;
	open_res 	open_ds(open_req *) 	= 9;
	close_res 	close_ds(close_req *) 	= 10;
	read_res	read_ds(read_req *) 	= 11;	
	write_res	write_ds(write_req *) 	= 12;	
	lookup_res	lookup_ds(lookup_req *) 	= 13;

	truncate_res	truncate_ds(truncate_req *)= 14;
	
	statfs_res	statfs_ds(statfs_req *) 	= 15;
	chmod_res	chmod_ds(chmod_req *)	= 16;
	chown_res	chown_ds(chown_req *)	= 17;
	link_res	link_ds(link_req *)	= 18;
	symlink_res	symlink_ds(symlink_req *)	= 19;
	readlink_res	readlink_ds(readlink_req *)= 20;
    mount_res   mount_ds(mount_req *) = 21;
    } = 1;
} = 0x20000011;

