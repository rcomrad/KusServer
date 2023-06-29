call scripts/key.bat
call ./maintain/scripts/autopush.bat

ssh-keygen -R %ip%
echo y | plink -ssh %server_name%@%ip% "exit"

plink.exe -batch -ssh %server_name%@%ip% -pw %server_password% sudo useradd -m -d /home/%user_name% -s /bin/bash %user_name%
plink.exe -batch -ssh %server_name%@%ip% -pw %server_password% "echo -e '%user_password%\n%user_password%\n' | sudo passwd  %user_name%"
plink.exe -batch -ssh %server_name%@%ip% -pw %server_password% sudo usermod -a -G sudo %user_name%

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S apt update && sudo apt upgrade -y" 
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (sudo -S apt install git -y)" 

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "git config --global user.email %git_name%"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "git config --global user.name %git_maile%"
@REM TODO: is sudo necessary? 
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "sudo git config --global user.email %git_name%"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "sudo git config --global user.name %git_maile%"

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "git clone -b autocommit %project_url% server"

call scripts/rsa.bat

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/setup/scripts/server_start.sh)"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (cd server/devops/setup/scripts; sudo -S ./server_start.sh %user_password% %user_name% %data_url% %domain% %domain_mail%)"

@REM ssh -o StrictHostKeyChecking=accept-new %user_name%@%ip% -i %key_dir%%ip% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/server_start.sh)"
@REM ssh -o StrictHostKeyChecking=accept-new %user_name%@%ip% -i %key_dir%%ip% "echo -e '%user_password%\n' | (cd server/devops; sudo -S ./server_start.sh %user_password%)"

echo FINISHED
pause
