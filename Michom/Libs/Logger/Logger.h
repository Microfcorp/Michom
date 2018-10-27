#ifndef Logger_h
#define Logger_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class Logger
{
        public:
                Logger(const char* gateway, const char* host);
                void Log(String text);
		private:
				const char* Gateway;
				const char* Host;
				String parsejson(String type, String data);
};

#endif // #ifndef Logger_h