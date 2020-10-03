#!/bin/sh

echo $#
echo $1
while [ $# -eq 1 ]
do
	cat /proc/$1/status 
	sleep 1
done
