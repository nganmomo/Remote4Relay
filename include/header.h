#include <Arduino.h>
#include "phone.h"
#include "mq66set.h"
//#include "manifest.h"
#ifdef ESP32
#include <WiFi.h>
#include <Ticker.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#define MqttClient
//#define MqttBroker
#include <AsyncMqttClient.h>
#ifdef MqttBroker
#include <uMQTTBroker.h>
#endif
#include <EEPROM.h>
#define EEPROM_SIZE 512
#define eessid      0       //  
#define broker      50      //100
#define port        150     //5
#define userid      155     //30
#define userpw      185     //30    
#define scode       215     //100
#define ELine1      315     //20
#define mtime1      335     //10
#define ELine2      345     //20
#define mtime2      365     //10
#define ELine3      375     //20
#define mtime3      395     //10
#define ELine4      415     //20
#define mtime4      435     //10
#define MCUID       445     //10 
#define serverport  455     //10
#define mqtten      465     //10
#define uniqueEND   475     //
#define swul        485     //5
#define swdl        490     //5
#define swur        495     //5
#define swdr        500     //5

#define setuppin     5
#define SETUPSTATE   0         //Low for SETUP

#define relay1      13
#define relay2      12
#define relay3      14
#define relay4      16

#define ON          true
#define OFF         false

extern int eerbytechar(int offset,char* keyc,int length,char exitcode=0);
extern void eewbyte(int offset,char* keyc,int length);
extern void eerbyte(int offset,char* keyc,int length);
extern void eewpassid(int offset,char* iddata,char* pwdata);
extern void eerpassid(int offset,char* iddata,char* pwdata);
extern void mqttclientsetup();
extern void connectToMqtt();
char eerchar(int offset);
void eewchar(int offset,char c);
/*ESP8266               /15 cannot use/
|GND|     |GND  GND|       |IO13 RY4|
|GND|     |GND IO15|       |IO12 RY3|
|IO0|     |5V   IO2|       |IO14 RY2|
|RX0|     |5V   IO0|       |IO16 RY1|
|TX0|     |3V3  IO4|       |EN      |
|5V |     |3V3  IO5|       |ADC     |
*/

/*ESP32 S2 Mini
________________________
|EN   1|       |40   39|
|3    2|       |38   37|
|5    4|       |36   35|
|7    6|       |34   33|
|9    8|       |21   18|
|11  10|       |17   16|
|12  13|       |GND GND|
|3V3 14| _____ |15 VBUS|
|_______|     |________|  
        |_____|       
*/  

/*ESP32 Ai-C3
 _______________
|GND|       |GND|
|3V3|       |TX |       
|3v3|       |RX |  
|2  |       |GND|      
|3  |       |9  |       
|GND|       |8  |      
|R  |       |GND|      
|GND|       |7  |     
|0  |       |6  |      
|1  |       |5  |  
|10 |       |4  |      
|GND|       |GND|      
|5V |       |1B |     
|5V |       |1S |      
|GND|       |GND|      
|  ____   ____  |
|_|    |_|    |_|  
  |____| |____|      
*/

/*ESP32 C3 SupperMini
 ________________________
|5  ADC2 SCL| |VBUS      |       
|6          | |GND       |       
|7          | |3V3       |      
|8       PWM| |4 ADC1 SDA|      
|9      BOOT| |3         |       
|10         | |2         |      
|20         | |1 RXD     |       
|21         | |0 TXD     |       
|          _____         |
|_________|     |________|  
          |_____|       
*/