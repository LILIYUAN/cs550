/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ds.h"
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

bool_t
xdr_filename (XDR *xdrs, filename *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, MAXNAME))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_pathname (XDR *xdrs, pathname *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, MAXPATHLEN))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_filedata (XDR *xdrs, filedata objp)
{
	register int32_t *buf;

	 if (!xdr_opaque (xdrs, objp, SIZE))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_dev_t (XDR *xdrs, my_dev_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_ino_t (XDR *xdrs, my_ino_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_mode_t (XDR *xdrs, my_mode_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_uid_t (XDR *xdrs, my_uid_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_gid_t (XDR *xdrs, my_gid_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_off_t (XDR *xdrs, my_off_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_blksize_t (XDR *xdrs, my_blksize_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_blkcnt_t (XDR *xdrs, my_blkcnt_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_time_t (XDR *xdrs, my_time_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_nlink_t (XDR *xdrs, my_nlink_t *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_stat (XDR *xdrs, my_stat *objp)
{
	register int32_t *buf;

	 if (!xdr_my_dev_t (xdrs, &objp->st_dev))
		 return FALSE;
	 if (!xdr_my_ino_t (xdrs, &objp->st_ino))
		 return FALSE;
	 if (!xdr_my_mode_t (xdrs, &objp->st_mode))
		 return FALSE;
	 if (!xdr_my_nlink_t (xdrs, &objp->st_nlink))
		 return FALSE;
	 if (!xdr_my_uid_t (xdrs, &objp->st_uid))
		 return FALSE;
	 if (!xdr_my_gid_t (xdrs, &objp->st_gid))
		 return FALSE;
	 if (!xdr_my_dev_t (xdrs, &objp->st_rdev))
		 return FALSE;
	 if (!xdr_my_off_t (xdrs, &objp->st_size))
		 return FALSE;
	 if (!xdr_my_blksize_t (xdrs, &objp->st_blksize))
		 return FALSE;
	 if (!xdr_my_blkcnt_t (xdrs, &objp->st_blocks))
		 return FALSE;
	 if (!xdr_my_time_t (xdrs, &objp->st_atime))
		 return FALSE;
	 if (!xdr_my_time_t (xdrs, &objp->st_mtime))
		 return FALSE;
	 if (!xdr_my_time_t (xdrs, &objp->st_ctime))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_my_dirent (XDR *xdrs, my_dirent *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_my_ino_t (xdrs, &objp->d_ino))
		 return FALSE;
	 if (!xdr_my_off_t (xdrs, &objp->d_off))
		 return FALSE;
	 if (!xdr_u_short (xdrs, &objp->d_reclen))
		 return FALSE;
	 if (!xdr_u_char (xdrs, &objp->d_type))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->d_name, 256,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_getattr_res (XDR *xdrs, getattr_res *objp)
{
	register int32_t *buf;

	 if (!xdr_my_stat (xdrs, &objp->sbuf))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_getattr_req (XDR *xdrs, getattr_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->path))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readdir_res (XDR *xdrs, readdir_res *objp)
{
	register int32_t *buf;

	 if (!xdr_my_dirent (xdrs, &objp->dent))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->eof))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readdir_req (XDR *xdrs, readdir_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->path))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->d_off))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_mkdir_res (XDR *xdrs, mkdir_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_mkdir_req (XDR *xdrs, mkdir_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->path))
		 return FALSE;
	 if (!xdr_my_mode_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_unlink_res (XDR *xdrs, unlink_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_unlink_req (XDR *xdrs, unlink_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rmdir_res (XDR *xdrs, rmdir_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rmdir_req (XDR *xdrs, rmdir_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rename_res (XDR *xdrs, rename_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rename_req (XDR *xdrs, rename_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->old))
		 return FALSE;
	 if (!xdr_pathname (xdrs, &objp->new))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_mknod_res (XDR *xdrs, mknod_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_mknod_req (XDR *xdrs, mknod_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->path))
		 return FALSE;
	 if (!xdr_my_mode_t (xdrs, &objp->mode))
		 return FALSE;
	 if (!xdr_my_dev_t (xdrs, &objp->dev))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_create_res (XDR *xdrs, create_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_create_req (XDR *xdrs, create_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->path))
		 return FALSE;
	 if (!xdr_my_mode_t (xdrs, &objp->mode))
		 return FALSE;
	 if (!xdr_my_dev_t (xdrs, &objp->dev))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_open_res (XDR *xdrs, open_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_open_req (XDR *xdrs, open_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->path))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->flags))
		 return FALSE;
	 if (!xdr_my_mode_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_close_res (XDR *xdrs, close_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_close_req (XDR *xdrs, close_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_read_res (XDR *xdrs, read_res *objp)
{
	register int32_t *buf;

	 if (!xdr_filedata (xdrs, objp->data))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->bytes))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_read_req (XDR *xdrs, read_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->offset))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->count))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_write_res (XDR *xdrs, write_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_write_req (XDR *xdrs, write_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_filedata (xdrs, objp->data))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->count))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->offset))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_lookup_res (XDR *xdrs, lookup_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_lookup_req (XDR *xdrs, lookup_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_truncate_res (XDR *xdrs, truncate_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_truncate_req (XDR *xdrs, truncate_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->len))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_statfs_res (XDR *xdrs, statfs_res *objp)
{
	register int32_t *buf;

	 if (!xdr_statfs (xdrs, &objp->stat))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_statfs_req (XDR *xdrs, statfs_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_chmod_res (XDR *xdrs, chmod_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_chmod_req (XDR *xdrs, chmod_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_my_mode_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_chown_res (XDR *xdrs, chown_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_chown_req (XDR *xdrs, chown_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_uid_t (xdrs, &objp->uid))
		 return FALSE;
	 if (!xdr_gid_t (xdrs, &objp->gid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_link_res (XDR *xdrs, link_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_link_req (XDR *xdrs, link_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->old))
		 return FALSE;
	 if (!xdr_pathname (xdrs, &objp->new))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_symlink_res (XDR *xdrs, symlink_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_symlink_req (XDR *xdrs, symlink_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->old))
		 return FALSE;
	 if (!xdr_pathname (xdrs, &objp->new))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readlink_res (XDR *xdrs, readlink_res *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->buf, MAXPATHLEN,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readlink_req (XDR *xdrs, readlink_req *objp)
{
	register int32_t *buf;

	 if (!xdr_pathname (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->bufzise))
		 return FALSE;
	return TRUE;
}
