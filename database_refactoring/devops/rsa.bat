@REM ssh-keygen -t rsa -b 4096 -f %p% -N %user_password%
ssh-keygen -t rsa -b 4096 -f %keyPath%%ip% -N ""
copy %keyPath%%ip% C:\Users\Sasha\.ssh\id_rsa

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | mkdir -p ~/temp"
pscp.exe -pw %user_password% %keyPath%%ip%.pub %user_name%@%ip%:./temp/authorized_keys
pscp.exe -pw %user_password% ./sshd_config %user_name%@%ip%:./temp/sshd_config

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | mkdir -p ~/.ssh"
@REM pscp.exe -pw %user_password% %keyPath%%ip%.pub %user_name%@%ip%:./.ssh/authorized_keys
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S cp ~/temp/authorized_keys ./.ssh/authorized_keys"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S chmod a+rwx,g-rwx,o-rwx ./.ssh"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S chmod a+rwx,u-x,g-rwx,o-rwx ./.ssh/authorized_keys"

@REM pscp.exe -pw %user_password% ./sshd_config %user_name%@%ip%:/etc/ssh/sshd_config
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S cp ~/temp/sshd_config /etc/ssh/sshd_config"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S sudo service ssh restart"

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | sudo -S rm -rf ~/temp"

@REM sudo nano /etc/ssh/sshd_config
@REM sudo service ssh restart
