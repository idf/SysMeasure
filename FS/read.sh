#!/usr/bin/env bash
sudo -v

function read_local_MB() {
   # param1: file size in MB
   F=$1 && let SZ=1024*$F && sudo ./read $SZ ${F}MB.txt > result/local/${F}MB.txt
}

function read_local_KB() {
   # param1: file size in MB
   SZ=$1 && sudo ./read $SZ ${SZ}KB.txt > result/local/${SZ}KB.txt
}

remote_path="/Volumes/3.6-1/"

function read_remote_MB() {
   # param1: file size in MB
   F=$1 && let SZ=1024*$F && sudo ./read $SZ ${remote_path}${F}MB.txt > result/remote/${F}MB.txt
}

function read_remote_KB() {
   # param1: file size in MB
   SZ=$1 && sudo ./read $SZ ${remote_path}${SZ}KB.txt > result/remote/${SZ}KB.txt
}