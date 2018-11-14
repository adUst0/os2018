#!/bin/bash

file1="$1"
file2="$2"

sort "$file1" > "sorted_$file1"
sort "$file2" > "sorted_$file2"

diff -y "sorted_$file1" "sorted_$file2"

rm -f "sorted_$file1" "sorted_$file2"