cd ../../..
mkdir -p build
cd build/
cmake .. -DVCPKG_ROOT=/home/$KUS_BUILD_USER/vcpkg
make -j $(nproc)
cd ..
rm -rf build
cd devops/maintain/scripts
