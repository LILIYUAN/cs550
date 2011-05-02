#!/bin/ksh

BASEDIR="~/cs550/pa3/"

ssh compute-0-0 "$BASEDIR/obtain_server $BASEDIR/relay-test/compute-0-0.peers $BASEDIR/data/share0" &
ssh compute-0-1 "$BASEDIR/obtain_server $BASEDIR/relay-test/compute-0-1.peers $BASEDIR/data/share1" &
