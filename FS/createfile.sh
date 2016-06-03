#!/usr/bin/env bash

dd if=/dev/urandom of=$1 bs=1024 count=$2
