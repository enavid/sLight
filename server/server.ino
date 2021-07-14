#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#import "./client/login/loginIndex.h"
#import "./client/login/loginStyle.h"
#import "./client/login/loginJS.h"

#import "./client/index/index.h"
#import "./client/index/app.h"
#import "./client/index/style.h"

#define LIGHTSENSORPIN A0
#define PWMPIN D5

// Define variable
unsigned long startMillis;  
unsigned long currentMillis;
const unsigned long period = 2000;  
float light;
int lightStatus = 0;
int lightBrightness = 50;
int lightThreshold = 50;
int stateWork = 1; //0 for Register state 1 for normal state
int stateReponse = 1; //0 send login page 1 send normal page;

String userName = "admin";
String password = "admin";

IPAddress staticIP(192, 168, 1, 50);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);


//================================== Function decelaration ===================================

//************************************* handle Function8 ***********************************
void handleIndex(){
  if(stateReponse == 0)return server.send(200, "text/html", loginIndex);
  if(stateReponse == 1)return server.send(200, "text/html", htmlPage);
}

void handleCSS(){
  if(stateReponse == 0)return server.send(200, "text/css", loginStyle);
  if(stateReponse == 1)return server.send(200, "text/css", stylePage);
  
}
void handleJS(){
  if(stateReponse == 0)return server.send(200, "text/js", loginJS);
  if(stateReponse == 1)return server.send(200, "text/js", appJS);
}

void handleRoot() {
  server.args()? server.send(200), handleRootQuery(): handleIndex();
 
}
//************************************* handle Function ***********************************

void handleRootQuery(){
     Serial.println(server.arg("password"));
     Serial.println(server.arg("username"));
  
  if (server.hasArg("threshold")) lightThreshold = server.arg("threshold").toInt();
  if(server.hasArg("brightness")) lightBrightness = server.arg("brightness").toInt();
  
  if(server.hasArg("lamp")){
    if(server.arg("lamp").toInt() == 1) lightStatus = 1;
    if(server.arg("lamp").toInt() == 0) lightStatus = 0; 
  }
}






void handleLight() {
  server.send(200, "text/json", "{\"response\":" + String(light) + "}"); //Send web page
}
void handleLightThreshold() {
  server.send(200, "text/json", "{\"response\":" + String(lightThreshold) + "}"); //Send web page
}
void handleLightBrightness() {
  server.send(200, "text/json", "{\"response\":" + String(lightBrightness) + "}"); //Send web page
}
void handleStatus() {
  if(lightStatus == 0){
    server.send(200, "text/json", "{\"response\": \"OFF\"}");
  }else{
    server.send(200, "text/json", "{\"response\": \"ON\"}");
  }
  
}


bool authorizationUser(String username, String password){
  return userName.equals(username) && password.equals(password);
}

int checkStateResponse(){
  
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
  server.on("/lightThreshold", handleLightThreshold);
  server.on("/lightBrightness", handleLightBrightness);
  server.begin();
  Serial.println("HTTP server started");
  
  startMillis = millis();  
}
//=====================================================================
void loop() {
  
  server.handleClient();
  currentMillis = millis();
  if (currentMillis - startMillis >= period) {
      light = analogRead(LIGHTSENSORPIN) * 0.0976;
      Serial.println(light);  
      startMillis = currentMillis;  
  }

  if(lightStatus){
    analogWrite(D5, lightBrightness * 2.6);
    if(light > lightThreshold){
      lightStatus = 0;
    }
  }else{
    analogWrite(D5, 0);
  }

}
