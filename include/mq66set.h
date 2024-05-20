static const char PROGMEM INDEX_HTML_mqsetup[] = R"rawliteral(
<!--4/19/2024-->
<html>
<script src='https://cdnjs.cloudflare.com/ajax/libs/qrcodejs/1.0.0/qrcode.min.js'></script>  
<body><div id='Ssetup'></div>

<h2>QR CODE FOR PHONE REMOTE CONTROL USE MQTT</h2>
<br><button type='button' onclick='PhoneLogicCode()' style='margin-left:50px' >Gen Phone Login code</button><br>
<h2 id='UTLI1'></h2>
<div class='qr' id='qrcode1' style='margin-left:200px;'></div><br><br>
<h2>QR CODE FOR PHONE REMOTE CONTROL USE LOCAL AREA NETWORK (LAN)</h2>
<h2 id='UTLI2'></h2>
<div class='qr' id='qrcode2' style='margin-left:200px;'></div><br><br>
<!--td><button type='button' id='grc' onclick='GererateRC(2)' style='margin-left:40px'>Gererate random PHCODE</button></td><br>
<br><button type='button' onclick='PhoneLogicCode()' style='margin-left:50px' >Gen Phone Login code</button><br-->
<h2 id='remine' style='background-color:yellow;'></h2>
<div class='qr' id='qrcode2' style='margin-left:200px;margin-bottom:50px;'></div><br><br>
</body>
</html>  
<script>
// For mqtt
var ysetdev=11;
var unid;
var txdata;
//for htmltestpage.html
//var rowtext = Array.from(Array(xsetdev), () => new Array(ysetdev)); 
//var systcell = Array.from(Array(xsetdev), () => new Array(ysetdev).fill("")); 

var rowtext = new Array(ysetdev).fill(""); 
var systcell = new Array(ysetdev+5).fill(""); 
//URL="192.168.1.113";
URL=window.location.host; 
function sysloadinitdata(){      
console.log('cd0',systcell);   
  //localStorage.clear(); //all items
  //localStorage.removeItem('systcell');
  rowtext[0] = "<td>Enable Mqtt<input type='checkbox' id='MQTTEN' onclick='togglepulse(15)' +'"+systcell[15]+"'></td>"                                           
  rowtext[1] = "<td>Mqtt Broker:<input type='text' id='ebroker' maxlength='120' value='"+systcell[0]+"'onchange=updatetcell(0,value) style='width:180px'></td>"
  rowtext[2] = "<td>Port:<input type='number' id='mport' step='any' maxlength='4' value='"+systcell[1]+"'onchange=updatetcell(1,value) style='width:100px;margin-right:50px'>Auto generate, depends on protocol</td>"          
  rowtext[3] = "<td>User ID:<input type='text' id='eid' maxlength='20' value='"+systcell[2]+"'onchange=updatetcell(2,value) style='width:100px'> Leave blank for Open Mqtt </td>"             
  rowtext[4] = "<td>User Password:<input type='text'  id='epw' maxlength='20' value='"+systcell[3]+"'onchange=updatetcell(3,value) style='width:100px'> Leave blank for Open Mqtt</td>"
  rowtext[5] = "<td>Encrypt:<input id='encrypt' type='text' maxlength='40' value='"+systcell[4]+"'onchange=updatetcell(4,value) style='width:260px'></select></td>"
  rowtext[6] = "<td>Relay1 Key Name<input id='RLYN1' type='text' maxlength='32' value='"+systcell[5]+"'onchange=updatetcell(5,value) style='width:162px'>"
  rowtext[7] = "<td>Relay2 Key Name<input id='RLYN2' type='text' maxlength='32' value='"+systcell[7]+"'onchange=updatetcell(7,value) style='width:162px'>"
  rowtext[8] = "<td>Relay3 Key Name<input id='RLYN3' type='text' maxlength='32' value='"+systcell[9]+"'onchange=updatetcell(9,value) style='width:162px'>"
  rowtext[9] = "<td>Relay4 Key Name<input id='RLYN4' type='text' maxlength='32' value='"+systcell[11]+"'onchange=updatetcell(11,value) style='width:162px'>"
  rowtext[10] = "<td><br><h3>SERVER PORT:</h3><input type='text' id='Sport' maxlength='10' value='"+systcell[14]+"'onchange=updatetcell(14,value) style='margin-left:80;width:80px'></td>"
  for(let j=0;j<ysetdev;j++)  
      {row = document.getElementById('myDRow'+j.toString());         
        x0 = row.insertCell(0);  //insert       
        x0.innerHTML = rowtext[j];  //                                  
      }      
  }     

function togglepulse(num)
{if(systcell[num]==='checked')
  systcell[num]='';
else
  systcell[num]='checked';  
}


function updatetcell(x,value)
{systcell[x]=value;
//localStorage.setItem('systcell',JSON.stringify(systcell));
document.getElementById('upl').style.backgroundColor='yellow';
}

