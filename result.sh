#!/bin/sh
echo -e "m\tn\tsize\tbitpersym\ttimeofget\tptimeofget\ttimeofrank\tptimeofrank\n" > result.txt
for i in {20..30}
	do
		echo $i
		./test_rrr $i >> result.txt
	done
