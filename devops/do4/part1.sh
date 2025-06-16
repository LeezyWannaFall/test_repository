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

# check if SizeOfFiles is a valid format
if [[ ! $SizeOfFiles =~ ^[0-9]+[kK][bB]$ ]]; then
    echo "Error: file size must be a number followed by 'kb' (like 12kb, 12Kb, 12kB, or 12KB)"
    exit 1
fi

# Extract the numeric part from SizeOfFiles
numberOfSize=${SizeOfFiles%[kK][bB]}

# Check if the numeric part is a valid integer
if ! [[ $numberOfSize =~ ^[0-9]+$ ]]; then
    echo "Error: file size must be a number followed by 'kb' (like 12kb, 12Kb, 12kB, or 12KB)"
    exit 1
fi

# Check if the numeric part is less than or equal to 100
if (( numberOfSize > 100 )); then
    echo "Error: file size must be <= 100KB"
    exit 1
fi

# Create directory
for ((i=1; i<=$CntDirectories; i++)); do
    dirName="${directory}/${SymbolsDirectory}${i}"
    mkdir -p "$dirName"

    # Create files in directories
    for ((j=1; j<=$FilesInDirectories; j++)); do
        fileName="${dirName}/${NameOfFile}${j}.${ExtOfFile}"
        dd if=/dev/urandom of="$fileName" bs=1 count=$((numberOfSize * 1024)) status=none
    done
done

# CREATE SYMBOLIC LINKS
for ((i=1; i<=$CntDirectories; i++)); do
    dirName="${directory}/${SymbolsDirectory}${i}"
    for ((j=1; j<=$FilesInDirectories; j++)); do
        fileName="${dirName}/${NameOfFile}${j}.${ExtOfFile}"
        linkName="${dirName}/${SymbolsFiles}${j}"
        ln -s "$fileName" "$linkName"
    done
done

echo "Directories and files created successfully."
exit 0
fi

