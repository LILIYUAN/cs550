#!/usr/bin/ksh

# This test script is used to make multiple calls fetch the files
# from the peer servers. We need to pass the file name 
# and the dest-dir to download / transfer the file on the local
# machine. Currently it is set to 200 iterations. 200 sequential
# calls are made to the peer servers to transfer the file.

# -f option is used to pull the file from the first peer 
# serving the file.


 i=0

while [ $i -lt 200 ]
do

    ./obtain_client -f $1 $2 
    i=$i+1
done

