#!/bin/bash

# This is OS_SS Lab 5
echo "Let us learn about shell variables!!!"
name="Mouli"
echo $name
echo "My name is $name"
echo $NAME   # This is an environment variable, machine name
echo "Name of this machine is $NAME"
echo "Let me make your name readonly"
name="Mouli Sankaran"   # Assign a different value to the existing shell variable
echo $name
echo "Now, my full name: $name"
readonly name
name="Another name"  #bash gives an error
echo "Readonly variables are premanent, they cannot be unset or deleted directly"
unset name  # It gives an error: Readonly variables cannot be unset

# Readonly variables remain untill the shell process teminates (close the terminal)
full_name="Chandramouleeswaran Sankaran"
echo "Now, my full name is $full_name"
echo "name and full_name are local variables"
unset full_name  # It removes this variable
echo $full_name  # Prints a null string
# All these variables are local to this shell program
# When you open another terminal these variables won't be available and cannot
# print the values set here.
# Open another window and you can see the same output for the below command
echo $NAME # But echo $name will not have any value set 

echo "Let us learn about the global Environment variables now ..."
env  # This commands gives the list of global env variables and their values

# To see the contents of the PATH env variable give the below command
echo $PATH


# There are some special variables: 
# $ is one them which gives the PID of the current shell
echo $$

echo "Let us try to get the parameters passed to this script with double quotes"
echo "Now, invoke this script with two parameters"
# variables.sh param1 param2
# The below commands give you the parameters passed to this script program

echo "number of parameters passed: $#"
echo "The first parameter passed: $1"
echo "The second parameter passed: $2"