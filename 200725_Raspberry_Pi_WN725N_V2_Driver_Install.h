RASPBERRY PI 2 MODEL B WITH TL-WN725N Version 2
#********************************************************************************
# RASPBERRY PI 2 MODEL B ON DEBIAN STRETCH 9.6
#********************************************************************************

root@raspime:~# cat /etc/debian_version
9.6

root@raspime:~# cat /etc/os-release
PRETTY_NAME="Raspbian GNU/Linux 9 (stretch)"
NAME="Raspbian GNU/Linux"
VERSION_ID="9"
VERSION="9 (stretch)"
ID=raspbian
ID_LIKE=debian
HOME_URL="http://www.raspbian.org/"
SUPPORT_URL="http://www.raspbian.org/RaspbianForums"
BUG_REPORT_URL="http://www.raspbian.org/RaspbianBugs"

root@raspime:~# uname -a
Linux raspime 4.14.79-v7+ #1159 SMP Sun Nov 4 17:50:20 GMT 2018 armv7l GNU/Linux

root@raspime:~# cat /proc/cpuinfo | grep Revision
Revision        : a01041

Note :
Hardware revision code from Cpuinfo for Pi 2 Model B is a01041 (Sony, UK) or a21041 (Embest, China).


If you are not sure for your TP-LINK wifi dongle version , please refer to this page
#*******************************************************************************
# WIFI DONGLE TL-WN725N Version 2
#*******************************************************************************

root@raspime:~# lsusb
Bus 001 Device 005: ID 0bda:8179 Realtek Semiconductor Corp. RTL8188EUS 802.11n Wireless Network Adapter


#*******************************************************************************
# DRIVER FOR TL-WN725N Version 2
#*******************************************************************************

root@raspime:~# sudo wget http://downloads.fars-robotics.net/wifi-drivers/install-wifi -O /usr/bin/install-wifi
root@raspime:~# sudo chmod +x /usr/bin/install-wifi
root@raspime:~# /usr/bin/install-wifi
