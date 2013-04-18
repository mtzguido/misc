#!/bin/bash

echo -ne "s\l\t"
for ((j=1; j<=10; j++)); do
	echo -ne "${j}\t"
done
echo
echo "-------------------------------------------"

for ((i=1; i<=6; i++)); do
	echo -ne "${i} |\t"
	for ((j=1; j<=10; j++)); do
		len=$(./magic $i $j | wc -c)
		echo -ne "$((len-1))\t" # subtract 1 for the newline
	done
	echo
done
