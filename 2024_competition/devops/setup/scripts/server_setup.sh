cd ../../../..

sudo swapoff -a
sudo rm -f /swapfile
sudo fallocate -l 8G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

sudo -S apt install gcc g++ make curl zip unzip tar pkg-config autoconf postgresql net-tools cmake build-essential gnumeric -y
sudo -S apt install texlive texinfo texlive-fonts-recommended texlive-latex-extra texlive-lang-cyrillic latex-cjk-all -y

# pascal compiler and python
sudo -S apt install fp-compiler python -y

sudo -H -u $2 git clone $3 data
git config --global --add safe.directory /home/$2/server
git config --global --add safe.directory /home/$2/data

cd server/devops/setup/scripts
# install cmake
sudo chmod +x cmake_install.sh
sudo ./cmake_install.sh

cd ../../../..
sudo -H -u $2 git clone https://github.com/Microsoft/vcpkg.git
cd ./vcpkg
sudo -H -u $2 ./bootstrap-vcpkg.sh
sudo -H -u $2 ./vcpkg install boost-filesystem:x64-linux
sudo -H -u $2 ./vcpkg install crow:x64-linux
sudo -H -u $2 ./vcpkg install libpqxx:x64-linux
sudo -H -u $2 ./vcpkg install mailio:x64-linux

cd ../server
sudo -H -u $2 printf "set(VCPKG_ROOT \"/home/$2/vcpkg/\")" > vcpkg_path.cmake

cd ./config
sudo -H -u $2 printf "0 postgres postgres $1 public\n1 journal_db $2 $1 journal\n" > database.pass
sudo -H -u $2 printf "default = /home/$2/data/" > path.conf
sudo -H -u $2 printf "$4" > url.pass
#sudo -H -u $2 printf " " > key_role.pass
sudo -H -u $2 printf "$6  $7" > mail.pass

cd ../devops/setup/scripts
sudo cp ../data/pg_hba.conf /etc/postgresql/14/main/pg_hba.conf
sudo -u postgres psql -c "ALTER USER postgres password '$1';"

# TODO: add journal_user and database from start
sudo -u postgres psql -c "CREATE USER $2;"
sudo -u postgres psql -c "ALTER USER $2 password '$1';"
sudo -u postgres psql -c "CREATE DATABASE journal_db;"

# add demon
sudo chmod +x make_servis.sh
sudo ./make_servis.sh $2

# nginx
sudo chmod +x nginx.sh
sudo ./nginx.sh $4 $5 $2

sudo apt update && sudo apt upgrade -y

# zsh
sudo chmod +x zsh.sh
sudo ./zsh.sh $2

# ssh-keys
sudo chmod +x rsa.sh
sudo ./rsa.sh

# compile
cd ../../maintain/scripts
sudo chmod +x remake.sh
sudo ./remake.sh

sudo apt install mc
