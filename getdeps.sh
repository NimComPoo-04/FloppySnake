#!/bin/sh

mkdir -p lib
cd lib
curl -L -O https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_linux_amd64.tar.gz
tar xvf raylib-5.0_linux_amd64.tar.gz
rm -rf raylib-5.0_linux_amd64.tar.gz
