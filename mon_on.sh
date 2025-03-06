# !/bin/bash

# assume the network interface is "wlan0"
sudo systemctl stop wpa_supplicant
sudo systemctl stop NetworkManager
sudo ip link set wlan0 down
sudo iw dev wlan0 set type monitor
sudo ip link set wlan0 up