# !/bin/bash

# assume the network interface is "wlan0"
sudo ip link set wlan0 down
sudo iw dev wlan0 set type managed
sudo ip link set wlan0 up
sudo systemctl restart NetworkManager