function updatecolor()
{
document.getElementById('upl').style.backgroundColor='yellow';  
}

function UploadsetupMqsu()  //for ????//
{
Uploadsetup('MQSU');
document.getElementById('uph').style.backgroundColor='yellow';   
}

function Uploadsetup(txdata)  //txdata= "MQSD" //from PLC to PC
{//MQSU MQSD      
var xhtp = new XMLHttpRequest(); 
let charbuf="";
//let stcount=0;
let look=0;
  xhtp.onreadystatechange = function() {
  let txre="";  
  let tyre="";
  if(this.readyState == 4 && this.status == 200) {      
    txre=this.responseText.substring(0,4);                                             
    tyre=this.responseText;
    if(txre==="mqsd")   //mQsU is Download     
      {for(let t=4; t<tyre.length;t++)
        {if(tyre[t]=='*')   
          {//if(stcount==0)
          //    {systcell[look]="";}  //for no input
          systcell[look]=charbuf;         
          charbuf="";          
          look++; //stcount=0;  
          if(look>15)  break;
          }
        else
          charbuf=charbuf+tyre[t];  //charbuf[stcount++]=tyre[t];                     
        }
      if(systcell[4].length<30 || systcell[4]===null || systcell[4]==='undefined')
        {Localdefault(2);  //include unload display     
        }
      else
        DisplayUpdate();
      }        
    }  
  else
    {if(this.readyState == 4 && this.status == 0)
      {window.alert('Unique code not found, check LAN not match');                                                      
      unid="123456";
      }
    } 
  t=systcell[1]-0x30;             
  }  
  ////////////////////////////
  if(txdata==="MQSU")
  {let t=0;
  txdata="";    
  for(t=0;t<16;t++)  
    txdata=txdata+systcell[t]+'*';  
  txdata="MQSU"+txdata;
  }
  xhtp.open("POST","http://"+URL+"/action?message=" + txdata, true);     
  xhtp.send();    
}


function makeid(length) {
    let result = '';
    const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    const charactersLength = characters.length;
    let counter = 0;
    while (counter < length) {
      result += characters.charAt(Math.floor(Math.random() * charactersLength));
      counter += 1;
    }
    return result;
}

function sumCode(str) {
    let sum = 0;
    let stsum="";
    for (let i = 0; i < str.length; i++) {
        sum += str.charCodeAt(i);                    
    }    
    stsum=sum.toString();
    return stsum.substring(0,3);
}


function GererateRC()
{let unidl=systcell[13];
let tcode="";
if(unidl!=undefined)
  tcode=unidl+makeid(22);  
else  
  tcode='1234567'+makeid(22);   
tcode=tcode+sumCode(tcode);
return tcode;
}

function Loaddefault(type)      
{var tcode; 
updatecolor();
if(type===1)   //HIVEMQ WSS
  {//systcell[0][0]='XXX eu.hivemq.cloud';//ste=localStorage.getItem('myurl'); 
  systcell[0]='f27d2ae246004779b11b64b42778b4a1.s2.eu.hivemq.cloud'; 
  systcell[1]='8883'
  systcell[2]='nganmomo'; 
  systcell[3]='5585Ngan';    
  }
else if(type===2)     //Simple HIVEMQ
  {tcode=GererateRC();  
  systcell[0]='broker.hivemq.com';                       //ste=localStorage.getItem('myurl'); 
  systcell[1]='1883'
  systcell[2]=''; 
  systcell[3]='';      
  }    
else if(type===3)   //Local Broker
  {GererateRC();  
  systcell[0]='192.168.X.X';                       //ste=localStorage.getItem('myurl'); 
  systcell[1]='1883';  
  systcell[2]='input_id'; 
  systcell[3]='input_pw';     
  }
  systcell[4]=tcode;
  systcell[5]='Relay1';  
  systcell[6]='';    
  systcell[7]='Relay2';  
  systcell[8]='';  
  systcell[9]='Relay3';  
  systcell[10]='';    
  systcell[11]='Relay4';  
  systcell[12]='';    
  systcell[14]='3300';    
  systcell[15]='checked';    
//GererateRC(1);
//Uploadsetup('MQSU');  //upload and display
//document.getElementById('uph').style.backgroundColor='yellow';
//if(type==2)
//  Uploadsetup('MQSU');
//else
//  document.getElementById('upl').style.backgroundColor='yellow';
}

//Z7?P  
function Localdefault(type)
{Loaddefault(type);
DisplayUpdate()
}

function DisplayUpdate(){
document.getElementById('ebroker').value=systcell[0];
document.getElementById('mport').value=systcell[1];
document.getElementById('eid').value=systcell[2];
document.getElementById('epw').value=systcell[3];
document.getElementById('encrypt').value=systcell[4];

document.getElementById('RLYN1').value=systcell[5];
document.getElementById('RLYN2').value=systcell[7];
document.getElementById('RLYN3').value=systcell[9];
document.getElementById('RLYN4').value=systcell[11];

//document.getElementById('RLYP1').checked=systcell[6];
//document.getElementById('RLYP2').checked=systcell[8];
//document.getElementById('RLYP3').checked=systcell[10];
document.getElementById('MQTTEN').checked=systcell[15];
document.getElementById('Sport').value=systcell[14];
}

