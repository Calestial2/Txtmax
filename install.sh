#!/bin/bash

git clone https://github.com/Calestial2/Txtmax.git
cd Txtmax 
cd src
make
make clean 
echo "Txtmax is installed. Type ./txtmax to use it"
