#!bin/bash
rm -rf buildDir
mkdir buildDir
cd buildDir
cmake ../
make
mv prog ../prog
cd ..
rm -rf buildDir