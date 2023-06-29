cd ../../../..

sudo swapoff -a
sudo rm -f /swapfile
sudo fallocate -l 8G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

sudo -S apt install gcc g++ make curl zip unzip tar pkg-config autoconf postgresql net-tools cmake build-essential -y

# pascal compiler and python
sudo -S apt install fp-compiler python -y

git clone $3 data
git config --global --add safe.directory /home/$2/server
git config --global --add safe.directory /home/$2/data

cd server/devops/setup/scripts
# install cmake
sudo chmod +x cmake_install.sh
sudo ./cmake_install.sh

cd ../../../..
git clone https://github.com/Microsoft/vcpkg.git
cd ./vcpkg
./bootstrap-vcpkg.sh
./vcpkg install boost:x64-linux
./vcpkg install crow:x64-linux
./vcpkg install libpqxx:x64-linux

cd ../server/bin
printf "0 postgres postgres $1 public\n1 journal_db journal_user $1 journal\n" > database.pass
printf "default /home/$2/data/" > paths.path

cd ../devops/setup/scripts
sudo cp ../data/pg_hba.conf /etc/postgresql/12/main/pg_hba.conf
sudo -u postgres psql -c "ALTER USER postgres password '$1';"

# TODO: add journal_user and database from start
sudo -u postgres psql -c "CREATE USER $2;"
sudo -u postgres psql -c "ALTER USER $2 password '$1';"
sudo -u postgres psql -c "CREATE DATABASE journal_db;"

# add demon
sudo chmod +x make_servis.sh
sudo ./make_servis.sh

# nginx
sudo chmod +x nginx.sh
sudo ./nginx.sh $4 $5

sudo apt update && sudo apt upgrade -y

# ssh-keys
sudo chmod +x rsa.sh
sudo ./rsa.sh

# zsh
cd ..
sudo chmod +x zsh.sh

# compile
cd ../maintain/scripts
sudo chmod +x remake.sh
sudo ./remake.sh
