//----------------------------------------------------------------------------------------------
//[Raspbian JESSIE] How to enable SSH (No Monitor and keyboard)
//----------------------------------------------------------------------------------------------
1> Format SD Card
2> Flash Raspbian JESSIE into SD Card with Win32DiskImager
3> Open CMD and type: dir H: ('H' is SD Card letter)
4> Type: echo>H:\ssh
5> Plug SD back to Rasperry Pi and Power On
6> Open SSH via Putty
7> Done
//----------------------------------------------------------------------------------------------
// Change default password
//----------------------------------------------------------------------------------------------
1> Change password for user pi: passwd 
2> Enter new passsword
3> Change password for su: sudo passwd 
4> Enter new passsword
5> Reboot: sudo reboot
//----------------------------------------------------------------------------------------------
// Expand system file
//----------------------------------------------------------------------------------------------
sudo raspi-config
7. Advanced options
A1. Expand Filesystem
reboot
//----------------------------------------------------------------------------------------------
// Set user permissions
//----------------------------------------------------------------------------------------------
sudo chown -R pi /usr/lib/node_modules/
Fix error: "sudo: /usr/bin/sudo must be owned by uid 0 and have the setuid bit set"
https://askubuntu.com/questions/452860/usr-bin-sudo-must-be-owned-by-uid-0-and-have-the-setuid-bit-set

su
pkexec chown root /usr/lib/sudo/sudoers.so
or
chown root:root /usr/bin/sudo && chmod 4755 /usr/bin/sudo

sudo chown -R pi /home/pi
//----------------------------------------------------------------------------------------------
// Setup Wi-Fi: wpa_gui
//----------------------------------------------------------------------------------------------
1> Install wpa_gui: sudo apt-get install wpagui
2> Install Xming on PC: https://sourceforge.net/projects/xming/files/latest/download
3> Enable Xming on Putty 
4> Run: sudo wpa_gui
5> Reboot: sudo reboot
//----------------------------------------------------------------------------------------------
// Install Mosquitto MQTT
// https://www.digitalocean.com/community/questions/how-to-setup-a-mosquitto-mqtt-server-and-receive-data-from-owntracks
// Mosquitto is not starting on boot  => https://github.com/eclipse/mosquitto/issues/310
//----------------------------------------------------------------------------------------------
adduser mosquitto

sudo apt-get update
sudo apt-get install build-essential libwrap0-dev libssl-dev libc-ares-dev uuid-dev xsltproc
sudo wget http://mosquitto.org/files/source/mosquitto-1.5.tar.gz
sudo tar xvzf mosquitto-1.5.tar.gz
cd mosquitto-1.5
sudo make
sudo make install

sudo mosquitto_passwd -c /etc/mosquitto/pwfile trieu.le

sudo mkdir /var/lib/mosquitto/

sudo chown pi:pi /var/lib/mosquitto/ -R

sudo cp /etc/mosquitto/mosquitto.conf.example /etc/mosquitto/mosquitto.conf

sudo nano /etc/mosquitto/mosquitto.conf

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

// RUN/TEST Broker
sudo mosquitto -c /etc/mosquitto/mosquitto.conf
sudo nano /etc/init/mosquitto.conf

// Type script below:

description "Mosquitto MQTT broker"
start on net-device-up
respawn
exec /usr/local/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf

// Run MQTT Broker on system start up
sudo update-rc.d mosquitto remove

sudo nano /etc/systemd/system/mosquitto.service

// Paste and save this script
[Unit]
Description=Mosquitto MQTT Broker
Documentation=man:mosquitto(8)
Documentation=man:mosquitto.conf(5)
ConditionPathExists=/etc/mosquitto/mosquitto.conf
After=xdk-daemon.service

[Service]
ExecStart=/usr/local/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf
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

//----------------------------------------------------------------------------------------------
// Install NodeJS 10.x
// http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/
//----------------------------------------------------------------------------------------------
curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -

sudo apt install -y nodejs

node -v

npm -v
	
