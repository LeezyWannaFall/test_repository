#!/bin/bash

HOSTNAME=$(hostname)
TIMEZONE=$(cat /etc/timezone)
OS=$(cat /etc/issue | cut -d'\' -f1)
DATE=$(date +"%d %b %Y %H:%M:%S")
UPTIME=$(uptime -p)
UPTIME_SEC=$(( $(date +%s) - $(date -d "$(uptime -s)" +%s) ))
IP=$(ip -o -4 a | awk ' {print $4; exit}')
MASK=$(ipcalc $IP | grep -e "Netmask:" | awk ' {print $2}')
GATEWAY=$(ip r | awk '/default/ {print $3}')
RAM_TOTAL=$(free -b | awk '/Mem:/ {printf "%.3f", $2/1024/1024/1024}')
RAM_USED=$(free -b | awk '/Mem:/ {printf "%.3f", $3/1024/1024/1024}')
RAM_FREE=$(free -b | awk '/Mem:/ {printf "%.3f", $7/1024/1024/1024}')
SPACE_ROOT=$(df / | awk '/\// {printf "%.2f", $2/1024}')
SPACE_ROOT_USED=$(df / | awk '/\// {printf "%.2f", $3/1024}')
SPACE_ROOT_FREE=$(df / | awk '/\// {printf "%.2f", $4/1024}')

OUTPUT="HOSTNAME: $HOSTNAME
TIMEZONE: $TIMEZONE
USER: $USER
OS: $OS
DATE: $DATE
UPTIME: $UPTIME
UPTIME_SEC: $UPTIME_SEC
IP: $IP
MASK: $MASK
GATEWAY: $GATEWAY
RAM_TOTAL = ${RAM_TOTAL} GB
RAM_USED = ${RAM_USED} GB
RAM_FREE = ${RAM_FREE} GB
SPACE_ROOT = ${SPACE_ROOT} MB
SPACE_ROOT_USED = ${SPACE_ROOT_USED} MB
SPACE_ROOT_FREE = ${SPACE_ROOT_FREE} MB"

echo "$OUTPUT"

read -p "Сохранить информацию в файл? (Y/y - да, остальное нет) " ANSWER

if [[ $ANSWER == 'Y' || $ANSWER == 'y' ]]; then
    FILENAME=$(date +"%d_%m_%y_%H_%M_%S").status
    echo "$OUTPUT" > "$FILENAME"
    echo "Информация была успешна записана в файл: $FILENAME"
else
    echo "Информация не была сохранена"
fi
    