/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "mds_ds.h"
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

bool_t
getattr_mds_1_svc(getattr_req *argp, getattr_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
readdir_mds_1_svc(readdir_req *argp, readdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
mkdir_mds_1_svc(mkdir_req *argp, mkdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
unlink_mds_1_svc(unlink_req *argp, unlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
rmdir_mds_1_svc(rmdir_req *argp, rmdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
rename_mds_1_svc(rename_req *argp, rename_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
mknod_mds_1_svc(mknod_req *argp, mknod_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
create_mds_1_svc(create_req *argp, create_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
open_mds_1_svc(open_req *argp, open_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
close_mds_1_svc(close_req *argp, close_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
read_mds_1_svc(read_req *argp, read_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
write_mds_1_svc(write_req *argp, write_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
lookup_mds_1_svc(lookup_req *argp, lookup_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
truncate_mds_1_svc(truncate_req *argp, truncate_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
statfs_mds_1_svc(statfs_req *argp, statfs_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
chmod_mds_1_svc(chmod_req *argp, chmod_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
chown_mds_1_svc(chown_req *argp, chown_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
link_mds_1_svc(link_req *argp, link_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
symlink_mds_1_svc(symlink_req *argp, symlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
readlink_mds_1_svc(readlink_req *argp, readlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
mount_mds_1_svc(mount_req *argp, mount_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
getlayout_1_svc(getlayout_req *argp, getlayout_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

int
mdprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}

bool_t
getattr_ds_1_svc(getattr_req *argp, getattr_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
readdir_ds_1_svc(readdir_req *argp, readdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
mkdir_ds_1_svc(mkdir_req *argp, mkdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
unlink_ds_1_svc(unlink_req *argp, unlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
rmdir_ds_1_svc(rmdir_req *argp, rmdir_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
rename_ds_1_svc(rename_req *argp, rename_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
mknod_ds_1_svc(mknod_req *argp, mknod_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
create_ds_1_svc(create_req *argp, create_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
open_ds_1_svc(open_req *argp, open_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
close_ds_1_svc(close_req *argp, close_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
read_ds_1_svc(read_req *argp, read_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
write_ds_1_svc(write_req *argp, write_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
lookup_ds_1_svc(lookup_req *argp, lookup_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
truncate_ds_1_svc(truncate_req *argp, truncate_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
statfs_ds_1_svc(statfs_req *argp, statfs_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
chmod_ds_1_svc(chmod_req *argp, chmod_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
chown_ds_1_svc(chown_req *argp, chown_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
link_ds_1_svc(link_req *argp, link_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
symlink_ds_1_svc(symlink_req *argp, symlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
readlink_ds_1_svc(readlink_req *argp, readlink_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
mount_mds_1_svc(mount_req *argp, mount_res *result, struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

int
dsprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