// NodeJS for Raspberry Pi 1	
https://raspberrypi.stackexchange.com/questions/48303/install-node-js-on-an-sd-card-to-work-on-all-pi-models/48313
apt-get remove nodered
apt-get remove nodejs nodejs-legacy
cd ~
wget https://nodejs.org/dist/v6.2.1/node-v6.2.1-linux-armv6l.tar.gz
tar -xzf node-v6.2.1-linux-armv6l.tar.gz
node-v6.2.1-linux-armv6l/bin/node -v
cd node-v6.2.1-linux-armv6l/
sudo cp -R * /usr/local/
export PATH=$PATH:/usr/local/bin
node -v
npm -v

//----------------------------------------------------------------------------------------------
// Install pm2 and pm2-web
// https://www.npmjs.com/package/pm2
// https://www.npmjs.com/package/pm2-web
// Error (Warning "root" does not have permission to access the dev dir): https://github.com/nodejs/node-gyp/issues/454 
// http://pm2.keymetrics.io/docs/usage/quick-start/
//----------------------------------------------------------------------------------------------
1> Install pm2: 
sudo npm install pm2 -g
pm2 register -> PM2 monitoring https://app.pm2.io (lethanhtrieuk36@gmail.com, Trieu101066)
pm2 start app.js

2> Install pm2-web: (Neu khong duoc thi cai pm2-gui)
sudo apt-get install libavahi-compat-libdnssd-dev
sudo chown -R pi /home/pi
sudo npm install -g pm2-web --unsafe-perm
Fix error: Could not locate the bindings files: https://github.com/achingbrain/pm2-web/issues/58
cd /usr/lib/node_modules/pm2-web/node_modules/pwuid/ and then rebuild with this command sudo node-gyp rebuild
//----------------------------------------------------------------------------------------------
// Install PM2-GUI
// link: https://github.com/Tjatse/pm2-gui/issues/47
// V.0.1.4 is working
//----------------------------------------------------------------------------------------------
wget https://github.com/Tjatse/pm2-gui/archive/v0.1.4.zip
unzip v0.1.4.zip
cd pm2-gui-0.1.4
sudo npm install
sudo node pm2-gui start
//----------------------------------------------------------------------------------------------
// Install Apache
// https://www.raspberrypi.org/documentation/remote-access/web-server/apache.md
//----------------------------------------------------------------------------------------------
1> Install Apache2
sudo apt-get install apache2 -y
2> Setting or change port
sudo nano /etc/apache2/ports.conf
sudo /etc/init.d/apache2 restart
//----------------------------------------------------------------------------------------------
// MJPEG-Streamer Install & Setup
// https://github.com/cncjs/cncjs/wiki/Setup-Guide:-Raspberry-Pi-%7C-MJPEG-Streamer-Install-&-Setup-&-FFMpeg-Recording
//----------------------------------------------------------------------------------------------

# Update & Install Tools
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install build-essential libjpeg8-dev imagemagick libv4l-dev cmake -y

# Clone Repo in /tmp
cd /tmp
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental

# Make
sudo make
sudo make install

# Run
/usr/local/bin/mjpg_streamer -i "input_raspicam.so -x 720 -y 480 --fps 30 -quality 80" -o "output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www -c trieu.le:ttp@2018"
//----------------------------------------------------------------------------------------------
// Install adminMongo
// https://github.com/mrvautin/adminMongo
//----------------------------------------------------------------------------------------------
git clone https://github.com/mrvautin/adminMongo.git 
cd adminMongo
sudo npm install
sudo npm start
//----------------------------------------------------------------------------------------------
// WiringPi
// https://www.rs-online.com/designspark/home-automation-with-raspberry-pi-2-and-node-red
//----------------------------------------------------------------------------------------------
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build

Now test that wiringPi installed correctly:
gpio -v
gpio readall
//----------------------------------------------------------------------------------------------
// Install Node-RED
// https://www.npmjs.com/package/node-red
//----------------------------------------------------------------------------------------------
1> Install Node-RED
sudo npm install -g --unsafe-perm node-red
node-red
2> Install node-red-admin: https://nodered.org/docs/security.html
sudo npm install -g node-red-admin --unsafe-perm 
3> Create hash password
node-red-admin hash-pw 

