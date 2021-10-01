#ifndef MichomUDP_h
#define MichomUDP_h

#include <Michom.h>
//#include <ESP8266WiFi.h>
//#include <WiFiUdp.h>
//#include <RTOS.h>

#include <LightModules.h>
#include <TimerLightModule.h>

typedef enum ActionsType {LightData, SendURL, SendGateway};

typedef struct UDPTriggers
{
    String Type;
    ActionsType ActionType;
    String Data;
    bool Enable;
};

class MichomeUDP
{
        public:
            String id; String type; bool timerLightModule = false;
            LightModules *lightModules;
            TimerLightModule *timerLightModules;
            bool EAlarm; bool ENightLight; bool EOverCold; bool EOverHot;
            
            MichomeUDP(Michome *gtwa){
                id = (*gtwa).GetModule(0);
                type = (*gtwa).GetModule(1);
                gtw = gtwa;
				(*gtwa).SetOptionFirmware(UDPTrigger, true);
            }
            
            void init();

            void running(void);
            
            void Save(void);
            
            void Load(void);
            
            void SendUDP(IPAddress ip, String data);
            
            void SendUDP(IPAddress ip, int Port, String data);
            
            String Split(String data, char separator, int index);
            
            String GetData_Discover(){
                return "Michome_" + WiFi.localIP().toString();
            }
            
            String GetData_SearchOK(){
                return "SearchOK_" + type + "-" + WiFi.localIP().toString();
            }
            
            String GetData_MyType(){
                return "Module_" + id + "-" + type;
            }
            
            String GetData_OK(){
                return type + "-" + id + "_OK";
            }
            
            String GetData_EventsList(){
                String tmp = "";                           
                tmp += (EAlarm ? "EAlarm|" : "");
                tmp += (ENightLight ? "ENightLight|" : "");
                tmp += (EOverCold ? "EOverCold|" : "");
                tmp += (EOverHot ? "EOverHot|" : "");
                for(int i = 0; i < Ut.size(); i++){
                    UDPTriggers tr = Ut.get(i);
                    tmp += tr.Type + "|";
                }  
                return (tmp == "" ? "None Events" : tmp);
            }
            
            String GetData_Event_OK(String Event){
                return "Event_"+Event+"_OK";
            }
            
            String GetHTMLOptions(int t){
                String tmp = "";
                tmp += (type == StudioLight ? (String)"<option "+(t == 0 ? "selected":"")+" value='LightData'>Telnet формат модуля освещения</option>" : "");
                tmp += (String)"<option "+(t == 1 ? "selected":"")+" value='SendURL'>Отпрвить URL</option>";
                tmp += (String)"<option "+(t == 2 ? "selected":"")+" value='SendGateway'>Отправить данные на шлюз</option>";
                return tmp;
            }
            
            void SendMulticast(String data);
        private:
            WiFiUDP UDP;
            unsigned int localUdpPort = 4210;
            unsigned int MulticastUdpPort = 4244;
            char incomingPacket[255];
            char replyPacekt[30];
            FSFiles fstext = FSFiles("/UDP.txt");
            IPAddress broadcast = IPAddress(224, 0, 1, 3); //224.0.1.3
            RTOS Discover;
            Michome *gtw;
            LinkedList<UDPTriggers> Ut = LinkedList<UDPTriggers>();
};
#endif // #ifndef MichomUDP_h