#!/bin/bash

echo "Add two numbers passed to the script"
echo "Parameters passed are $1 and $2"
num1=$1
num2=$2
echo "Values in num1 and num2 are $num1 and $num2"
let sum=($num1 + $num2)
echo "The sum of the numbers passed is $sum"