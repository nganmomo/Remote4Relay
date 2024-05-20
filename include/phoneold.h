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
<tr id='myDRow0'></tr><tr id='myDRow1'></tr><tr id='myDRow2'></tr><tr id='myDRow3'></tr>
<tr id='myDRow4'></tr><tr id='myDRow5'></tr><tr id='myDRow6'></tr><tr id='myDRow7'></tr>
</tbody>
</table>
<br>
<!--button class='button but9' id='rmt96' onclick='location.reload();'>Refresh</button-->
</body>
<script>
var HTTP = "http://"
let protocal=0;     //0 for xhttp  1 for mqtt
let mxsetdev=5;
let mysetdev=6;  

var rowtext = Array.from(Array(6), () => new Array(8)); 

var butcolor = ["#101010","#2f4468","#0c570c","808480","#576935"];
var ratio=Array(8).fill("0"); 
var kvalue=Array(24).fill(" "); 
var keyv="";
var keyvout="";
var PreviousKey=0;

function loadkeytable2(){    
  for(let t=0;t<mysetdev;t++)   
    {   let v=t+1;
        rowtext[0][t] = "<td><button class='button but1' id='rmt"+v+"1' onclick='toggleCheckbox("+v+"1);'>"+v+"</button></td>"
        rowtext[1][t] = "<td><button class='button but2' id='rmt"+v+"2' onclick='toggleCheckbox("+v+"2);'>"+v+"</button></td>"
        rowtext[2][t] = "<td><button class='button but3' id='rmt"+v+"3' onclick='toggleCheckbox("+v+"3);'>"+v+"</button></td>"
        rowtext[3][t] = "<td><button class='button but4' id='rmt"+v+"4' onclick='toggleCheckbox("+v+"4);'>"+v+"</button></td>"
        rowtext[4][t] = "<td><button class='button but5' id='rmt"+v+"5' onclick='toggleCheckbox("+v+"5);'>"+v+"</button></td>"
        rowtext[5][t] = "<td><button class='button but6' id='rmt"+v+"6' onclick='toggleCheckbox("+v+"6);'>"+v+"</button></td>"
    }     
  for(let j=0;j<mysetdev;j++)  //6
      {row = document.getElementById('myDRow'+j.toString());         
      for(let k=0;k<mxsetdev;k++)  //5
        {x0 = row.insertCell(k);        
        x0.innerHTML = rowtext[k][j];  //        
        }      
      }          
      //toggleCheckbox(999);    //request load key character  
}


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
{keyno=parseInt(x/10)-1;
document.getElementById('rmt'+x).style.backgroundColor="yellow";//butcolor[keyno];
PreviousKey=x;  
keytype=x%10;  
toggleCheck(x); //tx key to PLC
norepeat=1;     //get display once 
}

function FBhandledisplay(responseText,x)
{let disptext=responseText.substring(8,24);     
if(disptext[0]==='O' && disptext[1]==='N')
  document.getElementById('rmt'+PreviousKey).style='border:3px solid #c51919;width:'+WW+'px;height:'+HH+'px';
else
  document.getElementById('rmt'+PreviousKey).style='border:0px solid #c51919;width:'+WW+'px;height:'+HH+'px';        
} 

var WW;
var HH;

function handleInitKey(responseText){
  var keyv="";
  var k=1;
  var t=10;
  let tmpic="";
  const  tx=['140','140','100','80','60','50','53'];
  const  ty=['130','130','120','70','45','45','45','40'];  
  if(responseText[3]=='d')
  {for(j=20;j<100;j++)
    {if(responseText[j]==='*' && responseText[j+1]==='$' && responseText[j+2]==='^')  
      {
        mxsetdev=responseText[j+3];
        mysetdev=responseText[j+4];
        WW=tx[mxsetdev];
        HH=ty[mysetdev];
        keyv="";
        loadkeytable2();             
        for(let y=1;y<=mysetdev;y++)
          {for(let x=1;x<=mxsetdev;x++) 
            {t=y*10+x;             
            document.getElementById('rmt'+t).style.width=tx[mxsetdev]+'px';     
            document.getElementById('rmt'+t).style.height=ty[mysetdev]+'px';                                 
            }
          }                                                  
        break;                      
      }
    else    
      keyv=keyv+responseText[j];      
    }  
  t=10;  
  for(j=4;j<100;j++)   
    {if(responseText[j]==='@') // && responseText[j+2]=='%')             
      {if(k<=mxsetdev && t<=(mysetdev*10))                                 
        document.getElementById('rmt'+(k+t)).innerText=keyv;            //yx                              
      if(k===6)                        
        ratio[(t/10)-1]=keyv;                    //store a value 
      ////////////
      keyv=""; 
      if(k++>=6)
        {k=1;
        t=t+10;
        }
      if(t>80)                       
        break;                      
      }
    else
      keyv=keyv+responseText[j];                                                                                                                                                                                                
    }
  }
if(responseText[3]=='o')
  {
  document.getElementById('disp').value=responseText[4]+responseText[5]; 
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
  //URL="192.168.1.112";
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
    border: none;
    color:  rgb(214, 207, 202);
    padding: 5px 5px;
    text-align: justfy;
    text-decoration: none;
    display: inline-block;
    font-size: 14px;
    margin: 3px 3px;
    width:53px;
    height:30px;
    cursor: pointer;   
    border-radius: 12%;
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
    border-width: 2px;
    margin-bottom: 15px;
    border-radius: 10%;
    }
</style>
</html>
)rawliteral";