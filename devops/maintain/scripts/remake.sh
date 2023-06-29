git fetch --all
git reset --hard origin/autocommit

sudo chmod +x remake.sh
sudo chmod +x build.sh
./build.sh

sudo systemctl restart KusManager
