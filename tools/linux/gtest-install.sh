#!bin/sh

CC_COMPILER=gcc
CXX_COMPILER=g++

## GTEST
sudo apt-get install -qq libgtest-dev

sudo rm -rf /usr/src/gtest/build
sudo mkdir /usr/src/gtest/build
cd /usr/src/gtest/build
sudo cmake .. -DBUILD_SHARED_LIBS=1 -DCMAKE_CXX_COMPILER=$CXX_COMPILER -DCMAKE_CC_COMPILER=$CC_COMPILER
sudo make -j`grep -c processor /proc/cpuinfo`

sudo rm /usr/local/lib/libgtest.so
sudo rm /usr/local/lib/libgtest_main.so
echo "Creating gtest symlinks.."
sudo ln -s /usr/src/gtest/build/libgtest.so /usr/local/lib/libgtest.so
sudo ln -s /usr/src/gtest/build/libgtest_main.so /usr/local/lib/libgtest_main.so

cd -