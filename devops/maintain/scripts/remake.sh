#!/bin/bash

export KUS_BUILD_USER=$(cut -d / -f 3 <<< $(pwd))
echo building for user: $KUS_BUILD_USER

sudo -H -u $KUS_BUILD_USER git fetch --all
sudo -H -u $KUS_BUILD_USER git reset --hard origin/autocommit

sudo chmod +x remake.sh
sudo chmod +x build.sh
sudo -H -u $KUS_BUILD_USER ./build.sh

sudo systemctl restart KusManager
