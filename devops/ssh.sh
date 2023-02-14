#sudo apt-get install snap
sudo apt -y install snapd
sudo snap install core
sudo snap refresh core
sudo apt-get remove certbot
sudo snap install --classic certbot
sudo ln -s /snap/bin/certbot /usr/bin/certbot
sudo systemctl stop KusManager
sudo certbot certonly --standalone
sudo systemctl start KusManager
sudo cp /etc/letsencrypt/live/kusjournal.ru/{cert,chain,privkey,fullchain}.pem ~
sudo chown `whoami` ~/*.pem

# kusjournal.ru
