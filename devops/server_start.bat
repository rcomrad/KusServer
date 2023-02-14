call key.bat
call autopush.bat

ssh-keygen -R %ip%
echo y | plink -ssh %server_name%@%ip% "exit"

plink.exe -batch -ssh %server_name%@%ip% -pw %server_password% sudo useradd -m -d /home/%user_name% -s /bin/bash %user_name%
plink.exe -batch -ssh %server_name%@%ip% -pw %server_password% "echo -e '%user_password%\n%user_password%\n' | sudo passwd  %user_name%"
plink.exe -batch -ssh %server_name%@%ip% -pw %server_password% sudo usermod -a -G sudo %user_name%

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S apt update || sudo apt upgrade -y" 
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (sudo -S apt install git)" 

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "git clone %project_url% server"

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (sudo -S chmod +x ./server/devops/server_start.sh)"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | (cd server/devops; sudo -S ./server_start.sh %user_password%)"

echo FINISHED
pause
