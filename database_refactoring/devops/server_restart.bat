call key.bat
call autopush.bat

ssh-keygen -R %ip%
echo y | plink -ssh %user_name%@%ip% "exit"

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/remake.sh)"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (cd  ./server/devops/; sudo -S ./remake.sh)"

@REM ssh -o StrictHostKeyChecking=accept-new %user_name%@%ip% -i %key_dir%%ip% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/remake.sh)"
@REM ssh -o StrictHostKeyChecking=accept-new %user_name%@%ip% -i %key_dir%%ip% "echo -e '%user_password%\n' | (cd  ./server/devops/; sudo -S ./remake.sh)"

echo FINISHED
pause
