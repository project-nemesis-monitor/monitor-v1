#!/bin/bash


sudo apt-get update
sudo apt-get install -y libmariadb-dev mariadb-server

sudo mysql -e "CREATE DATABASE nemesisbdd;"
sudo mysql -e "CREATE USER 'admin'@'localhost' IDENTIFIED BY '2002';"
sudo mysql -e "GRANT ALL PRIVILEGES ON nemesisbdd.* TO 'admin'@'localhost';"
sudo mysql -e "FLUSH PRIVILEGES;"

gcc -Wall server/main.c server/includes/liblinux.c server/includes/reactwthbdd.c -o ./output/server `mariadb_config --cflags --libs`

service_file="/etc/systemd/system/monitor-nemesis.service"
service_content="[Unit]
Description=Monitor Nemesis Service
After=network.target mariadb.service

[Service]
Type=simple
ExecStart=$(realpath ./output/server)

[Install]
WantedBy=multi-user.target
"

echo "$service_content" | sudo tee "$service_file" > /dev/null

# Recharger systemd
sudo systemctl daemon-reload

# Activer et démarrer le service
sudo systemctl enable monitor-nemesis.service
sudo systemctl start monitor-nemesis.service
