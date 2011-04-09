#!/bin/ksh

BASEDIR="~/cs550/pa2/"

ssh compute-0-0 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-0.peers $BASEDIR/data/share0 > /tmp/star-10-0.log 2>&1 " &
ssh compute-0-1 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-1.peers $BASEDIR/data/share1 > /tmp/star-10-1.log 2>&1 " &
ssh compute-0-2 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-2.peers $BASEDIR/data/share2 > /tmp/star-10-2.log 2>&1 " &
ssh compute-0-3 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-3.peers $BASEDIR/data/share3 > /tmp/star-10-3.log 2>&1" &
ssh compute-0-10 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-10.peers $BASEDIR/data/share10 > /tmp/star-10-4.log 2>&1" &
ssh compute-0-5 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-5.peers $BASEDIR/data/share5 > /tmp/star-10-5.log 2>&1" &
ssh compute-0-6 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-6.peers $BASEDIR/data/share6 > /tmp/star-10-6.log 2>&1" &
ssh compute-0-7 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-7.peers $BASEDIR/data/share7 > /tmp/star-10-7.log 2>&1" &
ssh compute-0-8 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-8.peers $BASEDIR/data/share8 > /tmp/star-10-8.log 2>&1" &
ssh compute-0-9 "$BASEDIR/obtain_server $BASEDIR/star-10node/compute-0-9.peers $BASEDIR/data/share9 > /tmp/star-10-9.log 2>&1" &
