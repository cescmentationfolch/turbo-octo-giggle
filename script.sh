#!/bin/bash

for file in ./examples/*.asl; 
do
  error=`echo $file | sed 's/asl/err/'`
  if [ -f $error ]; then
    echo ${file}
    ./asl/asl < $file > out
    echo `diff out $error`
    rm out
    echo ""
  fi
done;
