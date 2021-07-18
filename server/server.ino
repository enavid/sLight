#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#define LIGHTSENSORPIN A0
#define PWMPIN D5

//***************************************** Add external file to programm ************************
#import "./client/register/registerIndex.h"
#import "./client/register/registerStyle.h"
#import "./client/register/registerJS.h"

#import "./client/login/loginIndex.h"
#import "./client/login/loginStyle.h"
#import "./client/login/loginJS.h"

#import "./client/index/index.h"
#import "./client/index/app.h"
#import "./client/index/style.h"

//***************************************** Define global variable ************************

int lightStatus = 0;
int lightBrightness = 50;
int lightThreshold = 50;
float light;

String _username = "admin";
String _password = "admin";
String _ssid     = "Navid";
String _ssidPass = "wWw.shatel.@com";



unsigned long startMillis;  
unsigned long currentMillis;
const unsigned long period = 2000;  

IPAddress staticIP(192, 168, 1, 50);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);



//  ================================= setup function ====================================
void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  pinMode(LIGHTSENSORPIN, INPUT);

  
  Serial.println();

  analogWriteFreq(55);

  //WiFi.config(staticIP, gateway, subnet);

  WiFi.begin(_ssid, _ssidPass);
  
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
// ======================================= wirte EEPROM  ===================================  
  writeString(0,"Na");
  delay(100);
//  writeString(50, _password);
//  delay(100);
//  writeString(100, _ssid);
//  delay(100);
//  writeString(150, _ssidPass);
//  delay(100);
  
  String username = read_String(0);
  String password = read_String(50);
  String ssid     = read_String(100);
  String ssidPass = read_String(150);

  Serial.println(username);
  Serial.println(password);
  Serial.println(ssid);
  Serial.println(ssidPass);
  

//======================================== Handle web root call ===========================
  //Handle root request
  server.on("/", handleRoot);
  server.on("/main", handleMain);
  server.on("/register", handleRegisterPage);
  server.on("/register-data", handleRegisterQuery);

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
    if(light > lightThreshold){
      lightStatus = 0;
    }
  }else{
    analogWrite(D5, 0);
  }

}
