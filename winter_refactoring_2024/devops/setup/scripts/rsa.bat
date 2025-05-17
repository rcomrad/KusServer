call key.bat
@REM ssh-key setup
@REM ssh-keygen -t rsa -b 4096 -f %p% -N %user_password%
ssh-keygen -t rsa -b 4096 -f %keyPath%%ip% -N ""
copy %keyPath%%ip% %win_ssh_dir%\id_rsa

plink.exe -batch -ssh %user_name%@%ip% -pw %user_password% "echo -e '%user_password%\n' | mkdir -p ~/.ssh"
pscp.exe -pw %user_password% %keyPath%%ip%.pub %user_name%@%ip%:./.ssh/authorized_keys
