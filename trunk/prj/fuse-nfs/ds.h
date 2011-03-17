/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DS_H_RPCGEN
#define _DS_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#define MAXNAME 128
#define SIZE 4096

typedef char *filename;

typedef char *pathname;

typedef char filedata[SIZE];

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

typedef int my_fsid_t;

struct my_stat {
	my_dev_t stat_dev;
	my_ino_t stat_ino;
	my_mode_t stat_mode;
	my_nlink_t stat_nlink;
	my_uid_t stat_uid;
	my_gid_t stat_gid;
	my_dev_t stat_rdev;
	my_off_t stat_size;
	my_blksize_t stat_blksize;
	my_blkcnt_t stat_blocks;
	my_time_t stat_atime;
	my_time_t stat_mtime;
	my_time_t stat_ctime;
};
typedef struct my_stat my_stat;

struct my_statfs {
	long f_type;
	long f_bsize;
	long f_blocks;
	long f_bfree;
	long f_bavail;
	long f_files;
	long f_ffree;
	my_fsid_t f_fsid;
	long f_namelen;
};
typedef struct my_statfs my_statfs;

struct my_dirent {
	my_ino_t d_ino;
	my_off_t d_off;
	u_short d_reclen;
	u_char d_type;
	char d_name[256];
};
typedef struct my_dirent my_dirent;

struct getattr_res {
	struct my_stat sbuf;
	int res;
};
typedef struct getattr_res getattr_res;

struct getattr_req {
	pathname name;
};
typedef struct getattr_req getattr_req;

struct readdir_res {
	struct my_dirent dent;
	int eof;
	int res;
};
typedef struct readdir_res readdir_res;

struct readdir_req {
	pathname name;
	int d_off;
};
typedef struct readdir_req readdir_req;

struct mkdir_res {
	int res;
};
typedef struct mkdir_res mkdir_res;

struct mkdir_req {
	pathname name;
	my_mode_t mode;
};
typedef struct mkdir_req mkdir_req;

struct unlink_res {
	int res;
};
typedef struct unlink_res unlink_res;

struct unlink_req {
	pathname name;
};
typedef struct unlink_req unlink_req;

struct rmdir_res {
	int res;
};
typedef struct rmdir_res rmdir_res;

struct rmdir_req {
	pathname name;
};
typedef struct rmdir_req rmdir_req;

struct rename_res {
	int res;
};
typedef struct rename_res rename_res;

struct rename_req {
	pathname old;
	pathname new;
};
typedef struct rename_req rename_req;

struct mknod_res {
	int res;
};
typedef struct mknod_res mknod_res;

struct mknod_req {
	pathname name;
	my_mode_t mode;
	my_dev_t dev;
};
typedef struct mknod_req mknod_req;

struct create_res {
	int res;
};
typedef struct create_res create_res;

struct create_req {
	pathname name;
	my_mode_t mode;
	my_dev_t dev;
};
typedef struct create_req create_req;

struct open_res {
	int res;
};
typedef struct open_res open_res;

struct open_req {
	pathname name;
	int flags;
	my_mode_t mode;
};
typedef struct open_req open_req;

struct close_res {
	int res;
};
typedef struct close_res close_res;

struct close_req {
	pathname name;
};
typedef struct close_req close_req;

struct read_res {
	filedata data;
	int bytes;
	int res;
};
typedef struct read_res read_res;

struct read_req {
	pathname name;
	int offset;
	int count;
};
typedef struct read_req read_req;

struct write_res {
	int res;
};
typedef struct write_res write_res;

struct write_req {
	pathname name;
	filedata data;
	int count;
	int offset;
};
typedef struct write_req write_req;

struct lookup_res {
	int res;
};
typedef struct lookup_res lookup_res;

struct lookup_req {
	pathname name;
};
typedef struct lookup_req lookup_req;

struct truncate_res {
	int res;
};
typedef struct truncate_res truncate_res;

struct truncate_req {
	pathname name;
	int len;
};
typedef struct truncate_req truncate_req;

struct statfs_res {
	struct my_statfs stat;
	int res;
};
typedef struct statfs_res statfs_res;

struct statfs_req {
	pathname name;
};
typedef struct statfs_req statfs_req;

struct chmod_res {
	int res;
};
typedef struct chmod_res chmod_res;

struct chmod_req {
	pathname name;
	my_mode_t mode;
};
typedef struct chmod_req chmod_req;

struct chown_res {
	int res;
};
typedef struct chown_res chown_res;

struct chown_req {
	pathname name;
	my_uid_t uid;
	my_gid_t gid;
};
typedef struct chown_req chown_req;

