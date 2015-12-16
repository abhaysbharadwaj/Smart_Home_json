# Smart_Home_json
An arduino IoT project to create a home automation scenario with ability to send and receive data over the internet via. a bluetooth module. must use an intermediate gateway device like a RasPi to connect to the internet.

Sensors/Actuators like DHT11, LDR, IR, pizeo buzzer, relat, BT-HC05 are connected to a arduino (Tested on UNO and NANO).
sensor data are collected, processed and sent to a raspberry pi via BT communication using Json format. 
The data is then sent to the cloud and stored in a DB.

Relay control data is sent from mobile app to the RasPi using internet. this is again sent to arduino via. BT and the relay is made to turn ON or OFF depending on the control signal.

This project is to illustrate a home automation scenerio using concept of IoT (Internet of Things).

You can install the Bluetooth Serial app on your android phone to see the BT data on your phone.
After installing the app fo the following changes in the app:
1) open app, go to Preference (top right corner)
2) change "orientation" to PORTRAIT
3) switch ON "Terminal Mode"
4) go back and use the app.
NB: makesure you pair your bluetooth module with your phone first before using.
