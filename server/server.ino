#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#import "./client/index.h"
#import "./client/app.h"
#import "./client/style.h"

#define LIGHTSENSORPIN A0
#define PWMPIN D5

unsigned long startMillis;  
unsigned long currentMillis;
const unsigned long period = 2000;  
int Light = 0;

IPAddress staticIP(192, 168, 1, 50);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);


//================================== Function decelaration ===================================
void handleRoot() {
  server.send(200, "text/html", htmlPage);
  handleQuery();
}
void handleCSS(){
  server.send(200, "text/css", stylePage);
}
void handleJS(){
  server.send(200, "text/js", appJS);
}

void handleLight() {
  String lightString = String(Light);
  server.send(200, "text/json", "{\"response\":" + lightString + "}"); //Send web page
}
void handleStatus() {
  server.send(200, "text/json", "{\"response\": \"ON\"}");
}
void handleQuery(){
  if (server.arg("threshold")) {
      int result = server.arg("threshold").toInt() * 2.5 ;
      Serial.println(result);
      analogWrite(D5, result);
    }
    Serial.println(server.arg("brightness"));
    Serial.println(server.arg("lamp"));
}


//  ================================= setup function ====================================
void setup() {
  pinMode(LIGHTSENSORPIN, INPUT);

  Serial.begin(115200);
  Serial.println();


  analogWriteFreq(55);

  //WiFi.config(staticIP, gateway, subnet);

  WiFi.begin("Navid", "wWw.shatel.@com");
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
      Light = analogRead(LIGHTSENSORPIN);
      Serial.println(Light);  
      startMillis = currentMillis;  
  }
  
  
 
}
