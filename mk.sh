#!/bin/bash
if [ ! -d "./build" ]; then 
    mkdir ./build
fi
cd build
cmake ..
make
cp myWebserver ../myWebserver
cd ..
#./myWebserver
