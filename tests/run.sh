# !/bin/bash
for (( c=1; c<=130; c++ ))
do
   echo "=== $c ==="  
   ./bin/$1 $c
done
