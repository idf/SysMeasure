#!/usr/bin/env bash

function read_local_MB() {
   # param1: file size in MB
   F=$1 && let SZ=1024*$F && sudo ./read_local $SZ ${F}MB.txt > result/local/${F}MB.txt
}

function read_local_KB() {
   # param1: file size in MB
   SZ=$1 && sudo ./read_local $SZ ${SZ}KB.txt > result/local/${SZ}KB.txt
}