#!/usr/bin/env bash

function read_local_MB() {
   # param1: file size in MB
   F=$1 && let SZ=1024*$F && sudo ./read $SZ ${F}MB.txt > result/local/${F}MB.txt
}

function read_local_KB() {
   # param1: file size in MB
   SZ=$1 && sudo ./read $SZ ${SZ}KB.txt > result/local/${SZ}KB.txt
}

remote_path="/Volumes/Someone's Public Folder/"

function read_remote_MB() {
   # param1: file size in MB
   F=$1 && let SZ=1024*$F && sudo ./read $SZ ${remote_path}${F}MB.txt > result/local/${F}MB.txt
}

function read_remote_KB() {
   # param1: file size in MB
   SZ=$1 && sudo ./read $SZ ${remote_path}${SZ}KB.txt > result/local/${SZ}KB.txt
}