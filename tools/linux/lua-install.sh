#!bin/sh

sudo apt-get update -qq
sudo apt-get install libreadline-dev -qq

rm -rf lua
wget http://www.lua.org/ftp/lua-5.3.1.tar.gz
tar -xvf lua-5.3.1.tar.gz
rm lua-5.3.1.tar.gz
mv lua-5.3.1 lua
cd lua
make linux
sudo make linux install

export LUA_PATH="`pwd`/src"

echo "\n\nLUA_PATH:"
echo $LUA_PATH
echo "\n"

cd -