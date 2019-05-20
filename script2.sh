#!/bin/bash

for file in ./examples/*.asl; 
do
  entrada=`echo $file | sed 's/asl/in/'`
  sortida=`echo $file | sed 's/asl/out/'`
  if [ -f $entrada ]; then
    fitxer=`echo $file | sed 's/asl/aux.t/'`
    echo ${file}
    ./asl/asl < $file > $fitxer 
    ./tvm/tvm $fitxer < $entrada > out.out
    echo `diff out.out $sortida`
    rm out.out
    echo ""
  fi
done;
