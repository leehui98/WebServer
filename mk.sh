#!/bin/bash
cd build
cmake ..
make
cp myWebserver ../myWebserver
cd ..
#./myWebserver
