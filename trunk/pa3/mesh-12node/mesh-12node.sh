#!/bin/ksh

BASEDIR="~/cs550/pa3/"

ssh compute-0-0 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-0.peers $BASEDIR/data/share0 > /tmp/mesh-12-0.log" &
ssh compute-0-1 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-1.peers $BASEDIR/data/share1 > /tmp/mesh-12-1.log" &
ssh compute-0-2 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-2.peers $BASEDIR/data/share2 > /tmp/mesh-12-2.log" &
ssh compute-0-3 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-3.peers $BASEDIR/data/share3 > /tmp/mesh-12-3.log" &
ssh compute-0-12 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-12.peers $BASEDIR/data/share12 > /tmp/mesh-12-4.log" &
ssh compute-0-5 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-5.peers $BASEDIR/data/share5 > /tmp/mesh-12-5.log" &
ssh compute-0-6 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-6.peers $BASEDIR/data/share6 > /tmp/mesh-12-6.log" &
ssh compute-0-7 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-7.peers $BASEDIR/data/share7 > /tmp/mesh-12-7.log" &
ssh compute-0-8 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-8.peers $BASEDIR/data/share8 > /tmp/mesh-12-8.log" &
ssh compute-0-9 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-9.peers $BASEDIR/data/share9 > /tmp/mesh-12-9.log" &
ssh compute-0-10 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-10.peers $BASEDIR/data/share10 > /tmp/mesh-12-10.log" &
ssh compute-0-11 "$BASEDIR/obtain_server $@ $BASEDIR/mesh-12node/compute-0-11.peers $BASEDIR/data/share11 > /tmp/mesh-12-11.log" &
