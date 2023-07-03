#!/bin/bash

export KUS_BUILD_USER=$(cut -d / -f 3 <<< $(pwd))
echo building for user: $KUS_BUILD_USER

cd ../../..
mkdir -p build
cd build/
cmake .. -DVCPKG_ROOT=/home/$KUS_BUILD_USER/vcpkg
# make -j $(nproc)
make
cd ..
rm -rf build
cd devops/maintain/scripts
