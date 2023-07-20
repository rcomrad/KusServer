cd ./scripts
call autopush.bat
cd ../

cd ../setup/scripts
call key.bat
cd ../../maintain

ssh-keygen -R %ip%
echo y | plink -ssh %user_name%@%ip% "exit"

@REM plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/maintain/scripts/remake.sh)"
@REM plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (cd  ./server/devops/maintain/scripts/; sudo -S ./remake.sh)"

ssh -o StrictHostKeyChecking=accept-new %user_name%@%ip% -i %key_dir%%ip% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/maintain/scripts/remake.sh)"
ssh -o StrictHostKeyChecking=accept-new %user_name%@%ip% -i %key_dir%%ip% "echo -e '%user_password%\n' | (cd  ./server/devops/maintain/scripts; sudo -S ./remake.sh)"

echo FINISHED
pause
