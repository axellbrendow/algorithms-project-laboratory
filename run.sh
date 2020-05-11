#!/bin/bash

help_msg="
USAGE01: ./run.sh [-h|--help] # This will print this message
USAGE02: ./run.sh 09 # This will run question 09
"

if [[ "$1" = "-h" || "$1" = "--help" ]]
then
    echo "$help_msg"
else
    pattern="$1"
    filename=$(find . -type f -name "$pattern*.cpp" -printf "%f" | cut -d "." -f 1)
    g++ $filename.cpp -o $filename.exe; ./$filename.exe < $filename.txt
fi
