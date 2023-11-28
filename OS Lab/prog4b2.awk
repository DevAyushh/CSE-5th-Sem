#!/usr/bin/awk -f

# usage: ./highest_tot.awk inFile

BEGIN {FS="|"; t1=0;t2=0;t3=0}; NR>1 {t1+=$3;t2+=$4;t3+=$5}; END {print "Average: ",t1/(NR-1),t2/(NR-1),t3/(NR-1)}
