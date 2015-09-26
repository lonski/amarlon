#!/bin/sh

sudo apt-get update -qq
sudo apt-get install libboost1.55-tools-dev

git clone https://github.com/lonski/luabind.git
cd luabind
mkdir build
cd build
cmake .. -DLUABIND_DYNAMIC_LINK=1
make -j`grep -c processor /proc/cpuinfo`

sudo cp libluabind09.so /usr/local/lib/libluabind.so

cp -r ../luabind ../../../../include

cd -