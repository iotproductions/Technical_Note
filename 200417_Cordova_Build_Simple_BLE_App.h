https://www.instructables.com/id/Using-Cordova-to-Create-Bluetooth-Mobile-App-for-T/
// Create new Cordova Project
cordova create SoliditekBLE com.soliditek.marco.SoliditekBLE SoliditekBLE
cd SoliditekBLE
// Install plugins
cordova plugin add cordova-plugin-ble-central
cordova platform add cordova-plugin-compat
/*
https://github.com/apache/cordova-plugin-compat
This plugin is no longer being worked on as the functionality provided by this plugin is now included in cordova-android 6.3.0. 
You should upgrade your application to use version 1.2.0 of this plugin. 
It will detect whether or not the plugin is required based on the version of cordova-android your app uses.
*/
// Add platform
cordova platform add android@6.3.0
// Download and replace www folder
http://www.soliditek.com/wp-content/uploads/2016/12/SoliditekBLE.zip
// Build app and run
cordova run android
