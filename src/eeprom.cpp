#include "header.h"
//will combin later

void eewbyte(int offset,char* keyc,int length)
{int t;
EEPROM.begin(EEPROM_SIZE);
for(t=0;t<length;t++)     
    EEPROM.write(offset+t,keyc[t]); //lower byte         
EEPROM.commit();     
EEPROM.end();   
}


void eerbyte(int offset,char* keyc,int length)
{int t;
EEPROM.begin(EEPROM_SIZE);
for(t=0;t<length;t++)     
    keyc[t]=EEPROM.read(offset+t); //lower byte             
EEPROM.commit();     
EEPROM.end();   
}

char eerchar(int offset)
{char c;
EEPROM.begin(EEPROM_SIZE);  
    c=EEPROM.read(offset); //lower byte             
EEPROM.commit();     
EEPROM.end();   
return c;
}


void eewchar(int offset,char c)
{EEPROM.begin(EEPROM_SIZE);  
    EEPROM.write(offset,c); //lower byte             
EEPROM.commit();     
EEPROM.end();   
}

int eerbytechar(int offset,char* keyc,int length,char exitcode)
{int t;
EEPROM.begin(EEPROM_SIZE);
for(t=0;t<length;t++)     
    {keyc[t]=EEPROM.read(offset+t); //lower byte         
    if(keyc[t]==exitcode || keyc[t]>127 || keyc[t]<0x20)
        break;
    }
EEPROM.commit();     
EEPROM.end();   
return t;
}

void eewpassid(int offset,char* iddata,char* pwdata)
{int t;
EEPROM.begin(EEPROM_SIZE);
for(t=0;t<20;t++)     
    EEPROM.write(offset+t,iddata[t]); //lower byte         
offset=offset+20;
for(t=0;t<20;t++)   
    EEPROM.write(offset+t,pwdata[t]); //lower byte        
EEPROM.commit();     
EEPROM.end();   
}

void eerpassid(int offset,char* iddata,char* pwdata)
{int t;
    EEPROM.begin(EEPROM_SIZE);
for(t=0;t<20;t++)     
    iddata[t]=EEPROM.read(offset+t); //lower byte         
offset=offset+20;
for(t=0;t<20;t++)   
    pwdata[t]=EEPROM.read(offset+t); //lower byte          
EEPROM.commit();     
EEPROM.end();   
}
