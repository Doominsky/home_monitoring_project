#include <SoftwareSerial.h>
#include <stdlib.h>
#include <ESP8266_Lib.h>
SoftwareSerial ESPserial(7, 8); // RX, TX

#define DEBUG true

int error;
String incomingData;
char serialData;

void setup()
{
  Serial.begin(115200);
  ESPserial.begin(9600);
}

void loop()
{
  start:
  error = 0;
  char buffer[10];

  if(error==1) goto start;
   while (ESPserial.available()>0){
      serialData = ESPserial.read();   
      //if(serialData=='\n') break;
      //else incomingData += serialData;
      incomingData += serialData;
      Serial.print(incomingData);

      incomingData = "";
      serialData = 0;
    }
  delay(30000);
}
