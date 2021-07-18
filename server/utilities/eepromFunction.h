#include <EEPROM.h>
//  usernamae in EEPROM address 0
//  passwowrd in EEPROM address 50
//  ssid      in EEPROM address 100
//  pass      in EEPROM address 150
// stateWork  in EEPROM address 200

//************************************************* Define function **************************************

void writeString(char add,String data)
{
  int _size, i;
  
  _size = data.length();
  
  for(i = 0; i < _size; i++){
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0'); 
  EEPROM.commit();
}

String read_String(char add)
{
  int i, len = 0;
  char data[100]; 
  unsigned char k;
  
  k = EEPROM.read(add);
  while(k != '\0' && len<500)   
  {    
    k = EEPROM.read(add+len);
    data[len] = k;
    len = len + 1;
  }
  data[len] = '\0';
  return String(data);
}

void writeInteger(char add, int data){
  EEPROM.write(add, data);
  EEPROM.commit();
}

int readInteger(char add){
  return EEPROM.read(add);
}
