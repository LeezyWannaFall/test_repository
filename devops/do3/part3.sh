#!/bin/bash

# Проверка что вводится 4 параметра
if [ "$#" -ne 4 ]; then
    echo "Ошибка: необходимо передать 4 параметра (числа от 1 до 6)."
    echo "Пример: $0 1 3 4 5"
    exit 1
fi

# Определяем цвета
COLORS=( "" "white" "red" "green" "blue" "purple" "black" )
BG_COLORS=( "" "47" "41" "42" "44" "45" "40" )
FG_COLORS=( "" "97" "31" "32" "34" "35" "30" )

# Параметры
BG_TITLE=${BG_COLORS[$1]}
FG_TITLE=${FG_COLORS[$2]}
BG_VALUE=${BG_COLORS[$3]}
FG_VALUE=${FG_COLORS[$4]}

# Проверяем что параметры находятся в диапазоне 1-6
for param in "$@"; do
    if ! [[ "$param" =~ ^[1-6]$ ]]; then
        echo "Ошибка: все параметры должны быть числами от 1 до 6."
        exit 1
    fi
done

# Проверяем что цвет фона и шрифта не совпадают в каждой колонке
if [ "$1" -eq "$2" ]; then
    echo "Ошибка: Цвет фона и текста для названий значений совпадают (${COLORS[$1]})."
    exit 1
fi

if [ "$3" -eq "$4" ]; then
    echo "Ошибка: Цвет фона и текста для значений совпадают (${COLORS[$3]})."
    exit 1
fi

# Основная инфа
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

# Функция вывода цветного текста
print_colored() {
    echo -e "\e[$1m\e[$2m $3 \e[0m = \e[$4m\e[$5m $6 \e[0m"
}

# Вывод инфы
print_colored "$BG_TITLE" "$FG_TITLE" "HOSTNAME" "$BG_VALUE" "$FG_VALUE" "$HOSTNAME"
print_colored "$BG_TITLE" "$FG_TITLE" "TIMEZONE" "$BG_VALUE" "$FG_VALUE" "$TIMEZONE"
print_colored "$BG_TITLE" "$FG_TITLE" "USER" "$BG_VALUE" "$FG_VALUE" "$USER"
print_colored "$BG_TITLE" "$FG_TITLE" "OS" "$BG_VALUE" "$FG_VALUE" "$OS"
print_colored "$BG_TITLE" "$FG_TITLE" "DATE" "$BG_VALUE" "$FG_VALUE" "$DATE"
print_colored "$BG_TITLE" "$FG_TITLE" "UPTIME" "$BG_VALUE" "$FG_VALUE" "$UPTIME"
print_colored "$BG_TITLE" "$FG_TITLE" "UPTIME_SEC" "$BG_VALUE" "$FG_VALUE" "$UPTIME_SEC"
print_colored "$BG_TITLE" "$FG_TITLE" "IP" "$BG_VALUE" "$FG_VALUE" "$IP"
print_colored "$BG_TITLE" "$FG_TITLE" "MASK" "$BG_VALUE" "$FG_VALUE" "$MASK"
print_colored "$BG_TITLE" "$FG_TITLE" "GATEWAY" "$BG_VALUE" "$FG_VALUE" "$GATEWAY"
print_colored "$BG_TITLE" "$FG_TITLE" "RAM_TOTAL" "$BG_VALUE" "$FG_VALUE" "${RAM_TOTAL} GB"
print_colored "$BG_TITLE" "$FG_TITLE" "RAM_USED" "$BG_VALUE" "$FG_VALUE" "${RAM_USED} GB"
print_colored "$BG_TITLE" "$FG_TITLE" "RAM_FREE" "$BG_VALUE" "$FG_VALUE" "${RAM_FREE} GB"
print_colored "$BG_TITLE" "$FG_TITLE" "SPACE_ROOT" "$BG_VALUE" "$FG_VALUE" "${SPACE_ROOT} MB"
print_colored "$BG_TITLE" "$FG_TITLE" "SPACE_ROOT_USED" "$BG_VALUE" "$FG_VALUE" "${SPACE_ROOT_USED} MB"
print_colored "$BG_TITLE" "$FG_TITLE" "SPACE_ROOT_FREE" "$BG_VALUE" "$FG_VALUE" "${SPACE_ROOT_FREE} MB"