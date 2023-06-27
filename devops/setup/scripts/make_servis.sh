sudo cp ../data/KusManager.service /etc/systemd/system/KusManager.service
sudo chmod 640 /etc/systemd/system/KusManager.service
sudo systemctl daemon-reload
sudo systemctl restart KusManager
