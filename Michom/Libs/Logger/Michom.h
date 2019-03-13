#ifndef Michom_h
#define Michom_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Logger.h>

class Michome
{
        public:
                Michome(const char* _ssid, const char* _password, const char* _id, const char* _type, const char* _host, const char* _host1);
                String SendDataGET(String gateway, const char* host, int Port);
				String SendDataPOST(const char* gateway, const char* host, int Port, String Data);
                String SendData(String Data);
                void init(void);
                void running(void);
                ESP8266WebServer& GetServer();
                //String GetJson();
                String ParseJson(String type, String data);
        private:
            const char* ssid; const char* password; const char* id; const char* type; const char* host; const char* host1;
            MDNSResponder mdns;
};
//extern ESP8266WebServer server;
#endif // #ifndef Michom_h