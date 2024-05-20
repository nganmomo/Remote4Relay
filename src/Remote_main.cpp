//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//
#include "header.h"
#ifdef MqttBroker
uMQTTBroker myBroker;
#endif
int loopup[17]={broker,port,userid,userpw,scode,ELine1,mtime1,ELine2,mtime2,ELine3,mtime3,ELine4,mtime4,MCUID,serverport,mqtten,uniqueEND};
void SaveMessEEP(String mess);
void RetriveMessEEP(char *buffer);
byte key,count=0; 
String MYSSID = "";
String MYPASSWORD = "";
char sport[11];
int Sport(){
eerbytechar(serverport,sport,10,0);    
return atoi(sport);
}

AsyncWebServer server(Sport());
//AsyncWebServer server(3300);
const char *htmlcontentType = "html/text";
//const char* ssid = "ATT3jl8Tns";
//const char* password = "6mrk8iyf26vn";
const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


void wifisetup() {  
String sSETUP="";
char cSETUP[20];
Serial.print("\nInput ssid=\n");  
do{if (Serial.available() > 0) {
    key = Serial.read();               
    MYSSID=MYSSID+static_cast<char>(key);
    count++;
    }
  }while(key!=0xd && key!=0xa);        
    Serial.println(MYSSID);  
    key=0;
Serial.println("Input password=");
do{if (Serial.available() > 0) {
    key = Serial.read();
    MYPASSWORD=MYPASSWORD+static_cast<char>(key);
    count++;
    }
  }while(key!=0xd && key!=0xa);   
    Serial.println(MYPASSWORD);  
    key=0;
//////////////////////////
Serial.println("Input Port=");    //hints
do{if (Serial.available() > 0) {
    key = Serial.read();
    sSETUP=sSETUP+static_cast<char>(key);   
    }
  }while(key!=0xd && key!=0xa);  
  if(sSETUP.length()>=2)
  {sSETUP.toCharArray(cSETUP,sSETUP.length());
  eewbyte(serverport,cSETUP,sSETUP.length());
  Serial.println(sSETUP);  
  Serial.println("port will come to effect after reset");  
  sSETUP="";key=0;
  }
//////////////////////////  
Serial.println("LOGIN PASSWORD=");    //hints
do{if (Serial.available() > 0) {
    key = Serial.read();
    sSETUP=sSETUP+static_cast<char>(key);   
    }
  }while(key!=0xd && key!=0xa);  
  if(sSETUP.length()>=2)
  {sSETUP.toCharArray(cSETUP,sSETUP.length()); 
  eewbyte(userid,cSETUP,sSETUP.length());
  Serial.println(sSETUP); 
  }  
//////////////////////////  
for(int t=1;t<5;t++)
    {int le[5]={0,ELine1,ELine2,ELine3,ELine4};
    int lt[5]={0,mtime1,mtime2,mtime3,mtime4};
    key=0;
    sSETUP="";
    Serial.printf("Input button%d=\n",t);   //hints
    do  {if (Serial.available() > 0) {
            key = Serial.read();
            sSETUP=sSETUP+static_cast<char>(key);   
            }
        }while(key!=0xd && key!=0xa);  
    if(sSETUP.length()>=2)
        {sSETUP.toCharArray(cSETUP,sSETUP.length());
        eewbyte(le[t],cSETUP,sSETUP.length());
        Serial.println(sSETUP);         
        }          
    key=0;
    sSETUP="";    
    Serial.printf("DelayTime%d=\n",t);   //hints
    do  {if (Serial.available() > 0) {
            key = Serial.read();
            sSETUP=sSETUP+static_cast<char>(key);   
            }
        }while(key!=0xd && key!=0xa);       
    if(sSETUP.length()>=2)
        {sSETUP.toCharArray(cSETUP,sSETUP.length());
        eewbyte(lt[t],cSETUP,sSETUP.length());
        Serial.println(sSETUP); 
        }       
    }  
}      

