#!/bin/ksh

BASEDIR="~/cs550/pa2/"
ssh compute-0-0 "rm -rf /tmp/indsvr"
ssh compute-0-0 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-0.peers $BASEDIR/data/share0" &
ssh compute-0-1 "rm -rf /tmp/indsvr"
ssh compute-0-1 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-1.peers $BASEDIR/data/share1" &
ssh compute-0-2"rm -rf /tmp/indsvr"
ssh compute-0-2 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-2.peers $BASEDIR/data/share2" &
ssh compute-0-3 "rm -rf /tmp/indsvr"
ssh compute-0-3 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-3.peers $BASEDIR/data/share3" &
ssh compute-0-10 "rm -rf /tmp/indsvr"
ssh compute-0-10 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-10.peers $BASEDIR/data/share10" &
ssh compute-0-5 "rm -rf /tmp/indsvr"
ssh compute-0-5 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-5.peers $BASEDIR/data/share5" &
ssh compute-0-6 "rm -rf /tmp/indsvr"
ssh compute-0-6 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-6.peers $BASEDIR/data/share6" &
ssh compute-0-7 "rm -rf /tmp/indsvr"
ssh compute-0-7 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-7.peers $BASEDIR/data/share7" &
ssh compute-0-8 "rm -rf /tmp/indsvr"
ssh compute-0-8 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-8.peers $BASEDIR/data/share8" &
ssh compute-0-9 "rm -rf /tmp/indsvr"
ssh compute-0-9 "$BASEDIR/obtain_server $BASEDIR/mesh-10node/compute-0-9.peers $BASEDIR/data/share9" &
