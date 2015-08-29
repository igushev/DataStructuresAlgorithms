#!/bin/bash

source=$1
binary=`echo $source | awk -F "." {'print $1'}`
echo Compiling $binary...
g++ -o $binary $source