//let t=systcell[3][1];
// Get the radio input element by its id
//var radioInput = document.getElementById("radio2");
// Set the checked property to true
//radioInput.checked = true;
syssetup=
"<table class='devtable'>\
<h3 style='display:inline'>MQTT SETUP (Optional, LAN not require this setup)</h3><br>\
<tbody>\
<tr id='myDRow0'></tr><tr id='myDRow1'></tr><tr id='myDRow2'></tr><tr id='myDRow3'></tr>\
<tr id='myDRow4'></tr><tr id='myDRow5'></tr><tr id='myDRow6'></tr><tr id='myDRow7'></tr>\
<tr id='myDRow8'></tr><tr id='myDRow9'></tr><tr id='myDRow10'></tr><div>\
</tbody>\
</table>\
<div id='myDRow9'><div>\
<h3 style='display:inline'>PHONE MQTT EFECTIVE Encrypt code = getChipId(7) + randon char(22) + sumcode(3)</h3><br>\
<br>\
<h3 style='display:inline'>SELECT DEFAULT CONFIG:</h3><br>\
<button type='button' onclick='Localdefault(2)' style='margin-left:50px' >#Simple HIVEMQ</button>\
<h3 style='display:inline'> Use for Simple mqtt without password and use ID</h3><br>\
<button type='button' onclick='Localdefault(3)' style='margin-left:50px' >#Local Broker</button>\
<h3 style='display:inline'> Use for Simple local mqtt broker without password and use ID</h3><br><br>\
<button type='button' onclick='Localdefault(1)' style='margin-left:50px' >HIVEMQ WSS(Phone)</button>\
<h3 style='display:inline'> Use for Mqtt with PW & ID (PASSWWORD AND USERID REQUIRE)</h3><br>\
<label for='cars' style='margin-left:50px'>Choose a Free Mqtt Broker [Obtional]: </label>\
<select name='freemqtt' id='freemqtt' onchange='recopycolor()'>\
<option value='broker.hivemq.com'>broker.hivemq.com</option>\
<option value='test.mosquitto.org'>test.mosquitto.org</option>\
<option value='broker.emqx.io'>broker.emqx.io</option>\
<option value='public.mqtthq.com'>public.mqtthq.com</option>\
</select>\
<button type='button' id='cts' onclick='copytoserver()' style='margin-left:70px'>Copy to Mqtt Broker</button><br>\
<h3 id='uph'>Press Hardware reset key and than Press [Network] button to test the condition.</h3>\
<button type='button' id='upl' onclick='UploadsetupMqsu()' style='margin-left:50px;' >Save setup to PLC</button><br>\
<br><button type='button' onclick='EffectTopic()' style='margin-left:50px' >Generate new randon encrypt code </button>\
<h3 id='testNet' style='display:inline;margin-left:100px'></h3>\
<h3 style='display:inline'><label type='text' id='efftopic'></label></h3>"

function PhoneLogicCode()
{
//loginincode='***'+systcell[0][0]+'***'+systcell[1][0]+'***'+systcell[2][0]+'***'+systcell[3][0]+'***'+systcell[2][1]; 
var loginincode="https://freeplc.w3spaces.com/e8266/phone?"+systcell[4]+systcell[0]; 
document.getElementById('qrcode1').innerText='';
var MQqrcode2 = new QRCode('qrcode1',loginincode);
//document.getElementById('remine').innerText='When all input is complete, press the HARDWARE RESET button to make it effective.';
document.getElementById('UTLI1').innerText='Scan QR code by Mqtt Phone, URL='+loginincode;
var MQqrcode2 = new QRCode('qrcode2',URL+':'+systcell[14].toString()+'/phone');
document.getElementById('UTLI2').innerText=URL+':'+systcell[14].toString()+'/phone';
}


function copytoserver()
{let va=document.getElementById('freemqtt').value; 
document.getElementById('ebroker').value=va;
systcell[0]=va;
document.getElementById('upl').style.backgroundColor='yellow';
}

function recopycolor()
{
document.getElementById('cts').style.backgroundColor='yellow';  
}

function EffectTopic()
{let tcode=GererateRC();
systcell[4]=tcode;
document.getElementById('encrypt').value=tcode;
}


window.onload = async function(){  
  document.getElementById('Ssetup').innerHTML=syssetup; 
  sysloadinitdata();
  //if(systcell[4].length<30)
  //  Localdefault(2);
  Uploadsetup("MQSD");            
}

</script>
<style>
  input{
    margin-left:10px;
  }
</style>
)rawliteral";