struct link_res {
	int res;
};
typedef struct link_res link_res;

struct link_req {
	pathname old;
	pathname new;
};
typedef struct link_req link_req;

struct symlink_res {
	int res;
};
typedef struct symlink_res symlink_res;

struct symlink_req {
	pathname old;
	pathname new;
};
typedef struct symlink_req symlink_req;

struct readlink_res {
	char buf[MAXPATHLEN];
	int res;
};
typedef struct readlink_res readlink_res;

struct readlink_req {
	pathname name;
	int bufsize;
};
typedef struct readlink_req readlink_req;

#define DSPROG 0x20000011
#define DSVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define getattr 1
extern  enum clnt_stat getattr_1(getattr_req *, getattr_res *, CLIENT *);
extern  bool_t getattr_1_svc(getattr_req *, getattr_res *, struct svc_req *);
#define readdir 2
extern  enum clnt_stat readdir_1(readdir_req *, readdir_res *, CLIENT *);
extern  bool_t readdir_1_svc(readdir_req *, readdir_res *, struct svc_req *);
#define mkdir 3
extern  enum clnt_stat mkdir_1(mkdir_req *, mkdir_res *, CLIENT *);
extern  bool_t mkdir_1_svc(mkdir_req *, mkdir_res *, struct svc_req *);
#define unlink 4
extern  enum clnt_stat unlink_1(unlink_req *, unlink_res *, CLIENT *);
extern  bool_t unlink_1_svc(unlink_req *, unlink_res *, struct svc_req *);
#define rmdir 5
extern  enum clnt_stat rmdir_1(rmdir_req *, rmdir_res *, CLIENT *);
extern  bool_t rmdir_1_svc(rmdir_req *, rmdir_res *, struct svc_req *);
#define rename 6
extern  enum clnt_stat rename_1(rename_req *, rename_res *, CLIENT *);
extern  bool_t rename_1_svc(rename_req *, rename_res *, struct svc_req *);
#define mknod 7
extern  enum clnt_stat mknod_1(mknod_req *, mknod_res *, CLIENT *);
extern  bool_t mknod_1_svc(mknod_req *, mknod_res *, struct svc_req *);
#define create 8
extern  enum clnt_stat create_1(create_req *, create_res *, CLIENT *);
extern  bool_t create_1_svc(create_req *, create_res *, struct svc_req *);
#define open 9
extern  enum clnt_stat open_1(open_req *, open_res *, CLIENT *);
extern  bool_t open_1_svc(open_req *, open_res *, struct svc_req *);
#define close 10
extern  enum clnt_stat close_1(close_req *, close_res *, CLIENT *);
extern  bool_t close_1_svc(close_req *, close_res *, struct svc_req *);
#define read 11
extern  enum clnt_stat read_1(read_req *, read_res *, CLIENT *);
extern  bool_t read_1_svc(read_req *, read_res *, struct svc_req *);
#define write 12
extern  enum clnt_stat write_1(write_req *, write_res *, CLIENT *);
extern  bool_t write_1_svc(write_req *, write_res *, struct svc_req *);
#define lookup 13
extern  enum clnt_stat lookup_1(lookup_req *, lookup_res *, CLIENT *);
extern  bool_t lookup_1_svc(lookup_req *, lookup_res *, struct svc_req *);
#define truncate 14
extern  enum clnt_stat truncate_1(truncate_req *, truncate_res *, CLIENT *);
extern  bool_t truncate_1_svc(truncate_req *, truncate_res *, struct svc_req *);
#define statfs 15
extern  enum clnt_stat statfs_1(statfs_req *, statfs_res *, CLIENT *);
extern  bool_t statfs_1_svc(statfs_req *, statfs_res *, struct svc_req *);
#define chmod 16
extern  enum clnt_stat chmod_1(chmod_req *, chmod_res *, CLIENT *);
extern  bool_t chmod_1_svc(chmod_req *, chmod_res *, struct svc_req *);
#define chown 17
extern  enum clnt_stat chown_1(chown_req *, chown_res *, CLIENT *);
extern  bool_t chown_1_svc(chown_req *, chown_res *, struct svc_req *);
#define link 18
extern  enum clnt_stat link_1(link_req *, link_res *, CLIENT *);
extern  bool_t link_1_svc(link_req *, link_res *, struct svc_req *);
#define symlink 19
extern  enum clnt_stat symlink_1(symlink_req *, symlink_res *, CLIENT *);
extern  bool_t symlink_1_svc(symlink_req *, symlink_res *, struct svc_req *);
#define readlink 20
extern  enum clnt_stat readlink_1(readlink_req *, readlink_res *, CLIENT *);
extern  bool_t readlink_1_svc(readlink_req *, readlink_res *, struct svc_req *);
extern int dsprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define getattr 1
extern  enum clnt_stat getattr_1();
extern  bool_t getattr_1_svc();
#define readdir 2
extern  enum clnt_stat readdir_1();
extern  bool_t readdir_1_svc();
#define mkdir 3
extern  enum clnt_stat mkdir_1();
extern  bool_t mkdir_1_svc();
#define unlink 4
extern  enum clnt_stat unlink_1();
extern  bool_t unlink_1_svc();
#define rmdir 5
extern  enum clnt_stat rmdir_1();
extern  bool_t rmdir_1_svc();
#define rename 6
extern  enum clnt_stat rename_1();
extern  bool_t rename_1_svc();
#define mknod 7
extern  enum clnt_stat mknod_1();
extern  bool_t mknod_1_svc();
#define create 8
extern  enum clnt_stat create_1();
extern  bool_t create_1_svc();
#define open 9
extern  enum clnt_stat open_1();
extern  bool_t open_1_svc();
#define close 10
extern  enum clnt_stat close_1();
extern  bool_t close_1_svc();
#define read 11
extern  enum clnt_stat read_1();
extern  bool_t read_1_svc();
#define write 12
extern  enum clnt_stat write_1();
extern  bool_t write_1_svc();
#define lookup 13
extern  enum clnt_stat lookup_1();
extern  bool_t lookup_1_svc();
#define truncate 14
extern  enum clnt_stat truncate_1();
extern  bool_t truncate_1_svc();
#define statfs 15
extern  enum clnt_stat statfs_1();
extern  bool_t statfs_1_svc();
#define chmod 16
extern  enum clnt_stat chmod_1();
extern  bool_t chmod_1_svc();
#define chown 17
extern  enum clnt_stat chown_1();
extern  bool_t chown_1_svc();
#define link 18
extern  enum clnt_stat link_1();
extern  bool_t link_1_svc();
#define symlink 19
extern  enum clnt_stat symlink_1();
extern  bool_t symlink_1_svc();
#define readlink 20
extern  enum clnt_stat readlink_1();
extern  bool_t readlink_1_svc();
extern int dsprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_filename (XDR *, filename*);
extern  bool_t xdr_pathname (XDR *, pathname*);
extern  bool_t xdr_filedata (XDR *, filedata);
extern  bool_t xdr_my_dev_t (XDR *, my_dev_t*);
extern  bool_t xdr_my_ino_t (XDR *, my_ino_t*);
extern  bool_t xdr_my_mode_t (XDR *, my_mode_t*);
extern  bool_t xdr_my_uid_t (XDR *, my_uid_t*);
extern  bool_t xdr_my_gid_t (XDR *, my_gid_t*);
extern  bool_t xdr_my_off_t (XDR *, my_off_t*);
extern  bool_t xdr_my_blksize_t (XDR *, my_blksize_t*);
extern  bool_t xdr_my_blkcnt_t (XDR *, my_blkcnt_t*);
extern  bool_t xdr_my_time_t (XDR *, my_time_t*);
extern  bool_t xdr_my_nlink_t (XDR *, my_nlink_t*);
extern  bool_t xdr_my_fsid_t (XDR *, my_fsid_t*);
extern  bool_t xdr_my_stat (XDR *, my_stat*);
extern  bool_t xdr_my_statfs (XDR *, my_statfs*);
extern  bool_t xdr_my_dirent (XDR *, my_dirent*);
extern  bool_t xdr_getattr_res (XDR *, getattr_res*);
extern  bool_t xdr_getattr_req (XDR *, getattr_req*);
extern  bool_t xdr_readdir_res (XDR *, readdir_res*);
extern  bool_t xdr_readdir_req (XDR *, readdir_req*);
extern  bool_t xdr_mkdir_res (XDR *, mkdir_res*);
extern  bool_t xdr_mkdir_req (XDR *, mkdir_req*);
extern  bool_t xdr_unlink_res (XDR *, unlink_res*);
extern  bool_t xdr_unlink_req (XDR *, unlink_req*);
extern  bool_t xdr_rmdir_res (XDR *, rmdir_res*);
extern  bool_t xdr_rmdir_req (XDR *, rmdir_req*);
extern  bool_t xdr_rename_res (XDR *, rename_res*);
extern  bool_t xdr_rename_req (XDR *, rename_req*);
extern  bool_t xdr_mknod_res (XDR *, mknod_res*);
extern  bool_t xdr_mknod_req (XDR *, mknod_req*);
extern  bool_t xdr_create_res (XDR *, create_res*);
extern  bool_t xdr_create_req (XDR *, create_req*);
extern  bool_t xdr_open_res (XDR *, open_res*);
extern  bool_t xdr_open_req (XDR *, open_req*);
extern  bool_t xdr_close_res (XDR *, close_res*);
extern  bool_t xdr_close_req (XDR *, close_req*);
extern  bool_t xdr_read_res (XDR *, read_res*);
extern  bool_t xdr_read_req (XDR *, read_req*);
extern  bool_t xdr_write_res (XDR *, write_res*);
extern  bool_t xdr_write_req (XDR *, write_req*);
extern  bool_t xdr_lookup_res (XDR *, lookup_res*);
extern  bool_t xdr_lookup_req (XDR *, lookup_req*);
extern  bool_t xdr_truncate_res (XDR *, truncate_res*);
extern  bool_t xdr_truncate_req (XDR *, truncate_req*);
extern  bool_t xdr_statfs_res (XDR *, statfs_res*);
extern  bool_t xdr_statfs_req (XDR *, statfs_req*);
extern  bool_t xdr_chmod_res (XDR *, chmod_res*);
extern  bool_t xdr_chmod_req (XDR *, chmod_req*);
extern  bool_t xdr_chown_res (XDR *, chown_res*);
extern  bool_t xdr_chown_req (XDR *, chown_req*);
extern  bool_t xdr_link_res (XDR *, link_res*);
extern  bool_t xdr_link_req (XDR *, link_req*);
extern  bool_t xdr_symlink_res (XDR *, symlink_res*);
extern  bool_t xdr_symlink_req (XDR *, symlink_req*);
extern  bool_t xdr_readlink_res (XDR *, readlink_res*);
extern  bool_t xdr_readlink_req (XDR *, readlink_req*);

