#!/usr/bin/awk -f

# usage: ./highest_tot.awk inFile

BEGIN {FS="|"; t1=0;t2=0;t3=0}; NR>1 {if(t1<$3) {t1=$3; s1=$2};if(t2<$4) {t2=$4; s2=$2};if(t3<$5) {t3=$5; s3=$2}}; END {printf"SUB1: %s --> %d\nSUB2: %s ---> %d\nSUB3: %s --> %d\n", s1,t1,s2,t2,s3,t3}
