#!/bin/sh

# For Vagrant provisioning - Check root and change to vagrant user
if [ $(id -u) = 0 ]; then
   USER='vagrant'
fi

sudo apt-get update &&  sudo apt-get -y install wget make

# Install GNU ARM toolchain
echo -e "\n\nInstalling GNU ARM toolchain..."
sudo apt-get -y install lib32ncurses5
cd /home/$USER && wget -nv https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
cd /usr/local
sudo tar xjf /home/$USER/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
rm /home/$USER/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2

# Install OpenOCD
# Reference: http://gnuarmeclipse.github.io/openocd/install/
echo -e "\n\nInstalling OpenOCD..."
cd /home/$USER && wget -nv https://github.com/gnuarmeclipse/openocd/releases/download/gae-0.10.0-20161028/gnuarmeclipse-openocd-debian64-0.10.0-201610281609-dev.tgz
sudo mkdir -p /opt/gnuarmeclipse
cd /opt/gnuarmeclipse
sudo tar xf /home/$USER/gnuarmeclipse-openocd-debian64-0.10.0-201610281609-dev.tgz
rm /home/$USER/gnuarmeclipse-openocd-debian64-0.10.0-201610281609-dev.tgz

# Add udev rule for OpenOCD
echo -e "\n\nAdding a udev rule for OpenOCD..."
sudo cp /opt/gnuarmeclipse/openocd/0.10.0-201610281609-dev/contrib/99-openocd.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo usermod -aG plugdev $USER

# Install QEMU
# Reference: http://gnuarmeclipse.github.io/qemu/install/
echo -e "\n\nInstalling QEMU..."
cd /home/$USER && wget -nv https://github.com/gnuarmeclipse/qemu/releases/download/gae-2.8.0-20161227/gnuarmeclipse-qemu-debian64-2.8.0-201612271623-dev.tgz
cd /opt/gnuarmeclipse
sudo tar xf /home/$USER/gnuarmeclipse-qemu-debian64-2.8.0-201612271623-dev.tgz
rm /home/$USER/gnuarmeclipse-qemu-debian64-2.8.0-201612271623-dev.tgz

# Install J-Link
# Reference: http://gnuarmeclipse.github.io/debug/jlink/install/
# Used personal Dropbox link as JEGGER homepage requires addtional sign-in
echo -e "\n\nInstalling J-Link..."
cd /home/$USER && wget -nv https://dl.dropboxusercontent.com/u/78819851/gnu_arm_eclipse/JLink/JLink_Linux_V612e_x86_64.deb
sudo dpkg -i /home/$USER/JLink_Linux_V612e_x86_64.deb
rm /home/$USER/JLink_Linux_V612e_x86_64.deb

# Install Oracle JDK for Eclipse
# http://askubuntu.com/questions/190582/installing-java-automatically-with-silent-option
echo -e "\n\nInstalling Oracle JRE..."
sudo apt-get install -y software-properties-common
sudo add-apt-repository ppa:webupd8team/java && sudo apt-get update
echo "oracle-java8-installer shared/accepted-oracle-license-v1-1 select true" | debconf-set-selections
echo "oracle-java8-installer shared/accepted-oracle-license-v1-1 seen true" | debconf-set-selections
sudo apt-get install -y oracle-java8-installer
sudo apt install -y oracle-java8-set-default

# Install GNU ARM Eclipse
echo -e "\n\nInstalling GNU ARM Eclipse..."
cd /home/$USER && wget -nv https://dl.dropboxusercontent.com/u/78819851/gnu_arm_eclipse/Eclipse_20160113/eclipse-cpp-mars-2-linux-gtk-x86_64.tar.gz
cd /opt && sudo tar -xf /home/$USER/eclipse-cpp-mars-2-linux-gtk-x86_64.tar.gz
rm /home/$USER/eclipse-cpp-mars-2-linux-gtk-x86_64.tar.gz
sudo mv ./eclipse ./eclipse_gnuarm

# Java Cryptography Extension (JCE) Unlimited Strength Jurisdiction Policy Files 8
cd /home/$USER && wget -nv https://dl.dropboxusercontent.com/u/78819851/gnu_arm_eclipse/jce_policy-8.zip
sudo apt-get install unzip 
unzip jce_policy-8.zip
sudo mv UnlimitedJCEPolicyJDK8/* /usr/lib/jvm/java-8-oracle/jre/lib/security/
rm -r UnlimitedJCEPolicyJDK8/
rm jce_policy-8.zip

# Install GNU ARM Eclipse Plugin
echo -e "\n\nInstalling GNU ARM Eclipse Plugin..."
/opt/eclipse_gnuarm/eclipse \
-clean -purgeHistory \
-application org.eclipse.equinox.p2.director \
-noSplash \
-repository \
http://download.eclipse.org/releases/mars,\
http://gnuarmeclipse.sourceforge.net/updates \
-installIUs \
org.eclipse.cdt.feature.group,\
ilg.gnuarmeclipse.templates.ad.feature.group,\
ilg.gnuarmeclipse.codered.feature.group,\
ilg.gnuarmeclipse.managedbuild.cross.feature.group,\
ilg.gnuarmeclipse.templates.freescale.feature.group,\
ilg.gnuarmeclipse.templates.cortexm.feature.group,\
ilg.gnuarmeclipse.debug.gdbjtag.jlink.feature.group,\
ilg.gnuarmeclipse.debug.gdbjtag.openocd.feature.group,\
ilg.gnuarmeclipse.packs.feature.group,\
ilg.gnuarmeclipse.debug.gdbjtag.qemu.feature.group,\
ilg.gnuarmeclipse.templates.stm.feature.group

# Restore Eclipse settings
#cd /home/$USER && wget -nv https://dl.dropboxusercontent.com/u/78819851/gnu_arm_eclipse/Eclipse_20160113/eclipse_settings.tar.gz
#mkdir -p /home/$USER/.eclipse
#cd /home/$USER/.eclipse && sudo tar -xf /home/$USER/eclipse_settings.tar.gz
#rm /home/$USER/eclipse_settings.tar.gz /home/$USER/eclipse-cpp-mars-2-linux-gtk-x86_64.tar.gz
#sudo chown -R $USER:$USER /home/$USER/.eclipse
