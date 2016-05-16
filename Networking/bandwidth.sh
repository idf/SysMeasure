#!/usr/bin/env bash

if [ $1 = 'localtest' ]; then
    python bandwidth_server.py localhost 50007 $2 &
    python bandwidth_client.py localhost 50007 $2
elif [ $1 = 'server' ]; then
    python bandwidth_server.py 0.0.0.0 50007 $2
elif [ $1 = 'client' ]; then
    python bandwidth_client.py $2 50007 $3  # 128.54.47.*
else
    echo "no argument matched"
fi
# need to kill server.py manually: pkill python