void ServerActive()
{   server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {                         
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", INDEX_HTML_phone);            
    request->send(response);
        });

    server.on("/phoneid", HTTP_GET, [](AsyncWebServerRequest *request){                    
    String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            #ifdef  ESP8266            
            message = ESP.getChipId();   
            #else
            message = ESP.getEfuseMac();   
            #endif
        }
        request->send(200, "text/plain", "ESP8266 Chip id: " + message);        
    });                              
   
    server.on("/setup", HTTP_GET, [] (AsyncWebServerRequest *request) {           
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", INDEX_HTML_mqsetup);            
        request->send(response);
    });    
            
    server.on("/action", HTTP_POST, [] (AsyncWebServerRequest *request) {
        String message;        
        char front5[6]; 
        char front4[5];   
        char Line1[20],Line3[20],Line2[20],Line4[20];     
        char buffer[EEPROM_SIZE];
        char st[4];   
        if (request->hasParam(PARAM_MESSAGE)) {
            {message = request->getParam(PARAM_MESSAGE)->value();
            //Serial.println(message);
            //SaveMessEEP(message);
            }
        } else {
            message = "No message sent";
        }  
        for(byte t=0;t<5;t++)
            {front5[t]=message[t];                  
            if(t<4)
            front4[t]=message[t];  
            }
        front5[5]=0; front4[4]=0;   
        if(strcmp(front4,"MQSU")==0)
            {SaveMessEEP(message);
            message=(String)buffer;
            Serial.println("MQSUmessage");
            Serial.println(message);
            }
        if(strcmp(front4,"MQSD")==0)
            {RetriveMessEEP(buffer);
            message=(String)buffer;
            Serial.println("MQSDmessage");
            Serial.println(message);
            }
        if(strcmp(front4,"keyr")==0)
            {eerbytechar(ELine1,Line1,20);
            eerbytechar(ELine2,Line2,20);
            eerbytechar(ELine3,Line3,20);
            eerbytechar(ELine4,Line4,20);
            //message=(String)Line1+"@"+(String)Line2+"@C1@D1@E1@100@"+(String)Line3+"@"+(String)Line4+"@C2@D2@E2@100@*$^22";
            message=(String)Line1+"@"+(String)Line2+"@"+(String)Line3+"@"+(String)Line4+"@";
            Serial.print("==message==");
            Serial.println(message);
            }
        if(front5[3]=='k')      //toggle switch
        {Serial.print("front5=");
        Serial.println(front5);
        eerbyte(swul,st,4);
        if(strcmp(front5,"mobk1")==0) //A1=11 A2=21  B112 B222
            {//eerbytechar(swul,&st[0],1);
            if(st[0]!=1)    {st[0]=1; message="mobkON A1";
                            digitalWrite(relay1,ON);} 
            else            {st[0]=0; message="mobkOFF A1";
                            digitalWrite(relay1,OFF);}  
            }
        if(strcmp(front5,"mobk2")==0) //A1=11 A2=21  B112 B222
            {//eerbytechar(swdl,&st[0],1);
            if(st[1]!=1)    {st[1]=1; message="mobkON A2";
                            digitalWrite(relay2,ON);}  
            else            {st[1]=0; message="mobkOFF A2";
                            digitalWrite(relay2,OFF);}  
            } 
        if(strcmp(front5,"mobk3")==0) //A1=11 A2=21  B112 B222
            {//eerbytechar(swur,&st[0],1);
            if(st[2]!=1)    {st[2]=1; message="mobkON B1";
                            digitalWrite(relay3,ON);} 
            else            {st[2]=0; message="mobkOFF B1"; 
                            digitalWrite(relay3,OFF);} 
            } 
        if(strcmp(front5,"mobk4")==0) //A1=11 A2=21  B112 B222
            {//eerbytechar(swdr,&st[0],1);
            if(st[3]!=1)    {st[3]=1; message="mobkON B2";
                            digitalWrite(relay4,ON);}  
            else            {st[3]=0;  message="mobkOFF B2";
                            digitalWrite(relay4,OFF);}  
            };                       
        eewbyte(swul,st,4);          
        }
        request->send(200, "text/plain","mqsd"+message);
    });    
}


