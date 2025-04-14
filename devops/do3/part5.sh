#!/bin/bash

start_time=$(date +%s.%M)

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 /path/to/directory"
    exit 1
fi

directory=$1

if [ ! -d "$directory" ]; then
    echo "Error: $directory is not valid directory"
    exit 1
fi

#TO DO: main part of script

total_folders=$(find /home/leezy/test_repository/ -type d | wc -l)

top_folders=$(du -h --max-depth=1 "$directory" 2>/dev/null | sort -hr | head -n 6 | tail -n 5 | awk '{printf("%d - %s, %s\n", NR, $2, $1)}')

total_files=$(find $directory -type f | wc -l)

total_conf_files=$(find $directory -type f -name "*.conf" | wc -l)

total_exec_files=$(find "$directory" -type f -exec file --mime-type {} + 2>/dev/null | grep 'text/plain' | wc -l)

