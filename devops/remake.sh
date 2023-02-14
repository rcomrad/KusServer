cd ..

git fetch --all
git reset --hard origin/autocommit

cd devops
chmod +x ./build.sh
./build.sh

sudo systemctl restart KusManager
