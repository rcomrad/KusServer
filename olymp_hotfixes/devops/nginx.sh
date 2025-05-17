sudo -S apt install curl gnupg2 ca-certificates lsb-release ubuntu-keyring -y
curl https://nginx.org/keys/nginx_signing.key | gpg --dearmor | sudo tee /usr/share/keyrings/nginx-archive-keyring.gpg >/dev/null
gpg --dry-run --quiet --no-keyring --import --import-options import-show /usr/share/keyrings/nginx-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/nginx-archive-keyring.gpg] http://nginx.org/packages/ubuntu `lsb_release -cs` nginx" | sudo tee /etc/apt/sources.list.d/nginx.list
echo -e "Package: *\nPin: origin nginx.org\nPin: release o=nginx\nPin-Priority: 900\n" sudo tee /etc/apt/preferences.d/99nginx
sudo apt update
sudo apt install nginx -y
sudo systemctl restart nginx

sudo ./ssl.sh
sudo ./ssl.sh
sudo cp default.conf /etc/nginx/conf.d/default.conf

sudo nginx -s reload

# sudo systemctl status nginx