#else /* K&R C */
extern bool_t xdr_filename ();
extern bool_t xdr_pathname ();
extern bool_t xdr_filedata ();
extern bool_t xdr_my_dev_t ();
extern bool_t xdr_my_ino_t ();
extern bool_t xdr_my_mode_t ();
extern bool_t xdr_my_uid_t ();
extern bool_t xdr_my_gid_t ();
extern bool_t xdr_my_off_t ();
extern bool_t xdr_my_blksize_t ();
extern bool_t xdr_my_blkcnt_t ();
extern bool_t xdr_my_time_t ();
extern bool_t xdr_my_nlink_t ();
extern bool_t xdr_my_fsid_t ();
extern bool_t xdr_my_stat ();
extern bool_t xdr_my_statfs ();
extern bool_t xdr_my_dirent ();
extern bool_t xdr_getattr_res ();
extern bool_t xdr_getattr_req ();
extern bool_t xdr_readdir_res ();
extern bool_t xdr_readdir_req ();
extern bool_t xdr_mkdir_res ();
extern bool_t xdr_mkdir_req ();
extern bool_t xdr_unlink_res ();
extern bool_t xdr_unlink_req ();
extern bool_t xdr_rmdir_res ();
extern bool_t xdr_rmdir_req ();
extern bool_t xdr_rename_res ();
extern bool_t xdr_rename_req ();
extern bool_t xdr_mknod_res ();
extern bool_t xdr_mknod_req ();
extern bool_t xdr_create_res ();
extern bool_t xdr_create_req ();
extern bool_t xdr_open_res ();
extern bool_t xdr_open_req ();
extern bool_t xdr_close_res ();
extern bool_t xdr_close_req ();
extern bool_t xdr_read_res ();
extern bool_t xdr_read_req ();
extern bool_t xdr_write_res ();
extern bool_t xdr_write_req ();
extern bool_t xdr_lookup_res ();
extern bool_t xdr_lookup_req ();
extern bool_t xdr_truncate_res ();
extern bool_t xdr_truncate_req ();
extern bool_t xdr_statfs_res ();
extern bool_t xdr_statfs_req ();
extern bool_t xdr_chmod_res ();
extern bool_t xdr_chmod_req ();
extern bool_t xdr_chown_res ();
extern bool_t xdr_chown_req ();
extern bool_t xdr_link_res ();
extern bool_t xdr_link_req ();
extern bool_t xdr_symlink_res ();
extern bool_t xdr_symlink_req ();
extern bool_t xdr_readlink_res ();
extern bool_t xdr_readlink_req ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DS_H_RPCGEN */
