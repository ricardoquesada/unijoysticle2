#!/usr/bin/env bash

#install basic tools
apt-get update
apt-get install -y build-essential git wget make libncurses-dev flex bison python python-serial pkg-config
apt-get install -y gperf

#config
TOOLCHAIN_DL="https://dl.espressif.com/dl/"
TOOLCHAIN="xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0.tar.gz"
TOOLCHAIN_SHA256="3fe96c151d46c1d4e5edc6ed690851b8e53634041114bad04729bc16b0445156  "$TOOLCHAIN
SDK_REPO="https://github.com/espressif/esp-idf.git"
SDK_BRANCH="v3.1.3"
TARGET_USER="vagrant"
TARGET_USER_PROFILE="/home/$TARGET_USER/.profile"
DOWNLOAD_DIR="/tmp/"
INSTALL_DIR="/esp/"
BTSTACK_REPO="https://github.com/bluekitchen/btstack"
BTSTACK_BRANCH="develop"

#get toolchain
mkdir -p $DOWNLOAD_DIR
cd $DOWNLOAD_DIR
rm $TOOLCHAIN
wget $TOOLCHAIN_DL$TOOLCHAIN
TEST_HASH=$(sha256sum $TOOLCHAIN)
if [ "$TOOLCHAIN_SHA256" != "$TEST_HASH" ]
then
	echo "Wrong download. Sorry."
	echo "Expected:"
	echo $TOOLCHAIN_SHA256
	echo "Got:"
	echo $TEST_HASH
	rm $TOOLCHAIN
	exit 1
fi
mkdir -p $INSTALL_DIR
cd $INSTALL_DIR
tar -xzf $DOWNLOAD_DIR$TOOLCHAIN
rm $DOWNLOAD_DIR$TOOLCHAIN

#get sdk
cd $INSTALL_DIR
git clone --depth=1 -b $SDK_BRANCH --recursive $SDK_REPO

#get btstack
git clone --depth=1 -b $BTSTACK_BRANCH --recursive $BTSTACK_REPO -b develop
cd btstack/port/esp32
IDF_PATH=$INSTALL_DIR/esp-idf ./integrate_btstack.py


#configure path and permissions
chown $TARGET_USER:$TARGET_USER -R $INSTALL_DIR
echo "export PATH=\"\$PATH:$INSTALL_DIR/xtensa-esp32-elf/bin\"" >> $TARGET_USER_PROFILE
echo "export IDF_PATH=$INSTALL_DIR/esp-idf" >> $TARGET_USER_PROFILE
chown $TARGET_USER:$TARGET_USER $TARGET_USER_PROFILE

#usb permissions
gpasswd -a $TARGET_USER plugdev
gpasswd -a $TARGET_USER dialout
echo "To build project:"
echo "vagrant ssh"
echo "cd /vagrant/"
echo "make menuconfig"
echo "make"
echo "To flash make sure to update Vagrant file with your usb info,"
echo "then restart the vagrant machine and:"
echo "cd /vagrant/"
echo "make flash"

