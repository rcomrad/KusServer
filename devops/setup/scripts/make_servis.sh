sudo cp ../data/KusManager.service /etc/systemd/system/KusManager.service
sudo chmod 640 /etc/systemd/system/KusManager.service
sudo systemctl daemon-reload
sudo systemctl restart KusManager
sudo sed -i 's/user_name/'$1'/g' /etc/systemd/system/KusManager.service
