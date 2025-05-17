#!/bin/bash
set -exu

sudo apt-get install libssl-dev #openssl
sudo apt-get install openssh-server build-essential wget make gcc g++ -y
sudo systemctl enable ssh --now
sudo systemctl start ssh
sudo systemctl restart sshd

wget https://github.com/Kitware/CMake/releases/download/v3.27.8/cmake-3.27.8.tar.gz
tar -xf ./cmake-3.27.8.tar.gz
pushd ./cmake-3.27.8
./bootstrap
sudo make -j "$(nproc)"
sudo make install
popd
