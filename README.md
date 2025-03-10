# deau2devi

A program used to simply disconnect target device(s) from chosen wifi network(s).

## Requirements
* Using Linux
* Having gcc
* Having a network adapter that supports monitor mode (promiscuous mode) and packet injection

## IMPORTANT NOTE
* In order to deauthentication attack using this program, you have to get the needed MAC addresses first. Before using this program, you have to use packet sniffers (e.g.: Wireshark, airodump-ng, tcpdump)
* Let `n` stands for number of AP, `m` stands for number of target device, `deau2devi` works best when `n*m == 1`, the greater value of `n*m` leads to the less effect of `deau2devi`
* To turn on/off monitor mode, I have 2 .sh files (`mon_on.sh`, `mon_off.sh`) in `programs` folder that you might use (those 2 files assume your wireless interface is `wlan0` so you should have a look inside)

## Usage

### Installation
```bash
git clone https://github.com/kmq-mqk/deau2devi.git
cd programs
gcc deau2devi.c llist.c input.c inject.c -o deau2devi
```

### How to use

After compiling as above, you can run the executable file using superuser privilege

```bash
sudo ./deau2devi <...>
```

* <...> has to include:
    * Wireless interface: `-i <interface>`
    * MAC address(es) of wifi network AP(s): `-b <AP's_MAC_address_1> <AP's_MAC_address_2> ... <AP's_MAC_address_n>` {b stands for bssid}
    * MAC address(es) of target device(s): 
        * `-a` to send deauthentication frames to broadcast (all devices on the network), OR
        * `-t <target_MAC_address_1> <target_MAC_address_2> ... <target_MAC_address_m>`
* Optional arguments for <...>:
    * `--density` - number of packet per burst
    * `--delay` - time for next burst (miliseconds)

To stop the program, use `Ctrl + C` or alternative ways to kill the process

## How it works
Based on the structure of `802.11 management frame`, the program uses information from input to construct spoofed deauthentication packets.

My packets contains radiotap header because my laptop needs it to inject packets.

The deauthentication packets will be sent spoofing from both client and router side, using some reason codes in hope of successfully disconnect the target.

## DISCLAIMER
This project is for educational and testing purposes only. Do not use this program for illegal purposes or without strict consent of the parties involved. I assume no liability and am not responsible for any misuse or damage caused by this program.