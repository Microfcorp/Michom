#ifndef TimerLightModule_h
#define TimerLightModule_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include <Michom.h>
#include <NTPClient.h>
#include <FSFiles.h>
#include <LightModules.h>

#define UTC3 10800 //Utc+3
#define NTPServer "pool.ntp.org"
#define NTPServerMaxLenght 50
#define NTPTimer 60000
#define MaximumTimers 15

typedef struct TimeLightModuleQ
{
    byte Hour;
    byte Minutes;
    byte Enable;
    byte Pin;
    int State;
    bool IsDynamic;
};

class TimerLightModule
{
        public:
                //Объявление класса
                TimerLightModule(LightModules *m);
                TimerLightModule(){};
                //
                void running();
                //
                void Save();
                //
                void Load();
                //
                void init();
                //
                void Add(TimeLightModuleQ tm);
                //
                void LoadNTP(){
                    String rs = settings.ReadFile();
                    String ntps = (*gtw).Split(rs, ';', 0);
                    int utctime = (*gtw).Split(rs, ';', 1).toInt();
                    if(ntps == "") ntps = NTPServer;
                    if(utctime == 0) utctime = UTC3;
                    ntps.toCharArray(_NTPServer, NTPServerMaxLenght);
                    _utcoffset = utctime;
                    SetNTP();
                }
        private:                       
            Michome *gtw;          
            LinkedList<TimeLightModuleQ> Qs = LinkedList<TimeLightModuleQ>();
            WiFiUDP ntpUDP;
            LightModules *light; 
            FSFiles fstext = FSFiles("/timer.txt");
            FSFiles settings = FSFiles("/tset.txt");
            NTPClient timeClient = NTPClient(ntpUDP, NTPServer, UTC3);
            char* _NTPServer = NTPServer;
            int _utcoffset = UTC3;
            RTOS timers = RTOS(NTPTimer);
            void _running();
            String GetPinsHTML(int pin){
                String tmp = "";
                for(int i = 0; i < (*light).CountPins(); i++){
                    tmp += "<option "+(String)(i==pin ? "selected":"")+" value='"+(String)i+"'>"+(String)i+" ("+((*light).GetPin(i).Type == Relay ? "Relay" : "PWM")+")</option>";
                }
                return tmp;
            }
            void SetNTP(){
                timeClient.setPoolServerName(_NTPServer);
                timeClient.setTimeOffset(_utcoffset);
                timeClient.forceUpdate();
            }
};
#endif // #ifndef TimerLightModule_h