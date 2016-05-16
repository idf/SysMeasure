#!/usr/bin/env bash

if [ $1 = 'localtest' ]; then
    python server.py localhost 50007 &
    python client.py localhost 50007
elif [ $1 = 'server' ]; then
    python server.py 0.0.0.0 50007
elif [ $1 = 'client' ]; then
    python client.py $2 50007  # 128.54.47.*
else
    echo "no argument matched"
fi
# need to kill server.py manually