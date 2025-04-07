#!/bin/bash

# Проверка вхождения параметров
if [[ -n "$1" && ! "$1" =~ ^[0-9]+$ ]] then 
    echo "$1"
else
    echo "Incorrect symbols or parametr not found"
fi