void setup() {
    //test key//    
    char mssid[20];
    char mpass[20];
    pinMode(setuppin,INPUT_PULLUP); 
    pinMode(relay1,OUTPUT); 
    pinMode(relay2,OUTPUT); 
    pinMode(relay3,OUTPUT); 
    pinMode(relay4,OUTPUT);          
    Serial.begin(74880);
    //set wifi//
    if(digitalRead(setuppin)==SETUPSTATE)  //setup mode
    {wifisetup();
    if(count>10)
      {MYSSID.toCharArray(mssid,MYSSID.length());
      MYPASSWORD.toCharArray(mpass,MYPASSWORD.length()); 
      eewpassid(eessid,mssid,mpass);          
      }
      Serial.println("To run program set switch to run position and press reset to start program");
      Serial.println("To change SSID or password set switch setup position and press reset"); 
      eewchar(mqtten,' ');            
    }             
    else      
        {eerpassid(eessid,mssid,mpass);          
        Serial.println(mssid);
        Serial.println(mpass);
        }
    WiFi.mode(WIFI_STA);
    WiFi.begin(&mssid[0],&mpass[0]);
    //WiFi.begin(ssid,password);
    Serial.printf("Connect to WiFi...\n");
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi not connected!\n");
        return;
    }

    Serial.println("IP Address: ");  
    Serial.print(WiFi.localIP());
    Serial.print(':');
    Serial.println(sport);
    ServerActive();
    Serial.println("WiFi Connected");
    server.onNotFound(notFound);
    server.begin();     
#ifdef MqttClient         
    if(eerchar(mqtten)=='c')
        {Serial.println("mqtt Enabled");
        mqttclientsetup();
        connectToMqtt();   
        }
    else
        Serial.println("mqtt Disabled");    
#endif 
#ifdef MqttBroker   
    Serial.println("Starting MQTT broker");
    myBroker.init();
#endif 
}

void loop() {
}

void GetUNID()
{
#ifdef  ESP8266    
    unsigned int unid=ESP.getChipId();
#else    
    u_int64_t unid = ESP.getEfuseMac();   //"No message sent";
#endif    
char Array[8];
itoa(unid,Array,10);
//Serial.println(Array);
//Serial.println("-3-");
eewbyte(MCUID,Array,8);
}

void SaveMessEEP(String mess)
{
byte look=0;
int stcount=0;
char charbuf[100];
int Length=mess.length();
if(Length>=EEPROM_SIZE)
    Length=EEPROM_SIZE;
for(byte t=4;t<Length;t++)
    {if(mess[t]=='*')   
        {if(stcount==0)
            {charbuf[0]=0;stcount=1;}  //for no input
        eewbyte(loopup[look],charbuf,stcount+1);
        Serial.print(stcount);
        Serial.print('=');
        Serial.println(charbuf);
        look++; stcount=0;  
        if(look>16)  break;
        }
    else
        {charbuf[stcount++]=mess[t];    
        charbuf[stcount]=0;
        }
    }
GetUNID();  
eerbytechar(MCUID,charbuf,8,0);  
Serial.print("mess=");
Serial.println(mess);
Serial.print("UNIQcode=");
Serial.println(charbuf);
}

void RetriveMessEEP(char *buffer)
{int upcount=0;
int retcount;

for(int t=0;t<EEPROM_SIZE;t++)
    buffer[t]=0;
String message="";
int stcount=0;
//char charbuf[100];
for(byte look=0;look<16;look++)
    {stcount=loopup[look+1]-loopup[look];
    retcount=eerbytechar(loopup[look],&buffer[upcount],stcount,0);          
    upcount=upcount+retcount;
    buffer[upcount++]='*';
    if(upcount>=EEPROM_SIZE)
        break;
    }
}
