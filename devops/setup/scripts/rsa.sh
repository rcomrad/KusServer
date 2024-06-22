cp ../data/sshd_config /etc/ssh/sshd_config
sudo -S chmod 0600 ../../../../.ssh/authorized_keys
#  echo "PasswordAuthentication no" > /etc/ssh/sshd_config.d/50-cloud-init.conf
sudo service ssh restart
