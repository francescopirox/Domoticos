#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Francescopirox2.4";
const char* password = "Rogliano99@It";
const byte pin = 4;
const char* ip = "192.168.0.50";
long time1 = 0;
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  pinMode(pin, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
 
    delay(500);
    Serial.println("Connecting.. ");
    
  }
  Serial.println("Connesso");
 
}
 
void loop() {
  
int w=0;

w = Watt();
sendHttp(w); 
}


void sendHttp(int w){

   
  if (WiFi.status() == WL_CONNECTED and w!=0) { //Check WiFi connection status
    
    
 
    HTTPClient http;  //Declare an object of class HTTPClient
    String httpReq = "http://"+String(ip)+"/script.php?w=" + String(w);
    http.begin(httpReq);  //Specify request destination
    http.GET();
    http.end();   //Close connection
      Serial.println(httpReq);
   } /* else{
    delay(1000); 
  */ 
  }



 int Watt(){
  long time2 = 0;
  long deltaTime = 0;
    
  int agg = 0;
  int watt = 0;

   while(digitalRead(pin) == HIGH){
   time2=millis();
   //Serial.println (millis()) ;
   }
  
    if(digitalRead(pin) == LOW){
      deltaTime = time2 - time1;
      
      if (deltaTime >50 ){
        //Serial.println (deltaTime) ;
        time1 = time2;
        agg = 1;
         }
    
     if (agg == 1){
      
      watt = 3600000/deltaTime;
     // Serial.print(watt);
      //Serial.println(" watt");
      agg = 0;
     }
     else
      {
        watt=0;
        }
      delay(10);
       return watt;  
 }
}
 




