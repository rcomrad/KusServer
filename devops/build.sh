cd ..
mkdir build
cd build/
cmake .. -DVCPKG_ROOT=/home/rcomrad/vcpkg
make
cd ..
rm -rf build
