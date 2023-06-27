# sudo apt-get install sshpass

. /home/sanya/keys/server.sh
sh -e ./autopush.bat

# echo $user_password
# echo sshpass -p $user_password ssh -o StrictHostKeyChecking=no $user_name@$ip "echo -e '$user_password\n' | (sudo -S chmod +x ./server/devops/maintain/scripts/remake.sh)"

sshpass -p $user_password ssh -o StrictHostKeyChecking=no $user_name@$ip "echo -e '$user_password\n' | (sudo -S chmod +x ./server/devops/maintain/scripts/remake.sh)"
sshpass -p $user_password ssh -o StrictHostKeyChecking=no $user_name@$ip "echo -e '$user_password\n' | (cd  ./server/devops/maintain/scripts; sudo -S ./remake.sh)"

echo FINISHED

