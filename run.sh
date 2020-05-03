#!/bin/bash

pattern="$1"
filename=$(find . -type f -name "$pattern*.cpp" -printf "%f" | cut -d "." -f 1)
g++ $filename.cpp -o $filename.exe; ./$filename.exe < $filename.txt
