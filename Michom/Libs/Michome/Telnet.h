#ifndef Telnet_h
#define Telnet_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#define MAX_SRV_CLIENTS 4
#define NullString "NullStringT"

// ansi stuff, could always use printf instead of concat
#define ansiPRE  "\033" // escape code
#define ansiHOME "\033[H" // cursor home
#define ansiESC  "\033[2J" // esc
#define ansiCLC  "\033[?25l" // invisible cursor

#define ansiEND  "\033[0m"   // closing tag for styles
#define ansiBOLD "\033[1m"

#define ansiRED  "\033[41m" // red background
#define ansiGRN  "\033[42m" // green background
#define ansiBLU  "\033[44m" // blue background

#define ansiREDF "\033[31m" // red foreground
#define ansiGRNF "\033[34m" // green foreground
#define ansiBLUF "\033[32m" // blue foreground
#define BELL     "\a"

#define ansiClearScreen (ansiHOME+ansiCLC)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

class Telnet
{
        public:
                //Объявление класса
                Telnet(int port);
                //
                String GetData();
                //
                bool IsDataAvalible();
                //
                void Running();
                //
                void print(String text);
                //
                void println(String text);
                //
                String read(){
                    return GetData();
                }
                //
                void Init();
                
        private:
            bool IsReadConfig = false;
            WiFiClient serverClients[MAX_SRV_CLIENTS];
            String RD = NullString;
            
};
#endif // #ifndef Telnet_h