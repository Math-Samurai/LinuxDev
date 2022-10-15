#!/bin/bash

DELAY=${1:-0.1}
str_num=0
picture=()
coords=()

tput clear
while IFS= read -r string
do
    picture+=("$string")
    for i in $(seq 0 $((${#string}-1)) )
    do
        coords+=("$str_num $i")
    done
    ((str_num++))
done

coords="$(echo -ne "$coords" | shuf)"

echo -ne "$picture" |
for iterator in $(shuf -i 0-$((${#coords[@]}-1)) )
do
    xCoord=$(echo ${coords[$iterator]} | cut -f 1 -d " ")
    yCoord=$(echo ${coords[$iterator]} | cut -f 2 -d " ")
    tput cup $xCoord $yCoord
    echo "${picture[$xCoord]: $yCoord :1}"
    sleep $DELAY
done

tput cup "$(tput lines)" 0
