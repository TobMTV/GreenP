#include <EtherCard.h>
#include <dht.h>
#include <math.h>

//+++++++++++++Setto ethernet shield++++++++++++++++++++
static byte mymac[] =  {0x74,0x69,0x64,0x2D,0x30,0x32};
byte Ethernet::buffer[700];
static byte myip[] = {192,168,2,200};

//+++++++++++++Setto DHT++++++++++++++++++++
dht DHT;
int lampo=0;
int pumpet=0;
int autoPumpe=1; //Se in modalita automatica
int autoLamp=1;

void setup () { //Eseguo il setup la prima volta

  //Presetto il pin per pompetta rele
  pinMode(04, OUTPUT);
  //Presetto il pin Fotoresistenza
  pinMode(A1,INPUT);
  //Presetto pin per luce rele  
  pinMode(06,OUTPUT); 
  //Presetto pin temp/hum
  pinMode(A0, OUTPUT); 
 
  
  if (ether.begin(sizeof Ethernet::buffer, mymac,10) == 0) // Controllo il buffer e gli passo il pin e il mac 
    Serial.println("Failed to access Ethernet controller");
  if(!ether.staticSetup(myip))
    Serial.println("Falied to set IP address");
   
}
//+++++++++++FotoResistenza Function++++++++ LOW --> fa passsare corrente, HIGH --> blocca corrente
int FotoRes(){
 int val = analogRead(A1); // salvo il valore fotoresistenza dentro alla variabile val

 if(val < 80 && autoLamp == 1){ //se il valore letto dalla fotoresistenza (luminosità) è basso, accendo il led
   lampo=1;
   digitalWrite(06,LOW);
 }
 if(val >= 80 && autoLamp == 1){
    lampo=0;
   digitalWrite(06,HIGH);
 }
 return val;
}


//+++++++++++Humidity & Temp Function++++++++
double humidityF(){ //40% PIANTE CACTACEE E 60% OTHER PIANTE, PER AUMENTARE L'UMIDITA PRENDO GHIAINO E LO METTO NEL VASSOIO SOTTO LA PIANTA, L'ACQUA NON DEVE SUPERARE IL LIVELLO DEL GHIAINO
 DHT.read11(A0);
  if(DHT.humidity > 50 && autoPumpe == 1){
    pumpet = 1;
    digitalWrite(04,LOW);
  }
  if(DHT.humidity <= 50 && autoPumpe ==1){
    pumpet= 0;
    digitalWrite(04,HIGH);
  }
    return DHT.humidity;
}
/*
megatermiche, cioè piante che vivono al di sopra dei 20°;
mesotermiche, cioè piante che vivono tra i 20° e i 15°:
microtermiche, cioè piante che vivono tra 0° e 15°:
echistotermiche, cioè piante che riescono a vivere al di sotto di 0° andando in una sorta di letargo con l'interruzione della loro crescita e la perdita delle foglie, se si tratta di piante a foglie caduche, o senza la loro perdita, in caso di sempreverdi.

*/
double TemperatureF(){
 DHT.read11(A0);

    return DHT.temperature;
}

static word homePage() {
 
 long t = millis() / 1000;
 word h = t / 3600;
 byte m = (t / 60) % 60;
 byte s = t % 60;
 char HumidityChar[10];
 char TemperatureChar[10];
 
 //Converto i duble delle funzioni in char per HTML
 dtostrf(humidityF(),2,2,HumidityChar);
 dtostrf(TemperatureF(),2,2,TemperatureChar);

 
  
 
 BufferFiller bfill = ether.tcpOffset();   
 
 if(lampo == 1 && pumpet == 1)
 bfill.emit_p(PSTR("temp:$S-hum:$S-lum:$D-lampadinaSwitch:ON-pompaSwitch:ON-autoPum:$D-autoLamp:$D"),
    TemperatureChar, HumidityChar, FotoRes(),autoPumpe,autoLamp);
if(lampo== 0 && pumpet == 1){
  bfill.emit_p(PSTR("temp:$S-hum:$S-lum:$D-lampadinaSwitch:OFF-pompaSwitch:ON-autoPum:$D-autoLamp:$D"),
    TemperatureChar, HumidityChar, FotoRes(),autoPumpe,autoLamp);
} 
if(lampo== 1 && pumpet == 0){
  bfill.emit_p(PSTR("temp:$S-hum:$S-lum:$D-lampadinaSwitch:ON-pompaSwitch:OFF-autoPum:$D-autoLamp:$D"),
    TemperatureChar, HumidityChar, FotoRes(),autoPumpe,autoLamp);
}
if(lampo== 0 && pumpet == 0){
  bfill.emit_p(PSTR("temp:$S-hum:$S-lum:$D-lampadinaSwitch:OFF-pompaSwitch:OFF-autoPum:$D-autoLamp:$D"),
    TemperatureChar, HumidityChar, FotoRes(),autoPumpe,autoLamp);
}
 return bfill.position();                                           
} 


void loop() {
 
  int state=0;
  
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
 if(pos) { //Se c'è qualcosa
 
  
     //____Setta il valore se automatico della pompetta
     if(strstr((char *)Ethernet::buffer + pos, "GET /?autoPump=1") != 0){
       autoPumpe = 1;
      
     }
     if(strstr((char *)Ethernet::buffer + pos, "GET /?autoPump=0") != 0){
       autoPumpe = 0;
        
     }
     //_____Setta il valore se automatico della lucetta
      if(strstr((char *)Ethernet::buffer + pos, "GET /?autoLamp=1") != 0){
       autoLamp = 1;
  
     }
     if(strstr((char *)Ethernet::buffer + pos, "GET /?autoLamp=0") != 0){
       autoLamp = 0;
      
     }
     
     int app= FotoRes();
     double appU = humidityF();
     
     
     //_______ Cambia stato pompetta se non automatico
      if(strstr((char *)Ethernet::buffer + pos, "GET /?pump=true") != 0 && autoPumpe== 0 ){
       pumpet = 1;
       digitalWrite(04,LOW); // accendi la pompetta
     }
     
     if(strstr((char *)Ethernet::buffer + pos, "GET /?pump=false") != 0 && autoPumpe== 0 ){
       pumpet = 0;
       digitalWrite(04,HIGH); //spegni la pompetta
     }
     //_______ Cambia stato luce se non automatico
      if(strstr((char *)Ethernet::buffer + pos, "GET /?lamp=true") != 0 && autoLamp== 0 ){
       lampo = 1;
       digitalWrite(06,LOW); // accendi la lampadina
     }
     
     if(strstr((char *)Ethernet::buffer + pos, "GET /?lamp=false") != 0 && autoLamp== 0 ){
       lampo = 0;
       digitalWrite(06,HIGH); //spegni la lampadina
     }
     
   ether.httpServerReply(homePage());   
    
  }
}

/* "HTTP/1.0 200 OK\r\n"
   "Content-Type: text/html\r\n"
   "Pragma: no-cache\r\n"
   "\r\n"
   "<meta http-equiv='refresh' content='1'/>"
   "<title>Tobe server</title>" 
   <h1>$D$D:$D$D:$D$D <br>Current Humidity is: 
    h/10, h%10, m/10, m%10, s/10, s%10, HumidityChar, TemperatureChar, FotoRes());
   */
