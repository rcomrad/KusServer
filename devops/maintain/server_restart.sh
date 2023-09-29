cd ./scripts
sudo chmod +x autopush.bat
./autopush.bat
cd ../

cd ../setup/scripts
sudo chmod +x autopush.bat
./key.bat
cd ../../maintain

ssh kussystem "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/maintain/scripts/remake.sh)"
ssh kussystem "echo -e '%user_password%\n' | (cd  ./server/devops/maintain/scripts; sudo -S ./remake.sh)"

echo FINISHED
pause
