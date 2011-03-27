#!/usr/bin/ksh

# This test script is used to make multiple calls fetch the files
# from the peer servers. We need to pass the local host name from 
# where the search should start, file-name
# and the dest-dir to download / transfer the file on the local
# machine. Currently it is set to 1000 iterations. 1000 sequential
# calls are made to the peer servers to transfer the file.


 i=0

while [ $i -lt 1000 ]
do

    ./obtain_client -f $1 $2 $3
    i=$i+1
done

