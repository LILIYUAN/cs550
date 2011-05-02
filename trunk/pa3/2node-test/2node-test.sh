#!/bin/ksh

BASEDIR="~/cs550/pa3/"

ssh compute-0-0 "$BASEDIR/obtain_server $@ $BASEDIR/2node-test/compute-0-0.peers $BASEDIR/data/share0 > /tmp/2node-test2.0.log" &
ssh compute-0-1 "$BASEDIR/obtain_server $@ $BASEDIR/2node-test/compute-0-1.peers $BASEDIR/data/share1 > /tmp/2node-test2.1.log" &
