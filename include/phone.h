static const char PROGMEM INDEX_HTML_phone[] = R"rawliteral(
<html>
<head><link href='https://freeplc.w3spaces.com/images/favicon.ico' type='image/x-icon' rel='shortcut icon'/>
<!--phone.html for xhttp-->
<!-- hand shakeing status
_________________________________________________________________________________________________________________
| From PHONE             Purpose                    Protocol                   return 
|keyr               Request keyboard initial        esp32 xhr get             keyvalue
|mobk11             TOGGLE SWITCH ID11              esp32 xhr get             'mobk'
|mobt               Request Display                 esp32 xhr get             'mobtON(A/1)'
|__________________________________________________________________________________________________________________
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>MQTT Publisher</title>
<script src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.1/mqttws31.min.js" type="text/javascript"></script>
-->
<!--link rel="manifest" href="./manifest.json"-->
</head>
<title>ESP32-CAM Xhttp phone</title>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<body> 
<label id="init"></label>
<br>
<tr>
<input  type='text' id='disp' onclick='inputclick()' class='disp' minlength='4' maxlength='16' size='14'></input>
<table class='devtable'><tbody>
<button class='button but1' id='rmt1' onclick='toggleCheckbox(1);'>1</button>  
<button class='button but1' id='rmt2' onclick='toggleCheckbox(2);'>2</button>
<button class='button but1' id='rmt3' onclick='toggleCheckbox(3);'>3</button>
<button class='button but1' id='rmt4' onclick='toggleCheckbox(4);'>4</button>
</tbody>
</table>
<br>
<!--button class='button but9' id='rmt96' onclick='location.reload();'>Refresh</button-->
</body>
<script>
var HTTP = "http://"
let protocal=0;     //0 for xhttp  1 for mqtt
let mysetdev=4;  

var rowtext = Array.from(Array(6), () => new Array(8)); 

var butcolor = ["#101010","#2f4468","#0c570c","808480","#576935"];
var ratio=Array(8).fill("0"); 
var kvalue=Array(24).fill(" "); 
var keyv="";
var keyvout="";
var PreviousKey=0;

function inputclick()           //display click
{if(butcolor[keytype]!=null && PreviousKey>0)
    document.getElementById('rmt'+PreviousKey).style.backgroundColor=butcolor[keytype];//"#2f4468"; 
  document.getElementById('disp').value=""; 
}

var  txed="";
var  norepeat=0;
var  keyno=0;
var  keytype=0;
var  disptext;
var  islock;
/////////////////////////////////
function toggleCheckbox(x)
{document.getElementById('rmt'+x).style.backgroundColor="yellow";//butcolor[keyno];
PreviousKey=x;  
toggleCheck(x); //tx key to PLC
norepeat=1;     //get display once 
}

function FBhandledisplay(responseText,x)
{let disptext=responseText.substring(8,24);     
if(disptext[0]==='O' && disptext[1]==='N')
  document.getElementById('rmt'+PreviousKey).style='border:5px solid #c51919;width:'+WW+'px;height:'+HH+'px';
else
  document.getElementById('rmt'+PreviousKey).style='border:5px solid rgb(17, 17, 17); width:'+WW+'px;height:'+HH+'px';        
} 

var WW;
var HH;

function handleInitKey(responseText){
var keyv="";
var k=0;
var t=10;
let tmpic="";  
if(responseText[3]=='d')  
  {for(j=4;j<100;j++)   
    {if(responseText[j]==='@') // && responseText[j+2]=='%')             
      {if(k++<mysetdev)                                 
        {document.getElementById('rmt'+k).innerText=keyv;                                                     
        keyv="";                                    
        }
      }
    else
      keyv=keyv+responseText[j];                                                                                                                                                                                                
    }     
  }
}
///////////////////FOR XHTTP COMMUNICATION////////////////
function toggleCheck(x) {
//if(keyv.length>20)
//keyv="";
//kvalue[x]; 
var xhr = new XMLHttpRequest();
xhr.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200)           
    FBhandledisplay(this.responseText,x);     
  }
  ///////////////////////
  if(x!='T')
  {if(x!=96) //show value except verify password
    {disptext=document.getElementById('disp').value;
    if(disptext!="0")//disptext[0]!='*')  //convert accordingly
      {if(parseInt(disptext)>parseInt(ratio[~~(x/10)]))
        {document.getElementById('disp').value="over maximum";          
        disptext="255";
        }
      else
        {disptext=~~(parseInt(disptext)*255/parseInt(ratio[~~(x/10)]));             
        x="mobk"+x;
        }
      }  
    }     
  }
  else
      x="mobt"; //request display again 
  xhr.open("POST",HTTP+URL+"/action?message="+x, true);            
  xhr.send();                     
}
var pw=0;
//////////////////////////////////////////
window.onload = async function(){  
  URL=window.location.host; 
  updatekeytext();  
  document.getElementById("disp").value="Ready";    
  islock=1;
  }
//////////////////////////////////////////
function updatekeytext() {
var xhr = new XMLHttpRequest();  
xhr.onreadystatechange = function() {
  if(this.readyState == 4 && this.status == 200) {    
    if(this.responseText.length<10)
      document.getElementById("disp").value="Code not match";   
    else  
      handleInitKey(this.responseText);
    }  
  }  
//xhr.open("GET",URL+"action?go=keyr", true);
xhr.open("POST",HTTP+URL+"/action?message=keyr", true);
xhr.send();  
}
</script>
<style> 
  body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px; background-color: rgb(58, 56, 55);}
  table { margin-left: auto; margin-right: auto; }
  td { padding: 8 px; }
  .button {        
    color: rgb(17, 17, 17); 
    padding: 5px 5px;
    text-align: justfy;
    text-decoration: none;
    display: inline-block;
    font-size: 25px;    
    margin: 10px 10px;
    width:90%;
    height:10%;
    cursor: pointer;   
    border-radius: 25px;
    border-color:black;
    border-width: 5px;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
  }
  .but {
    background-color: rgb(196, 189, 184);
    color:rgba(7, 7, 6, 0.788);
  }
  .but1 {
    background-color: #2f4468;    
  }
  .but2 {
    background-color: rgb(12, 87, 12);   
  }
  .but3 {
    background-color: rgb(128,134,128);  
  }
  .but4 {
    background-color: rgb(87,105,53);   
  }
  .but5 {
    background-color: rgb(121,37,37);  
  } 
  .but6 {
    background-color: rgb(138, 190, 41);   
  }
  .but7 {
    background-color: rgb(87, 59, 212);  
  } 
  .but8 {
    background-color: rgb(206, 111, 111);  
  } 
  .but9 {
    background-color: rgb(17, 17, 17); 
    color:rgb(58, 56, 55);
    width:100px; 
  }    
  .disp{text-align: center;
    font-size: 25px;
    background-color: chocolate;
    border-color:black;
    border-width: 5px;
    margin-bottom: 15px;
    border-radius: 25px;
    width:90%;
    height:10%;
    }
</style>
</html>
)rawliteral";