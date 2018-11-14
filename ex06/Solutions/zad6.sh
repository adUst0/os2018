#!/bin/bash

# head -$2 $1 | tail -1 -> This is a shorter solution but it is very confusing

fileName="$1"
line=$2

head -$line $fileName | tail -1