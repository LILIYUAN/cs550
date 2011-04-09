#!/usr/bin/ksh
#
# This can be used to compile all the code.
# - index_server    : The index server executable
# - obtain_server   : The peer server executable
# - obtain_client   : The peer client which the user can use to fetch the files
#
 
make -f Makefile.ind
make -f Makefile.obtain
