#!/bin/bash

if [ "$#"  -ne 6 ]; then
    echo "Error: 6 parameters must be passed"
    exit 1
fi


# PARAMETRS
directory=$1
CntDirectories=$2
SymbolsDirectory=$3
FilesInDirectories=$4
SymbolsFiles=$5
SizeOfFiles=$6

NameOfFile="${SymbolsFiles%%.*}"
ExtOfFile="${SymbolsFiles#*.}"

# DATA INPUT CHECKS
if [[ "$directory" != /* ]]; then
    echo "Error: path isnt absolute"
    exit 1
fi

check_integer() {
    local Value=$1
    local Name=$2
    if [[ ! $Value =~ ^[0-9]+$ ]]; then 
        echo "Error: $Name must be a non‑negative integer"
        exit 1
    fi
}

check_alpha() {
  local Value=$1
  local Name=$2
  local Maxlen=$3
  if [[ ! $Value =~ ^[A-Za-z]{1,$Maxlen}$ ]]; then
    echo "Error: $Name must be only letters (1-$Maxlen chars)"
    exit 1
  fi
}

check_integer "$CntDirectories" "number of directories"
check_integer "$FilesInDirectories" "number of files"
check_alpha "$SymbolsDirectory" "directory alphabet" 7
check_alpha "$NameOfFile" "file-name alphabet" 7
check_alpha "$ExtOfFile" "file-ext alphabet" 3

if [[ $SizeOfFiles =~ ^([0-9]{1,3})([kK][bB])$ ]]; then
    numberOfSize=${$BASH_REMATCH[1]}
    if [[ $numberOfSize -gt 100 ]] then
        echo "Error: file size must be <= 100KB"
        exit 1
else
    echo "Error: file size must be number+kb (like 12kb or 12Kb)"
    exit 1
fi

