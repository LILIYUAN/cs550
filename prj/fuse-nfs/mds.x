%#include <sys/vfs.h>
%#include <sys/types.h>
%#include <sys/stat.h>
%#include <fcntl.h>
%#include <dirent.h>
%#include <unistd.h>

#include "pnfs.h"

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

