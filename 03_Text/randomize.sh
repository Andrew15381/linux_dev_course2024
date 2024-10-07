#!/bin/bash

if [ $# = 1 ]; then
  t=$1
else
  t=0
fi

tmp=$(mktemp)

x=0
y=0

while read -r -N 1 ch; do
  x=$((x+1))
  case $ch in
  ([[:blank:]])
    continue;;
  ([[:space:]])
    x=0
    y=$((y+1));;
  (*)
    echo $ch $x $y >> $tmp;;
  esac
done

cat $tmp | shuf -o $tmp

clear
cat $tmp | while read -r line; do
  IFS=' ' read -r ch x y <<< $line
  tput cup $y $x
  echo $ch
  sleep $t
done

y=$((y+1))
tput cup $y 0

rm -f $tmp
