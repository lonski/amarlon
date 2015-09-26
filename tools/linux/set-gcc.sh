#!/bin/sh

GCC_VERSION=$1

sudo update-alternatives --remove-all gcc
sudo update-alternatives --remove-all g++

sudo apt-get install -qq gcc-$GCC_VERSION g++-$GCC_VERSION

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-$GCC_VERSION 20 --slave /usr/bin/g++ g++ /usr/bin/g++-$GCC_VERSION
sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc 30
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 30
sudo update-alternatives --set cc /usr/bin/gcc
sudo update-alternatives --set c++ /usr/bin/g++

echo `gcc --version`
