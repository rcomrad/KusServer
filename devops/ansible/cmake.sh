#!/bin/bash
set -exu

wget https://github.com/Kitware/CMake/releases/download/v3.27.8/cmake-3.27.8.tar.gz
tar -xf ./cmake-3.27.8.tar.gz
pushd ./cmake-3.27.8
    ./bootstrap
    sudo make -j "$(nproc)"
    sudo make install
popd
rm -rf cmake-3.27.8
rm -rf cmake-3.27.8.tar.gz
