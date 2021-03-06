//******************************** Define web handle root function ************************

// Define variable 
String __username ;
String __password;
String __ssid;
String __pass;

// main page
void handleIndex(){server.send(200, "text/html", htmlPage);}
void handleCSS(){server.send(200, "text/css", stylePage);}
void handleJS(){server.send(200, "text/js", appJS);}

// login page
void handleLoginPage(){server.send(200, "text/html", loginIndex);}
void handleLoginCSS() {server.send(200, "text/css", loginStyle);}
void handleLoginJS()  {server.send(200, "text/js", loginJS);}

// register page
void handleRegisterPage(){server.send(200, "text/html", registerIndex);}
void handleRegisterCSS() {server.send(200, "text/css", registerStyle);}
void handleRegisterJS()  {server.send(200, "text/js", registerJS);}
//******************************************************************************************************

// register data qeury
void handleRegisterQuery(){
  
// get argument
  if(server.hasArg("username")) __username = server.arg("username");
  if(server.hasArg("password")) __password = server.arg("password");
  if(server.hasArg("ssid"))     __ssid     = server.arg("ssid");
  if(server.hasArg("ssidpass")) __pass     = server.arg("ssidpass");
  
// save argument to eeprom
  writeString(0, __username);
  delay(200);
  writeString(50,__password);
  delay(200);
  writeString(100, __ssid);
  delay(200);
  writeString(150, __pass);
  delay(200);
  
  Serial.println("==============resieve data=================");
  Serial.println(server.arg("username"));
  Serial.println(server.arg("password"));
  Serial.println(server.arg("ssid"));
  Serial.println(server.arg("ssidpass"));
  
  server.send(202);
  Serial.println("Restart ...");
  // write state work = 1 to connect to home wireless network and restart ESP8266
  writeInteger(200, 1);
  ESP.restart();
}
  
void handleRootQuery(){
  server.send(200);
  if(server.hasArg("threshold")) {
    lightThreshold = server.arg("threshold").toInt();
   }
  if(server.hasArg("brightness")) {
    lightBrightness = server.arg("brightness").toInt();
   }
  if(server.hasArg("lamp")){
    if(server.arg("lamp").toInt() == 1) lightStatus = 1;
    if(server.arg("lamp").toInt() == 0) lightStatus = 0;
  }
}

void handleLight() {
  server.send(200, "text/json", "{\"response\":" + String(light) + "}"); 
}
void handleLightThreshold() {
  server.send(200, "text/json", "{\"response\":" + String(lightThreshold) + "}"); 
}
void handleLightBrightness() {
  server.send(200, "text/json", "{\"response\":" + String(lightBrightness) + "}"); 
}
void handleStatus() {
  lightWork == 0 ?
    server.send(200, "text/json", "{\"response\": \"OFF\"}"):
    server.send(200, "text/json", "{\"response\": \"ON\"}");
}
