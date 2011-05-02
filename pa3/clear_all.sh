#!/bin/ksh

BASEDIR="~/cs550/pa3/"

ssh compute-0-0 "pkill obtain_server"
ssh compute-0-0 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-1 "pkill obtain_server"
ssh compute-0-1 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-2 "pkill obtain_server"
ssh compute-0-2 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-3 "pkill obtain_server"
ssh compute-0-3 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-5 "pkill obtain_server"
ssh compute-0-5 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-6 "pkill obtain_server"
ssh compute-0-6 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-7 "pkill obtain_server"
ssh compute-0-7 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-8 "pkill obtain_server"
ssh compute-0-8 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-9 "pkill obtain_server"
ssh compute-0-9 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-10 "pkill obtain_server"
ssh compute-0-10 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-11 "pkill obtain_server"
ssh compute-0-11 "rm -rf /tmp/indsvr /tmp/cachedir"

ssh compute-0-12 "pkill obtain_server"
ssh compute-0-12 "rm -rf /tmp/indsvr /tmp/cachedir"
