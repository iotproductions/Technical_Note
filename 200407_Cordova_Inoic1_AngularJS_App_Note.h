// Install NodeJS
Download and install Node.js. On installation you should be able to invoke node and npm on your command line.
// Check Nodejs installation by Open CMD then type
node -v
// Install Cordova and Ionic
npm install -g cordova
cordova -v
npm install -g ionic
ionic -v
// Create new Cordova project
cordova create SmartNotifier com.example.smartnotifier SmartNotifier
cd SmartNotifier

// Create new Ionic 1 project => To use AngularJS resources
// Ionic 1 docs: https://ionicframework.com/docs/v1/
ionic start testapp sidemenu --type ionic1

Copy all files in www folder from testapp to SmartNotifier

// Add Android platform
cordova platform add android@6.2.2 --save
//cordova platform rm android

// Build app
cordova build android
// Run app
cordova run android

