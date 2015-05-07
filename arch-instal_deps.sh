#!/bin/bash

sudo pacman -S sdl glu gtest mercurial

hg clone https://bitbucket.org/jice/libtcod
cd libtcod

make -f makefiles/makefile-linux debug

mkdir ../lib

cp ./libtcod_debug.so ../lib/libtcod_debug.so
cp ./libtcodxx_debug.so ../lib/libtcodxx_debug.so
cp ./libtcod_debug.so ../lib/libtcod.so
cp ./libtcodxx_debug.so ../lib/libtcodxx.so

cd ../lib

ln -s libtcod.so libtcod.so.1
ln -s libtcodxx.so libtcodxx.so.1

