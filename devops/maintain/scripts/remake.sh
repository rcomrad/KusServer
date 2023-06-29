cd ..

git fetch --all
git reset --hard origin/autocommit

chmod +x remake.sh
chmod +x build.sh
./build.sh

sudo systemctl restart KusManager
