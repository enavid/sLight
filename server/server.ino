#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LIGHTSENSORPIN A0
#define button D0
#define PWMPIN D5

//********************************* Add external file to programm ************************
#import "./client/register/registerIndex.h"
#import "./client/register/registerStyle.h"
#import "./client/register/registerJS.h"

#import "./client/login/loginIndex.h"
#import "./client/login/loginStyle.h"
#import "./client/login/loginJS.h"

#import "./client/index/index.h"
#import "./client/index/app.h"
#import "./client/index/style.h"

#import "./utilities/eepromFunction.h"
#import "./utilities/manageNetwork.h"

//***************************************** Define global variable ************************

int lightStatus     = 0;
int lightBrightness = 50;
int lightThreshold  = 50;
float light;

String _username   = "admin";
String _password   = "admin";
String _ssid       = "Navid";
String _pass       = "wWw.shatel.@com";
int    _stateWork  = 0;

unsigned long startMillis;  
unsigned long currentMillis;
const unsigned long period = 2000; 

ESP8266WebServer server(80);

//  ================================= setup function ====================================
void setup() {
  
//************************ Initialize modules **************************
  EEPROM.begin(512);
  Serial.begin(115200);
  pinMode(LIGHTSENSORPIN, INPUT);
  pinMode(button, OUTPUT); 
  digitalWrite(button, LOW); 
  analogWriteFreq(55);

//******************** Reading data from eeprom ***********************
  _username  = read_String(0);
  _password  = read_String(50);
  _ssid      = read_String(100);
  _pass      = read_String(150);
  _stateWork = readInteger(200);
  
//************************** Set up Access point *************************

  // state work = 0 for create Access point
  if(_stateWork == 0 ){ createAccessPoint("smart light");}
  // state work = 1 for connect to home wirelless network
  if(_stateWork == 1){ connetToWifi(_ssid, _pass, "IOT");}

  Serial.println(_username);
  Serial.println(_password);
  Serial.println(_ssid);
  Serial.println(_pass);
  Serial.println(_stateWork);
//**************************** Handle web address *******************************
if(_stateWork == 0 ){
  //Handle register page
  server.on("/", handleRegisterPage);
  server.on("/register.css", handleRegisterCSS);
  server.on("/register.js", handleRegisterJS);
  server.on("/setdata", handleRegisterQuery);
}
else if(_stateWork == 1){
  //Handle root request
  server.on("/", handleIndex);
  server.on("/data", handleRootQuery);
  server.on("/login", handleLoginPage);
  server.on("/register", handleRegisterPage);
  server.on("/register/setdata", handleRegisterQuery);

  //Handle css request
  server.on("/style.css", handleCSS);
  server.on("/login.css", handleLoginCSS);
  server.on("/register.css", handleRegisterCSS);
  
  //Handle javascript request
  server.on("/app.js", handleJS);
  server.on("/login.js", handleLoginJS);
  server.on("/register.js", handleRegisterJS);
  
  //Query data
  server.on("/light", handleLight);
  server.on("/status", handleStatus);
  server.on("/lightThreshold", handleLightThreshold);
  server.on("/lightBrightness", handleLightBrightness);

}
  // Begin server
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
      //Serial.println(light);  
      startMillis = currentMillis;  
  }

  if(lightStatus){
    analogWrite(D5, lightBrightness * 2.6);
    if(light > lightThreshold){lightStatus = 0;}
  }else{
    analogWrite(D5, 0);
  }

  if(digitalRead(button) == HIGH){
    delay(100);
    if(digitalRead(button) == HIGH){
      writeInteger(200, 0);
      delay(1000);
      ESP.restart();
    }
  }

}
