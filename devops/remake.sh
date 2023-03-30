cd ..

git fetch --all
git reset --hard origin/autocommit

cd devops
chmod +x ./build.sh
./build.sh

cp Server.exe Server0.exe

sudo systemctl restart KusManager
