sudo apt install snapd -y
sudo snap install core
sudo snap refresh core
sudo snap install --classic certbot
sudo ln -s /snap/bin/certbot /usr/bin/certbot

certbot run -n --nginx --agree-tos -d $1 -m $2 --redirect