4> Edit settings.js (/home/pi/.node-red/settings.js)
adminAuth: {
    type: "credentials",
    users: [{
        username: "admin",
        password: "$2a$08$uL7VjM6HRIhJcECnfK0mEeCvwB6BkLNZGRiS/wuBNg7mO7/EjbZdq",
        permissions: "*"
    }]
}

5> Run on bot using crontab
@reboot pm2 start /usr/bin/node-red

6> Install custom node: https://nodered.org/docs/getting-started/adding-nodes
cd 
cd .node-red
sudo npm install <npm-package-name>
Example: sudo npm install node-red-contrib-onesignal
Then need to stop and restart Node-RED for it to pick-up the new nodes.

7> Fix Onesignal node error: ONESIGNAL ERROR
Edit file: onesignal.js at location: 
pi@raspberrypi:~/.node-red/node_modules/node-red-contrib-onesignal/onesignal 

sudo nano .node-red/node_modules/node-red-contrib-onesignal/onesignal/onesignal.js
/*
var https = require('https');

module.exports = function (RED) {
  function OneSignalNode(config) {
    RED.nodes.createNode(this, config);
    var oneSignalConfig = RED.nodes.getNode(config.config);
    var [web, android, ios, segment, targetType] = [config.web, config.android, config.ios, config.segments, config.targetType];

    var node = this;
    var headers = {
      "Content-Type": "application/json; charset=utf-8",
      "Authorization": "Basic " + oneSignalConfig.restApiKey
    };

    var options = {
      host: "onesignal.com",
      port: 443,
      path: "/api/v1/notifications",
      method: "POST",
      headers: headers
    };

    this.on('input', function (msg) {
      var req = https.request(options, function (res) {
        res.on('data', function (data) {
          var response = JSON.parse(data);
          if (response.errors) {
            response.errors.forEach(function (err) {
              console.log("ONESIGNAL Responce Error:", err);
              node.error("ONESIGNAL Responce Error->"+ err);
            })
            node.status({ fill: "red", shape: "ring", text: "OneSignal ERROR" });
          } else {
            node.log("Notification SENT SUCCESSFULLY");
            node.status({ fill: "green", shape: "ring", text: "SENT!" });
          }
        });

        req.on('error', function (e) {
          console.log("ONE SIGNAL ERROR:", e);
          node.error("ONE SIGNAL ERROR", e);
          node.status({ fill: "red", shape: "ring", text: "OneSignal ERROR" });
        });
      });

      var title = msg.payload.title || config.title;
      var text = msg.payload.content || config.message;
      var playerId = [];
      playerId = msg.payload.playerId || config.player;
      var messageJson = {
        app_id: oneSignalConfig.appId,
        headings: { "en": title },
        contents: { "en": text },
		included_segments: ["All"]
      };
	  console.log('OneSignal Message:- ', messageJson);
      req.write(JSON.stringify(messageJson));
      req.end();
    });
  }
  RED.nodes.registerType("onesignal", OneSignalNode);
}
*/

//----------------------------------------------------------------------------------------------
// Install ngx-admin
// https://github.com/akveo/ngx-admin
//----------------------------------------------------------------------------------------------
1> Install tools
To install ngx-admin on your machine you need to have the following tools installed:

Git - https://git-scm.com
Node.js - https://nodejs.org. Please note the version should be >=8
Npm - Node.js package manager, comes with Node.js. Please make sure npm version is >=5
2> Install ngx-admin
git clone https://github.com/akveo/ngx-admin.git
cd ngx-admin
sudo npm install
sudo chown -R pi /home/pi/ngx-admin/node_modules
sudo npm rebuild node-sass (Rebuild node-sass, Fix error request node-sass > 4.) 
npm run build
sudo cp -r dist/* /var/www/html (Copy app to Apache2)
//----------------------------------------------------------------------------------------------
// GIT Tool
//----------------------------------------------------------------------------------------------
# Create a new repository on the command line

git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/c0ldlimit/vimcolors.git
git push -u origin master
 
# Push an existing repository from the command line
git commit -am "test commit"
git push -u origin master
//----------------------------------------------------------------------------------------------
// Kill process by ID
//----------------------------------------------------------------------------------------------
sudo netstat -lpn |grep : '9000'
-> Got Process ID
sudo kill -9 <PID>






