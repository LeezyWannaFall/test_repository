#!/bin/bash

# Засекаем стартовое время (в секундах с миллисекундами)
start_time=$(date +%s.%N)

# Проверка: скрипт должен запускаться с одним аргументом (директорией)
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 /path/to/directory"
    exit 1
fi

# Сохраняем путь до директории в переменную
directory=$1

# Проверка: существует ли директория
if [ ! -d "$directory" ]; then
    echo "Error: $directory is not valid directory"
    exit 1
fi

# Подсчёт общего количества папок (включая вложенные)
total_folders=$(find $directory -type d | wc -l)

# Топ-5 папок по размеру (сначала выводим 6, чтобы пропустить первую строку с общей директорией)
top_folders=$(du -h --max-depth=1 "$directory" 2>/dev/null | sort -hr | head -n 6 | tail -n 5 | awk '{printf("%d - %s, %s\n", NR, $2, $1)}')

# Общее количество файлов
total_files=$(find $directory -type f | wc -l)

# Количество конфигурационных файлов (.conf)
total_conf_files=$(find $directory -type f -name "*.conf" | wc -l)

# Количество текстовых файлов (определяется по MIME-типу)
total_txt_files=$(find "$directory" -type f -exec file --mime-type {} + 2>/dev/null | grep 'text/plain' | wc -l)

# Количество исполняемых файлов
total_exec_files=$(find "$directory" -type f -executable | wc -l)

# Количество лог-файлов (.logs) — здесь есть ошибка: должно быть .log
total_logs_files=$(find $directory -type f -name "*.log" | wc -l)

# Количество архивов (по распространённым расширениям)
total_archive_files=$(find $directory -type f \( -name "*.tar" -o -name "*.gz" -o -name "*.zip" -o -name "*.rar" -o -name "*.7z" \) | wc -l)

# Количество символических ссылок
total_symlink_count=$(find "$directory" -type l | wc -l)

# Топ-10 самых больших файлов: размер, путь, тип файла
top_files=$(find "$directory" -type f -exec du -b {} + 2>/dev/null | sort -nr | head -n 10 | while read size path; do
    type=$(file -b "$path" | cut -d ' ' -f 1 | tr '[:upper:]' '[:lower:]') # Определяем тип файла
    echo "$path|$size|$type"
done | awk -F "|" '{printf "%d - %s, %.2f MB, %s\n", NR, $1, $2/1024/1024, $3}') # Форматированный вывод

# Топ-10 самых больших исполняемых файлов: путь, размер, MD5-хеш
top_execs=$(find "$directory" -type f -executable -exec du -b {} + 2>/dev/null | sort -nr | head -n 10 | while read size path; do
    hash=$(md5sum "$path" | awk '{print $1}') # Получаем MD5-хеш файла
    echo "$path|$size|$hash"
done | awk -F "|" '{printf "%d - %s, %.2f MB, %s\n", NR, $1, $2/1024/1024, $3}') # Форматированный вывод

# Засекаем конечное время
end_time=$(date +%s.%N)

# Вычисляем время выполнения скрипта и округляем до одного знака после запятой
script_time=$(printf "%.1f" "$(echo "$end_time - $start_time" | bc)")

# Выводим результаты
echo "Total number of folders (including all nested ones) = $total_folders"
echo "TOP 5 folders of maximum size arranged in descending order (path and size): "
echo "$top_folders"
echo "Total number of files = $total_files"
echo "Number of:"
echo "Configuration files (with the .conf extension) = $total_conf_files"
echo "Text files = $total_txt_files"
echo "Executable files = $total_exec_files"
echo "Log files (with the extension .log) = $total_logs_files"
echo "Archive files = $total_archive_files"
echo "Symbolic links = $total_symlink_count"
echo "TOP 10 files of maximum size arranged in descending order (path, size and type): "
echo "$top_files"
echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
echo "$top_execs"
echo "Script execution time (in seconds) = $script_time"
