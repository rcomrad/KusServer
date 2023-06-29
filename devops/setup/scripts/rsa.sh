cp ../data/sshd_config /etc/ssh/sshd_config
sudo -S chmod 0600 ../../../../.ssh/authorized_keys
sudo service ssh restart
