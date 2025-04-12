#!/bin/bash

# Загружаем конфиг
CONFIG_FILE="config.conf"

# Проверяем наличе конфига
if [ ! -f "$CONFIG_FILE" ]; then
    echo "Ошибка: конфиг '$CONFIG_FILE' не найден."
    exit 1
fi

source "$CONFIG_FILE"

# Заменяем пустые параметры дефолтными
if [ -z "$column1_background" ]; then
    column1_background="1"
fi

if [ -z "$column2_background" ]; then
    column2_background="3"
fi

if [ -z "$column1_font_color" ]; then
    column1_font_color="6"
fi

if [ -z "$column2_font_color" ]; then
    column2_font_color="6"
fi

# Определяем цвета
COLORS=( "" "white" "red" "green" "blue" "purple" "black" )
BG_COLORS=( "" "47" "41" "42" "44" "45" "40" )
FG_COLORS=( "" "97" "31" "32" "34" "35" "30" )

# Присваиваем параметры
BG_TITLE=${BG_COLORS[$column1_background]}
FG_TITLE=${FG_COLORS[$column1_font_color]}
BG_VALUE=${BG_COLORS[$column2_background]}
FG_VALUE=${FG_COLORS[$column2_font_color]}
BG_TITLE_COLORNAME=${COLORS[$column1_background]}
FG_TITLE_COLORNAME=${COLORS[$column1_font_color]}
BG_VALUE_COLORNAME=${COLORS[$column2_background]}
FG_VALUE_COLORNAME=${COLORS[$column2_font_color]}

# Проверка диапазона
for param in $column1_background $column1_font_color $column2_background $column2_font_color; do
    if ! [[ "$param" =~ ^[1-6]$ ]]; then
        echo "Ошибка: параметры должны быть числами от 1 до 6."
        exit 1
    fi
done

# Проверяем, что цвет фона и шрифта не совпадают в каждой колонке
if [ "$column1_background" -eq "$column1_font_color" ]; then
    echo "Ошибка: Цвет фона и текста для названий значений совпадают (${COLORS[$column1_background]})."
    exit 1
fi

if [ "$column2_background" -eq "$column2_font_color" ]; then
    echo "Ошибка: Цвет фона и текста для значений совпадают (${COLORS[$column2_background]})."
    exit 1
fi

# Получаем системные данные
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

# Вывод инфы цветов
echo ""
if [ $column1_background -eq "1" ] && [ $column1_font_color -eq "6" ] && [ $column2_background -eq "3" ] && [ $column2_font_color -eq "6" ]; then 
    echo "Column 1 background = default ($BG_TITLE_COLORNAME)"
    echo "Column 1 font color = default ($FG_TITLE_COLORNAME)"
    echo "Column 2 background = default ($BG_VALUE_COLORNAME)"
    echo "Column 2 font color = default ($FG_VALUE_COLORNAME)"
else
    echo "Column 1 background = $column1_background ($BG_TITLE_COLORNAME)"
    echo "Column 1 font color = $column1_font_color ($FG_TITLE_COLORNAME)"
    echo "Column 2 background = $column2_background ($BG_VALUE_COLORNAME)"
    echo "Column 2 font color = $column2_font_color ($FG_VALUE_COLORNAME)"
fi