👋 Hello remote control user!
If we control home appliances remotely using a cell phone, we typically rely on a third-party server. Our remote-control device polls this server every second. To cover the service costs, the server provider often includes ads in your mobile application, which can potentially expose your information to third parties.

To address these concerns, we have designed an open-source application that does not rely on any third-party applications or servers. For users operating within a local area network (LAN), no additional router configuration is necessary. However, if you wish to control your devices from anywhere, you will need to open a port on your router.

In this setup, the hardware, powered by ESP8266, operates in server mode. Importantly, there is no communication signal when the device is not being controlled, enhancing security and privacy.

FRIMWARE SOURCE CODE
Download from Github and compile it, or just down load bin file.

SETUP
This design does not require a server or application for setup, you can use any serial communication to set it up, but we provide a website for installation reference. Our server is not encrypt can see source code.

COMMUNICTION PROTOCAL
The ESP8266 is run as server mode, use HTTP TCP protocal, it is will for launch request signal, the communication traffic is zero if no one visit it.

HOW TO USE PLEASE VISIT

http://plccontrol.online


ESP8266 CIRCUITRY
IO13 RELAY4
IO12 RELAY3
IO14 RELAY2
IO16 RELAY1

EN   RESET   
ADC  N.C.
IO15 SETUP 

HTML
CSS
JavaScript
Node.js

⛑ Need support ,subjection or involve the project design is welcome?
email:maxtronusa@outlook.com
