#!/usr/bin/env bash

python server.py localhost 50007 &
python client.py localhost 50007

# need to kill server.py manually