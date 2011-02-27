#!/usr/bin/ksh

 i=0

while [ $i -lt 1000 ]
do

    ./obtain_client -f $1 $2 $3
    i=$i+1
done

