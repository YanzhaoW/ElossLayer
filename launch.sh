#! /bin/sh

##stop on error
set -e

mkdir -p build
mkdir -p out
cd build
cmake ..
make -j 10
cd ..

if [ -n "$1" ]
then
    ./build/TestEm18 ./$1
else
    ./build/TestEm18
fi

root -l -q root2csv.cc
mv output.root ./out/