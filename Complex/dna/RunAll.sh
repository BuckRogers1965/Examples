#!/bin/bash

filename=`date +"RunAll%Y%m%d%H%M%S.txt"` 

exec > results/$filename 2>&1

echo Begin Run All `date +"%Y%m%d%H%M%S"`
echo

echo Saving all results to $filename
echo

time ./bp.sh 

echo End Run All `date +"%Y%m%d%H%M%S"`
