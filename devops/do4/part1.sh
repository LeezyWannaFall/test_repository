#!/bin/bash

if [ "$#"  -ne 6 ]; then
    echo "Ошибка: необходимо передать 6 параметров"
    exit 1
fi


# PARAMETRS
directory=$1
CntDirectories=$2
SymbolsDirectory=$3
FilesInDirectories=$4
SymbolsFiles=$5
SizeOfFiles=$6
NameOfFile=$($SymbolsFiles | cut -d '.' -f1)

if [[ ! "$directory" == /* ]]; then
    echo "Error: path isnt absolute"
    exit 1
fi

if [[ ! "$CntDirectories" =~ ^[0-9]+$ ]]; then
    echo "Error: Invalid number of directories"
    exit 1
fi

if [[ ! "$SymbolsDirectory" =~ ^[a-zA-Z]+$ || ${#SymbolsDirectory} -gt 7 ]]; then
    echo "Error: Symbols of directory name isnt valid"
    exit 1
fi

if [[ ! "$FilesInDirectories" =~ ^[0-9]+$ ]]; then 
    echo "Error: Invalid number of files"
    exit 1
fi



echo "$NameOfFile"
# echo "$directory"
# echo "$CntDirectories"
# echo "$SymbolsDirectory"
# echo "$FilesInDirectories"
# echo "$SymbolsFiles"
# echo "$SizeOfFiles"