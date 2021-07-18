//******************************** Define web handle root function ************************

void handleIndex(){server.send(200, "text/html", htmlPage);}
void handleCSS(){ server.send(200, "text/css", stylePage);}
void handleJS(){server.send(200, "text/js", appJS);}

void handleLoginPage(){server.send(200, "text/html", loginIndex);}
void handleLoginCSS(){server.send(200, "text/css", loginStyle);}
void handleLoginJS(){server.send(200, "text/js", loginJS);}

void handleRegisterPage(){server.send(200, "text/html", registerIndex);}
void handleRegisterCSS(){server.send(200, "text/css", registerStyle);}
void handleRegisterJS(){server.send(200, "text/js", registerJS);}

void handleRegisterQuery(){
  if(server.hasArg("username")) _default_username = server.arg("username");
  if(server.hasArg("password")) _default_password = server.arg("password");
  if(server.hasArg("ssid"))     _default_ssid     = server.arg("ssid");
  if(server.hasArg("ssidpass")) _default_pass     = server.arg("ssidpass");

  Serial.println(server.arg("username"));
  Serial.println(server.arg("password"));
  Serial.println(server.arg("ssid"));
  Serial.println(server.arg("ssidpass"));

  server.send(202);
}
  
void handleMain(){handleIndex();}
void handleResponse(){if(!handleRootQuery()){handleIndex();}}

void handleRoot() {
  Serial.println(server.header("Authorization"));
  if(!server.hasHeader("Authorization")){return handleLoginPage();}
  
  //server.authenticate(_username, _password)? handleResponse() : server.send(403);
}

bool handleRootQuery(){
  if(server.hasArg("threshold")) {
    lightThreshold = server.arg("threshold").toInt();
    return true;
   }
  if(server.hasArg("brightness")) {
    lightBrightness = server.arg("brightness").toInt();
    return true;
   }
  if(server.hasArg("lamp")){
    if(server.arg("lamp").toInt() == 1) lightStatus = 1;
    if(server.arg("lamp").toInt() == 0) lightStatus = 0;
    return true; 
  }
  
  return false;
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
  lightStatus == 0 ?
    server.send(200, "text/json", "{\"response\": \"OFF\"}"):
    server.send(200, "text/json", "{\"response\": \"ON\"}");
}
