%#include <sys/vfs.h>
%#include <sys/types.h>
%#include <sys/stat.h>
%#include <fcntl.h>
%#include <dirent.h>
%#include <unistd.h>

const MAXNAME = 128;
const SIZE = 4096;

/*
 * Type for storing path . Assuming max file path length to be 1024
 */
typedef string filename<MAXNAME>;
typedef string pathname<MAXPATHLEN>;
typedef opaque filedata[SIZE];

typedef int my_dev_t;
typedef int my_ino_t;
typedef int my_mode_t;
typedef int my_uid_t;
typedef int my_gid_t;
typedef int my_off_t;
typedef int my_blksize_t;
typedef int my_blkcnt_t;
typedef int my_time_t;
typedef int my_nlink_t;

struct my_stat {
       my_dev_t     st_dev;     /* ID of device containing file */
       my_ino_t     st_ino;     /* inode number */
       my_mode_t    st_mode;    /* protection */
       my_nlink_t   st_nlink;   /* number of hard links */
       my_uid_t     st_uid;     /* user ID of owner */
       my_gid_t     st_gid;     /* group ID of owner */
       my_dev_t     st_rdev;    /* device ID (if special file) */
       my_off_t     st_size;    /* total size, in bytes */
       my_blksize_t st_blksize; /* blocksize for file system I/O */
       my_blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
       my_time_t    st_atime;   /* time of last access */
       my_time_t    st_mtime;   /* time of last modification */
       my_time_t    st_ctime;   /* time of last status change */
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
};

struct readdir_req {
	pathname name;
	int d_off;
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
	my_dev_t dev;
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
};

struct read_req {
	pathname name;
	int offset;
	int count;
};

struct write_res {
	int res;

};

struct write_req {
	pathname name;
	filedata data;
	int count;
	int offset;
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
	int len;
};

struct statfs_res {
	struct statfs stat;
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
	uid_t uid;
	gid_t gid;
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
	int bufzise;
};


program DSPROG {
    version DSVERS {
	getattr_res	getattr(getattr_req *)	= 1;
	readdir_res	readdir(readdir_req *)	= 2;
	mkdir_res	mkdir(mkdir_req *) 	= 3;
	unlink_res	unlink(unlink_req *) 	= 4;
	rmdir_res	rmdir(rmdir_req *) 	= 5;
	rename_res	rename(rename_req *) 	= 6;
	mknod_res	mknod(mknod_req *) 	= 7;

	create_res	create(create_req *) 	= 8;
	open_res 	open(open_req *) 	= 9;
	close_res 	close(close_res *) 	= 10;
	read_res	read(read_req *) 	= 11;	
	write_res	write(write_req *) 	= 12;	
	lookup_res	lookup(lookup_req *) 	= 13;

	truncate_res	truncate(truncate_req *)= 14;
	
	statfs_res	statfs(statfs_req *) 	= 15;
	chmod_res	chmod(chmod_req *)	= 16;
	chown_res	chown(chown_req *)	= 17;
	link_res	link(link_req *)	= 18;
	symlink_res	symlink(symlink_req *)	= 19;
	readlink_res	readlink(readlink_req *)= 20;
    } = 1;
} = 0x20000011;

