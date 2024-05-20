#include "header.h"
/*
|station             subscribe       publish
|PLC                  R               T
|Server               T               R
*/
//#define MQTT_HOST IPAddress("broker.hivemq.com")
//#define MQTT_HOST "broker.hivemq.com"
//#define MQTT_PORT 1883
#ifdef MqttClient
AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;
char Scode[100];
char mqttbroker[60];
int  mqPort;
void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent) {
  //uint16_t packetIdSub = 
  Scode[0]='R';
  mqttClient.subscribe(Scode, 2);
  //mqttClient.publish('R'+Scode, 0, true, "test 1");
  //Serial.println(packetIdSub);
  /*
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSub);
  mqttClient.publish("test/lol", 0, true, "test 1");
  Serial.println("Publishing at QoS 0");
  uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  Serial.print("Publishing at QoS 1, packetId: ");
  Serial.println(packetIdPub1);
  uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  Serial.print("Publishing at QoS 2, packetId: ");
  Serial.println(packetIdPub2);
  */
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {  
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void  stringtochar(char *KEYDATA,String KEYST)
{for(unsigned int j=0;j<100;j++)
    KEYDATA[j]=0;  
for(unsigned int t=0;t<KEYST.length();t++)
    KEYDATA[t]=KEYST[t];    
}
#endif

#ifdef MqttClient
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {  
  char Keydata[150];
  char Line1[20],Line3[20],Line2[20],Line4[20];
  char ckul[10],ckdl[10],ckur[10],ckdr[10];
  char st[4];
  //Serial.print("On message=");  
  //Serial.println(topic);
  //Serial.println(payload);
  String keysetup,message;
  if(payload[0]=='I' && payload[1]=='N' && payload[2]=='I' && payload[3]=='T' && payload[4]=='K')
      { eerbytechar(ELine1,Line1,20);
        eerbytechar(mtime1,ckul,10);
        eerbytechar(ELine2,Line2,20);
        eerbytechar(mtime2,ckdl,10);
        eerbytechar(ELine3,Line3,20);
        eerbytechar(mtime3,ckur,10);
        eerbytechar(ELine4,Line4,20);        
        eerbytechar(mtime4,ckdr,10);
        //keysetup="mqsd"+(String)Line1+"@"+(String)Line2+"@C1@D1@E1@100@"+(String)Line3+"@"+(String)Line4+"@C2@D2@E2@100@*$^22";
        keysetup="mqsd"+(String)Line1+"@"+(String)Line2+"@"+(String)Line3+"@"+(String)Line4+"@";
        stringtochar(Keydata,keysetup);
        Scode[0]='T';
        mqttClient.publish(Scode, 0, false,Keydata);
      }
  if(payload[0]=='M' && payload[1]=='O' && payload[2]=='B' && payload[3]=='K')
    {eerbyte(swul,st,4);
    if(payload[4]=='1') //A1=11 A2=21  B112 B222
        {//eerbytechar(swul,&st[0],1);
        if(st[0]!=1)    {st[0]=1; message="mobk____ON A1";
                        digitalWrite(relay1,ON);}                       
        else            {st[0]=0; message="mobk____OFF A1";
                        digitalWrite(relay1,OFF);}  
        //if(ckul[0]!='c')
        //                {delay(1000);
        //                digitalWrite(relay1,OFF); 
        //                st[0]=0; message="mobk____OFF A1";                       
        //                } 
        }
    if(payload[4]=='2') //A1=11 A2=21  B112 B222
        {//eerbytechar(swdl,&st[0],1);
        if(st[1]!=1)    {st[1]=1; message="mobk____ON A2";
                        digitalWrite(relay2,ON);}  
        else            {st[1]=0; message="mobk____OFF A2";
                        digitalWrite(relay2,OFF);} 
        //if(ckdl[1]!='c')
        //                {delay(1000);
        //                digitalWrite(relay2,OFF); 
        //                st[1]=0; message="mobk____OFF A2";                      
        //                }                  
        } 
    if(payload[4]=='3') //A1=11 A2=21  B112 B222
        {//eerbytechar(swur,&st[0],1);
        message="";
        if(st[2]!=1)    {st[2]=1; message="mobk____ON  B1";
                        digitalWrite(relay3,ON);} 
        else            {st[2]=0; message="mobk____OFF B1"; 
                        digitalWrite(relay3,OFF);} 
        //if(ckur[2]!='c')
        //                {delay(1000);
        //                digitalWrite(relay3,OFF); 
        //                st[2]=0; message="mobk____OFF B1";                      
        //                }                           
        } 
    if(payload[4]=='4') //A1=11 A2=21  B112 B222
        {//eerbytechar(swdr,&st[0],1);
        if(st[3]!=1)    {st[3]=1; message="mobk____ON  B2";
                        digitalWrite(relay4,ON);}  
        else            {st[3]=0;  message="mobk____OFF B2";
                        digitalWrite(relay4,OFF);} 
        //if(ckdr[3]!='c')
        //                {delay(1000);
        //                digitalWrite(relay4,OFF); 
        //                st[3]=0; message="mobk____OFF B2";                      
        //                }                            
        };               
    stringtochar(Keydata,message);             
    Serial.println(Scode);
    Scode[0]='T';
    mqttClient.publish(Scode, 0, false,Keydata,15);        
    eewbyte(swul,st,4);   
    }              
  //Serial.println("Publish received.");
  //Serial.print("  payload: ");
  //Serial.println(payload);
  }
  
  /*
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain: ");
  Serial.println(properties.retain);
  Serial.print("  len: ");
  Serial.println(len);
  Serial.print("  index: ");
  Serial.println(index);
  Serial.print("  total: ");
  Serial.println(total);
  */


void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void mqttclientsetup() { 
  char PPort[5];
  eerbytechar(scode,&Scode[1],100);
  eerbytechar(broker,mqttbroker,60);
  eerbytechar(port,PPort,5);
  mqPort=atoi(PPort); 
  Serial.println("Connected to MQTT.");
  Serial.print("Mqtt Topic=");
  Scode[0]='R';
  Serial.println(Scode);
  Serial.print("mqttbroker=");
  Serial.println(mqttbroker); 
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  //mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setServer(mqttbroker,mqPort);
  //connectToWifi();
}
#endif