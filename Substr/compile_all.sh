#!/bin/bash

SOURCES=*.C
for source in $SOURCES
do
  ./compile.sh $source
done
