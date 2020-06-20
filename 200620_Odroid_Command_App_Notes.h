//-----------------------------------------------------------------------------------------------------------------------
// Odroiod command app notes
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// Set password for root user
sudo passwd root
// set password for odroid user
sudo passwd odroid
//-----------------------------------------------------------------------------------------------------------------------
// Enable sudo without password
//-----------------------------------------------------------------------------------------------------------------------
//Open the /etc/sudoers file (as root, of course!) by running:
sudo EDITOR=nano visudo
//At the end of the /etc/sudoers file add this line:
odroid ALL=(ALL) NOPASSWD:ALL
// Save file and reboot
//-----------------------------------------------------------------------------------------------------------------------
// Install Git
//-----------------------------------------------------------------------------------------------------------------------  
sudo apt-get install git
//-----------------------------------------------------------------------------------------------------------------------
// Install NodeJS 10.x
// http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/
//----------------------------------------------------------------------------------------------
curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -

sudo apt -y install gcc g++ make
sudo apt -y install nodejs

node -v
npm -v
//----------------------------------------------------------------------------------------------
// Install Mosquitto MQTT
// https://www.vultr.com/docs/how-to-install-mosquitto-mqtt-broker-server-on-ubuntu-16-04
// Mosquitto is not starting on boot  => https://github.com/eclipse/mosquitto/issues/310
//----------------------------------------------------------------------------------------------
sudo apt-get install mosquitto

sudo mosquitto_passwd -c /etc/mosquitto/pwfile trieu.le

sudo nano /etc/mosquitto/conf.d/default.conf

listener 1883 localhost
persistence true
persistence_location /var/lib/mosquitto/
persistence_file mosquitto.db
log_dest syslog
log_dest stdout
log_dest topic
log_type error
log_type warning
log_type notice
log_type information
connection_messages true
log_timestamp true
allow_anonymous false
password_file /etc/mosquitto/pwfile

sudo /sbin/ldconfig

sudo systemctl restart mosquitto

// RUN/TEST Broker
sudo mosquitto -c /etc/mosquitto/conf.d/default.conf
sudo nano /etc/init/mosquitto.conf

// Type script below:

description "Mosquitto MQTT broker"
start on net-device-up
respawn
exec /usr/local/sbin/mosquitto -c /etc/mosquitto/conf.d/default.conf

// Run MQTT Broker on system start up
sudo update-rc.d mosquitto remove

sudo nano /etc/systemd/system/mosquitto.service

// Paste and save this script
[Unit]
Description=Mosquitto MQTT Broker
Documentation=man:mosquitto(8)
Documentation=man:mosquitto.conf(5)
ConditionPathExists=/etc/mosquitto/conf.d/default.conf

After=xdk-daemon.service

[Service]
ExecStart=/usr/local/sbin/mosquitto -c /etc/mosquitto/conf.d/default.conf

ExecReload=/bin/kill -HUP $MAINPID
User=mosquitto
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target

sudo systemctl enable mosquitto.service

sudo reboot

sudo service mosquitto restart
//----------------------------------------------------------------------------------------------
// Install Crontab
// https://www.raspberrypi.org/documentation/linux/usage/cron.md
//----------------------------------------------------------------------------------------------
sudo apt-get install gnome-schedule
crontab -e
or
sudo crontab -u pi -e

@reboot sudo mosquitto -c /etc/mosquitto/mosquitto.conf -d

Fix error: "crontabs//: fopen: Permission denied" 
https://askubuntu.com/questions/710671/cannot-access-crontab-after-changing-uid
sudo chown root:crontab /usr/bin/crontab
sudo chmod 2755 /usr/bin/crontab
