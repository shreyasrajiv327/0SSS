#!/bin/bash

echo "Let me execute some commands for you!!!"
pwd
ls
mypid=$$
echo "My pid is $mypid"
echo “Bye, Bye, I am going to kill myself”
kill -9 $mypid
