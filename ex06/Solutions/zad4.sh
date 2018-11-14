#!/bin/bash

# create temporary file with unique name
tempfile="temp_$1_$2_`date`_`whoami`_swap"
touch "$tempfile"

cat "$1" > "$tempfile"
cat "$2" > "$1"
cat "$tempfile" > "$2"

rm -f "$tempfile"