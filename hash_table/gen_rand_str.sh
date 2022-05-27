#!/bin/bash

num=20          # $1
file="text"     # $2

MAX_LEN=30

# parse file and num
if [[ $# -eq 2 ]]; then
    num=$1
    file=$2

elif [[ $# -eq 1 ]]; then
    num=$1
fi

# clear string
> $file

str=""
for i in $(seq 1 $num)
do
    str=`echo $RANDOM | md5sum | base64 | head -c $(($RANDOM % $MAX_LEN))`
    if [[ -n $str ]]; then
        echo $str >> $file
    fi
done

echo "$num strings is generated into $file"

echo "===== file content ===="
cat < $file
