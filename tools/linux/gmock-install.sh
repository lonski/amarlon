#!bin/sh

CC_COMPILER=gcc
CXX_COMPILER=g++

##GMOCK
sudo apt-get install -qq google-mock

sudo rm -rf /usr/src/gmock/build
sudo mkdir /usr/src/gmock/build
cd /usr/src/gmock/build
sudo cmake .. -DBUILD_SHARED_LIBS=1 -DCMAKE_CXX_COMPILER=$CXX_COMPILER -DCMAKE_CC_COMPILER=$CC_COMPILER
sudo make -j`grep -c processor /proc/cpuinfo`

sudo rm /usr/local/lib/libgmock.so
sudo rm /usr/local/lib/libgmock_main.so
echo "Creating gmock symlinks.."
sudo ln -s /usr/src/gmock/build/libgmock.so /usr/local/lib/libgmock.so
sudo ln -s /usr/src/gmock/build/libgmock_main.so /usr/local/lib/libgmock_main.so

cd -
