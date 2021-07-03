#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#import "./client/index.h"
#import "./client/app.h"
#import "./client/style.h"

#define LIGHTSENSORPIN A0
#define PWMPIN D5

// Define variable
unsigned long startMillis;  
unsigned long currentMillis;
const unsigned long period = 2000;  
int light;
int lightStatus = 0;
int lightBrightness = 50;
int lightThreshold = 50;

IPAddress staticIP(192, 168, 1, 50);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);


//================================== Function decelaration ===================================
void handleRoot() {
  if (server.args()){
    handleQuery();
  }else{
    server.send(200, "text/html", htmlPage);
  }
}
void handleCSS(){
  server.send(200, "text/css", stylePage);
}
void handleJS(){
  server.send(200, "text/js", appJS);
}

void handleLight() {
  server.send(200, "text/json", "{\"response\":" + String(light) + "}"); //Send web page
}
void handleStatus() {
  if(lightStatus == 0){
    server.send(200, "text/json", "{\"response\": \"OFF\"}");
  }else{
    server.send(200, "text/json", "{\"response\": \"ON\"}");
  }
  
}
void handleQuery(){
  if (server.hasArg("threshold")) {
      Serial.println("lightThreshold");
      lightThreshold = server.arg("threshold").toInt();
      Serial.println(lightThreshold);
      // analogWrite(D5, result);
    }
  if(server.hasArg("brightness")){
    lightBrightness = server.arg("brightness").toInt();
    Serial.println("lightBrightness");
    Serial.println(lightBrightness);
  }
  if(server.hasArg("lamp")){
    if(server.arg("lamp").toInt() == 1){
      lightStatus = 1;
    }
    if(server.arg("lamp").toInt() == 0){
      lightStatus = 0;
    }
    Serial.println("lightStatus");
    Serial.println(lightStatus);
  }
}


//  ================================= setup function ====================================
void setup() {
  pinMode(LIGHTSENSORPIN, INPUT);

  Serial.begin(115200);
  Serial.println();


  analogWriteFreq(55);

  //WiFi.config(staticIP, gateway, subnet);

  //WiFi.begin("Navid", "wWw.shatel.@com");
  WiFi.begin("quadrotor", "12345678");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  WiFi.hostname("IOT");
  Serial.printf("New hostname: %s\n", WiFi.hostname().c_str());
  Serial.println();
  Serial.print("Connected , Ip address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/app.js", handleJS);
  server.on("/light", handleLight);
  server.on("/status", handleStatus);
  server.begin();
  Serial.println("HTTP server started");
  
  startMillis = millis();  
}
//=====================================================================
void loop() {
  
  server.handleClient();
  
  currentMillis = millis();
  if (currentMillis - startMillis >= period) {
      light = analogRead(LIGHTSENSORPIN);
      //Serial.println(light);  
      startMillis = currentMillis;  
  }
  
  
 
}
