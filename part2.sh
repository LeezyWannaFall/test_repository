#!/bin/bash

hostname=$(hostname)
timezone=$(cat /etc/timezone)
os=$(cat /etc/issue | cut -d'\' -f1)
date=$(date +"%d %b %Y %H:%M:%S")
uptime=$(uptime -p)
uptime_sec=$(( $(date +%s) - $(date -d "$(uptime -s)" +%s) ))
ip=$(ip -o -4 a | awk ' {print $4; exit}')
# to do 
# mask=$(ip -o -4 a | awk ' {print $4; exit}' | cut -d'/' -f2) 

echo "HOSTNAME: $hostname"
echo "TIMEZONE: $timezone"
echo "USER: $USER"
echo "OS: $os"
echo "DATE: $date"
echo "UPTIME: $uptime"
echo "UPTIME_SEC: $uptime_sec"
echo "IP: $ip"
# echo "MASK: $mask"
