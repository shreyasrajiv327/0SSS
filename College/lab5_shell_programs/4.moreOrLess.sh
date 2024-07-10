#!/bin/bash

echo "Invoke this shell script with two parameters A and B"
echo "It prints whether parameter A is greater or less or equal than B"
numA=$1
numB=$2
echo "Parameter A passed is $numA"
echo "Parameter B passed is $numB"

if [ $numA -eq $numB ]
then
  echo "Parameter A is equal to B"
elif [ $numA -gt $numB ]
then
  echo "Parameter A is greater than Parameter B"
else
  echo "Parameter A is less than Parameter B"
fi
