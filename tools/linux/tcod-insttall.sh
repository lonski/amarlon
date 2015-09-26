#!/bin/sh

##LIBTCOD

REVISION=1edf96d

rm -rf libtcod
hg clone https://bitbucket.org/libtcod/libtcod -r $REVISION
cd libtcod
make -f makefiles/makefile-linux debug

sudo rm /usr/local/lib/libtcod_debug.so
sudo cp ./libtcod_debug.so /usr/local/lib/libtcod_debug.so

sudo rm /usr/local/lib/libtcodxx_debug.so
sudo cp ./libtcodxx_debug.so /usr/local/lib/libtcodxx_debug.so

sudo rm /usr/local/lib/libtcod.so
sudo cp ./libtcod_debug.so /usr/local/lib/libtcod.so

sudo rm /usr/local/lib/libtcodxx.so
sudo cp ./libtcodxx_debug.so /usr/local/lib/libtcodxx.so

cd -
rm -rf libtcod

