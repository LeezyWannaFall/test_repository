#!/bin/bash

hostname=$(hostname)
timezone=$(cat /etc/timezone)
os=$(cat /etc/issue | cut -d'\' -f1)
date=$(date +"%d %b %Y %H:%M:%S")
uptime=$(uptime -p)
uptime_sec=$(( $(date +%s) - $(date -d "$(uptime -s)" +%s) ))
ip=$(ip -o -4 a | awk ' {print $4; exit}')
mask=$(ipcalc $ip | grep -e "Netmask:" | cut -d'=' -f1 | cut -d':' -f2)
gateway=$(ip r | grep -e "default" | awk -Fvia ' {print $2}' | cut -d'd' -f1)


echo -e "\e[32mHOSTNAME\e[0m: $hostname"
echo -e "\e[32mTIMEZONE\e[0m: $timezone"
echo -e "\e[32mUSER\e[0m: $USER"
echo -e "\e[32mOS\e[0m: $os"
echo -e "\e[32mDATE\e[0m: $date"
echo -e "\e[32mUPTIME\e[0m: $uptime"
echo -e "\e[32mUPTIME_SEC\e[0m: $uptime_sec"
echo -e "\e[32mIP\e[0m: $ip"
echo -e "\e[32mMASK\e[0m: $mask"
echo -e "\e[32mGATEWAY\e[0m: $gateway"
echo -e "\e[32mGATEWAY\e[0m: $
