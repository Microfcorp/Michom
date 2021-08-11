#include "Telnet.h"

WiFiServer servT(23);

//Объявление класса
Telnet::Telnet(int port){
    servT = WiFiServer(port);                    
};
//
String Telnet::GetData(){
    if(!IsDataAvalible()) return "";

    String tm = RD;
    RD = NullString;
    return tm;
};
//
bool Telnet::IsDataAvalible(){
    return RD != NullString;
};
//
void Telnet::Running(){
    uint8_t i;
    //check if there are any new clients
    if (servT.hasClient()) {
        //find free/disconnected spot
        for(i = 0; i < MAX_SRV_CLIENTS; i++){
            if (!serverClients[i] || !serverClients[i].connected()) {
                if (serverClients[i]) serverClients[i].stop();
                serverClients[i] = servT.available();
                //serverClients[i].setTimeout(100);
                serverClients[i].println("Michome module Telnet");
                //continue;
            }
        }
        //no free/disconnected spot so reject
        //WiFiClient serverClient = servT.available();
        //serverClient.println("Helloy");
        //serverClient.stop();
    }    

    for(i = 0; i < MAX_SRV_CLIENTS; i++){
        if (serverClients[i] && serverClients[i].connected()) {
            if (serverClients[i].available()) {
                RD = serverClients[i].readStringUntil('\t');                           
                //yield();
            }
        }   
    }    
};
//
void Telnet::Init(){
    servT.begin();
    servT.setNoDelay(true);
};
//
void Telnet::print(String text){
    serverClients[0].print(text);
};
//
void Telnet::println(String text){
    serverClients[0].println(text);
};