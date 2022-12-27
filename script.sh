#!/usr/bin/env bash


counter=0


while [ $counter -lt $1 ]
	do
	./a.out  | grep eating | wc -l
	printf "\n---------------TEST $counter----------------------\n"
	sleep 0.5
	((counter++))
done