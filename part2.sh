#!/bin/bash

hostname=$(cat /etc/hostname)
timezone=$(cat /etc/timezone)
os=$(cat /etc/issue)
uptime=$(uptime -p)
uptime_sec=$(( $(date +%s) - $(date -d "$(uptime -s)" +%s) ))
ip=$(ip -4 a | awk ' /192/{print $2}')

echo "HOSTNAME: $hostname"
echo "TIMEZONE: $timezone"
echo "USER: $USER"
echo "OS: $os"
echo "UPTIME: $uptime"
echo "UPTIME_SEC: $uptime_sec"
echo "IP: $ip"
