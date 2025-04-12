#!/bin/bash

start_time=$(date +%s.%M)

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 /path/to/directory"
    exit 1
fi

directory=$1

if [ ! -d "$directory" ]; then
    echo "Error: $directory is not valid"
    exit 1
fi

#TO DO: main part of script

