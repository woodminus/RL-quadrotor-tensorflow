#!/bin/bash +

#sudo apt-get update
#sudo apt-get upgrade -y

##sudo add-apt-repository ppa:openjdk-r/ppa
##sudo apt-get update
##sudo apt-get install openjdk-8-jdk
##echo "change java to 8"

sudo apt-get install -y build-essential python-pip python-dev git python-numpy swig python-dev default-jdk zip zlib1g-dev cmake

## Blacklist Noveau which has some kind of conflict with the nvidia driver
##echo -e "blacklist nouveau\nblacklist lbm-nouveau\noptions nouveau modeset=0\nalias nouveau off\nalias lbm-nouveau off\n" | sudo tee /etc/modprobe.d/blacklist-nouveau.conf
##echo options nouveau modeset=0 | sudo tee -a /etc/modprobe.d/nouveau-kms.conf
##sudo update