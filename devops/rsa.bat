call D:\keys\server.bat

set p=D:\keys\%ip%

ssh-keygen -t rsa -b 4096 -f %p% -N %user_password%
copy %p% C:\Users\Sasha\.ssh\id_rsa

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "mkdir -p ~/.ssh"
pscp.exe -pw %user_password% %p%.pub %user_name%@%ip%:./.ssh/authorized_keys
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "chmod a+rwx,g-rwx,o-rwx ./.ssh"
plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "chmod a+rwx,u-x,g-rwx,o-rwx ./.ssh/authorized_keys"

pause


# sudo nano /etc/ssh/sshd_config
# sudo service ssh restart

