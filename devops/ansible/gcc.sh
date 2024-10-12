#!/bin/bash
set -exu

version="${1:?}"

this_script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}" )" && pwd)"

apt install gcc

# https://ftp.gnu.org/gnu/gcc/gcc-14.1.0/gcc-14.1.0.tar.gz
wget "https://ftp.gnu.org/gnu/gcc/gcc-$version/gcc-$version.tar.gz"
tar -xf "./gcc-$version.tar.gz"
pushd "gcc-$version"

rm -rf obj.gcc-$version
mkdir obj.gcc-$version
pushd obj.gcc-$version
    "../gcc-$version/configure" --prefix=/usr/local/gcc-$version --disable-multilib --enable-language=c,c++
    make -j "$(nproc)"
    make install
popd
