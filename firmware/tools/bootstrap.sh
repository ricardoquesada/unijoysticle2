#!/usr/bin/env bash

#install basic tools
apt-get install -y build-essential git wget libusb-1.0-0-dev pkg-config

#config
TARGET_USER="vagrant"
TARGET_USER_PROFILE="/home/vagrant/.profile"
#from Makefile
INSTALL_DIR="/home/$TARGET_USER/src/"
BTSTACK_REPO="https://github.com/bluekitchen/btstack"

#get sdk
mkdir -p $INSTALL_DIR
cd $INSTALL_DIR
git clone --depth=1 --recursive $BTSTACK_REPO

#configure path and permissions
chown $TARGET_USER:$TARGET_USER -R $INSTALL_DIR

