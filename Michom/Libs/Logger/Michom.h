#ifndef Michom_h
#define Michom_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class Michome
{
        public:
                Michome();
                String SendDataGET(String gateway, const char* host, int Port);
				String SendDataPOST(const char* gateway, const char* host, int Port, String Data);
};

#endif // #ifndef Michom_h