#!/bin/bash

echo "This shell scripts prints param2 numbers starting from param1"
startingnum=$1
numseq=$2
echo "Starting number passed is $startingnum"
echo "Number sequence passed is $numseq"
while [ $numseq -gt 0 ]
do
   echo "$startingnum"
   startingnum=$(( $startingnum + 1))
   numseq=$(( $numseq - 1 ))
done

