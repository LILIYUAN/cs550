%#include <sys/vfs.h>
%#include <sys/types.h>
%#include <sys/stat.h>
%#include <fcntl.h>
%#include <dirent.h>
%#include <unistd.h>

#include "pnfs.h"

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
        mount_res   mount_mds(mount_req *) = 21;
    } = 1;
} = 0x20000011;

