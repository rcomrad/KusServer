git clone https://github.com/openssl/openssl

cd openssl
mkdir build
cd build
../Configure
make

sudo make install

cd ../..
rm -rf openssl

git clone https://github.com/Kitware/CMake

cd CMake
mkdir build
cd build
../bootstrap
make

sudo make install

cd ../..
rm -rf CMake
