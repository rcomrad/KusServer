#!/bin/bash
set -exu

version="${1:?}"

sudo apt update
sudo apt install -y libgmp-dev libmpfr-dev libmpc-dev build-essential flex bison libisl-dev
sudo apt upgrade

this_script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}" )" && pwd)"

sudo apt install gcc

# https://ftp.gnu.org/gnu/gcc/
# https://ftp.fu-berlin.de/gnu/gcc/
# https://mirror.ibiblio.org/gnu/gcc/
# https://mirror.csclub.uwaterloo.ca/gnu/gcc/

# https://ftp.gnu.org/gnu/gcc/gcc-14.1.0/gcc-14.1.0.tar.gz
wget "https://ftp.wayne.edu/gnu/gcc/gcc-$version/gcc-$version.tar.gz"
tar -xf "./gcc-$version.tar.gz"
pushd "gcc-$version"

rm -rf obj.gcc-$version
mkdir obj.gcc-$version
pushd obj.gcc-$version
    ../configure --prefix=/usr/local/gcc-$version --disable-multilib --enable-language=c,c++
    make -j "$(nproc)"
    sudo make install
popd
