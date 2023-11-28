#!/bin/bash

n=$1
log=`echo "scale=2;l($n)/l(10)"|bc -l`
echo $log
