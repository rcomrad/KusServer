cp ./sshd_config /etc/ssh/sshd_config

cd ../..
sudo -S chmod 0600 ./.ssh/authorized_keys

sudo service ssh restart

# sudo nano /etc/ssh/sshd_config
# ls -a