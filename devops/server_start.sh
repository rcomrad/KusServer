cd ../..
git config --global --add safe.directory ./server
sudo -S apt install gcc g++ make curl zip unzip tar pkg-config autoconf postgresql net-tools -y

cd server
git switch autocommit
git config --global --add safe.directory /home/rcomrad/server

cd devops
# install cmake
sudo chmod +x ./cmake_install.sh
sudo ./cmake_install.sh

cd ../..
git clone https://github.com/Microsoft/vcpkg.git
cd ./vcpkg
./bootstrap-vcpkg.sh
./vcpkg install crow:x64-linux
./vcpkg install libpqxx:x64-linux

cd ../server/bin
printf "$1\n$1\n" > database.pass

cd ../devops
sudo cp pg_hba.conf /etc/postgresql/12/main/pg_hba.conf
sudo -u postgres psql -c "ALTER USER postgres password '$1';"

# TODO: add journal_user and database from start
sudo -u postgres psql -c "CREATE USER $2;"
sudo -u postgres psql -c "ALTER USER $2 password '$1';"
sudo -u postgres psql -c "CREATE DATABASE journal_db;"

# sudo -u postgres psql -c "CREATE USER journal_user;"
# sudo -u postgres psql -c "ALTER USER journal_user password '$1';"
# 

# add demon
sudo chmod +x make_servis.sh
sudo ./make_servis.sh

sudo chmod +x nginx.sh
sudo ./nginx.sh

# compile
sudo chmod +x remake.sh
sudo ./remake.sh

sudo apt update || sudo apt upgrade -y

# TODO: add paths.path
# TODO: new database.pass
# TODO: create data folder
