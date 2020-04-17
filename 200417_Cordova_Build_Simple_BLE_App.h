https://www.instructables.com/id/Using-Cordova-to-Create-Bluetooth-Mobile-App-for-T/
// Create new Cordova Project
cordova create SoliditekBLE com.soliditek.marco.SoliditekBLE SoliditekBLE
cd SoliditekBLE
// Install plugins
cordova plugin add cordova-plugin-ble-central
cordova platform add cordova-plugin-compat
// Add platform
cordova platform add android@6.2.0
// Download and replace www folder
http://www.soliditek.com/wp-content/uploads/2016/12/SoliditekBLE.zip
// Build app and run
cordova run android
