IPAddress local_IP (192,168,1,1);
IPAddress staticIP (192, 168, 1, 50);
IPAddress gateway  (192, 168, 1, 1);
IPAddress subnet   (255, 255, 255, 0);

void connetToWifi(String ssid, String password, String hostName){ 
 
  //WiFi.config(staticIP, gateway, subnet);

  WiFi.begin(ssid, password);
  WiFi.hostname(hostName);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.printf("New hostname: %s\n", WiFi.hostname().c_str());
  Serial.println();
  Serial.print("Connected , Ip address: ");
  Serial.println(WiFi.localIP());
}
