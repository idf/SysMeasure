#!/usr/bin/env bash

dd if=/dev/urandom of=$1 bs=1048576 count=$2
