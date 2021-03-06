#!/bin/bash

count=0
diff=0
total=0
lines=0
i=1
x=10
biggest=0

while getopts x: flag
do
	case "${flag}" in
		x) x=${OPTARG};;
	esac
done

while [ $i -le $x ]
do
  echo "Run $i / $x"
#  string=`./generator --flow-one | ./lem-in -l| grep 'lines'`
#  string=`./generator --flow-ten | ./lem-in -l| grep 'lines'`
# string=`./generator --flow-thousand | ./lem-in -l| grep 'lines'`
#  string=`./generator --big | ./lem-in -l| grep 'lines'`
  string=`./generator --big-superposition | ./lem-in -l| grep 'lines'`
  required=`echo "$string" | cut -d " " -f 8 | sort -u`
  echo "lines required: " $required
  lines=`echo "$string" | grep 'lines: ' | awk '{print $2}'`
  echo "lines used: " $lines
  diff=$((lines-required))
  echo "difference: " $diff
  if [ "$diff" -gt "$biggest" ]
  	then
  		biggest=$diff
  fi
  total=$((total+=diff))
  i=$(( $i + 1 ))
  count=$(( $count + 1))
  sleep 1
done

avg=$(echo $total / $count | bc -l)
echo "Total runs $count"
echo "Total diff $total"
echo "Average diff to req: $avg"
# echo "Biggest difference: $biggest"
