#include "MichomUDP.h"

void MichomeUDP::init(){
    UDP.beginMulticast(WiFi.localIP(), broadcast, MulticastUdpPort);
    Discover = RTOS(1000*60*5);
    Discover.Start();
    SendMulticast(GetData_Discover());    
    //UDP.beginMulticast(WiFi.localIP(), broadcast, localUdpPort);
    //replyPacekt = "Hi there! Got the message :-)";
    
    Load();
    ESP8266WebServer& server1 = (*gtw).GetServer();
    server1.on("/udptrigger", [&](){
        if(server1.arg("type") == "show" || !server1.hasArg("type")){
            String tmp = "";
            for(int i = 0; i < Ut.size(); i++){
                UDPTriggers tr = Ut.get(i);
                tmp += (String)"<tr><form action='/udptrigger'><input name='type' type='hidden' value='save' /><input name='id' type='hidden' value='"+i+"' /><td>Состояние: <input type='checkbox' " + (tr.Enable == 1 ? "checked": "") +" name='en' /></td><td>Тип триггера <input name='TypeTrigger' value='"+tr.Type+"' /></td><td>Действие <select name='ActionType'>"+GetHTMLOptions((int)tr.ActionType)+"</select></td><td>Данные действия <input name='Data' value='"+tr.Data+"' /></td><td><input type='submit' value='Сохранить' /></td><td><a href='/udptrigger?type=remove&id="+i+"'>Удалить</a></td></form></tr>";
            }
            server1.send(200, "text/html", RussianHead("Настройка UDP триггеров") + "<table>"+tmp+"</table><br /><a href='udptrigger?type=add'>Добавить</a>");
        }
        if(server1.arg("type") == "save"){
            int ids = server1.arg("id").toInt();
            byte en = server1.arg("en") == "on"; 
            String Types = server1.arg("TypeTrigger"); 
            ActionsType AT = (ActionsType)server1.arg("ActionType").toInt();
            String Data = server1.arg("Data");
            
            UDPTriggers tm = {Types, AT, Data, en};
            Ut.set(ids, tm);
            Save();
            server1.send(200, "text/html", (String)"<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/udptrigger?type=show' /></head>Триггер "+ids+" сохранен");
        }
        if(server1.arg("type") == "add"){  
            Ut.add({"EAlarm", SendGateway, "Test UDP", false});   
            Save();            
            server1.send(200, "text/html", (String)"<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/udptrigger?type=show' /></head>Новый триггер добавлен");
        }
        if(server1.arg("type") == "remove"){
            int ids = server1.arg("id").toInt();
            Ut.remove(ids);
            Save();
            server1.send(200, "text/html", (String)"<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/udptrigger?type=show' /></head>Триггер "+ids+" удален");
        }
    });
}

void MichomeUDP::Save(void){
    int countQ = Ut.size();
    String sb = ((String)countQ) + "|";
    for(int i = 0; i < countQ; i++){
        UDPTriggers em = Ut.get(i);
        sb += String(em.Type) + "~" + String(em.ActionType) + "~" + String(em.Data) + "~" + String(em.Enable ? "1" : "0") + "!";
    }                   
    fstext.WriteFile(sb);
}

void MichomeUDP::Load(void){
    String rd = fstext.ReadFile();
    int countQ = (*gtw).Split(rd, '|', 0).toInt();
    String data = (*gtw).Split(rd, '|', 1);
    for(int i = 0; i < countQ; i++){
        String str = (*gtw).Split(data, '!', i);
        UDPTriggers qq = {((*gtw).Split(str, '~', 0)), ((ActionsType)(*gtw).Split(str, '~', 1).toInt()), ((*gtw).Split(str, '~', 2)), ((*gtw).Split(str, '~', 3).toInt() == 1)};
        Ut.add(qq);
    }
}

void MichomeUDP::SendUDP(IPAddress ip, String data){
    UDP.beginPacket(ip, UDP.remotePort());
      char msg[data.length()+1];
      (data).toCharArray(msg, data.length()+1);
    UDP.write(msg);
    UDP.endPacket();
}

void MichomeUDP::SendUDP(IPAddress ip, int Port, String data){
    UDP.beginPacket(ip, Port);
      char msg[data.length()+1];
      (data).toCharArray(msg, data.length()+1);
    UDP.write(msg);
    UDP.endPacket();
}

void MichomeUDP::SendMulticast(String data){
    UDP.beginPacketMulticast(broadcast, MulticastUdpPort, WiFi.localIP());
       char msg[data.length()+1];
      (data).toCharArray(msg, data.length()+1);
    UDP.write(msg);
    UDP.endPacket();
}

String MichomeUDP::Split(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void MichomeUDP::running(){
    int packetLength = UDP.parsePacket();
    if(packetLength){
        if(UDP.remoteIP() != WiFi.localIP()){                   
            int len = UDP.read(incomingPacket, 255);
            if (len > 0){
                incomingPacket[len] = 0;           
            }
            String reads = String(incomingPacket);
            if(Split(reads, '-', 0) == "Search"){
                if(Split(reads, '-', 1) == type){
                    SendMulticast(GetData_SearchOK());
                }
                else if(Split(reads, '-', 1) == "all"){
                    SendMulticast(GetData_Discover());
                }
                else if(Split(reads, '-', 1) == "noconfigured" && !(*gtw).IsConfigured){
                    SendMulticast(GetData_SearchOK());
                }
            }
            if(Split(reads, '-', 0) == StudioLight && IsStr(type, StudioLight)){
                if(Split(reads, '-', 1) == "lightchange"){
                    (*lightModules).SetLightAll(Split(reads, '-', 2).toInt());
                    SendMulticast(GetData_OK());
                }
                else if(Split(reads, '-', 1) == "Countpins"){
                    SendMulticast((String)(*lightModules).CountPins());
                }
                else if(Split(reads, '-', 1) == id){
                    (*lightModules).TelnetRun(Split(reads, '-', 2));
                    SendMulticast(GetData_OK());
                }
                else if(Split(reads, '-', 1) == "telnetdata"){
                    (*lightModules).TelnetRun(Split(reads, '-', 2));
                    SendMulticast(GetData_OK());
                }
            }
            if(Split(reads, '-', 0) == id){
                if(Split(reads, '-', 1) == "Gettype"){
                    SendMulticast(GetData_MyType());
                }
                else if(Split(reads, '-', 1) == "rssi"){
                    SendMulticast((String)WiFi.RSSI());
                }
            }
            if(Split(reads, '-', 0) == "Events"){
                if(Split(reads, '-', 1) == "list"){
                    SendMulticast(GetData_EventsList());
                }
                else {
                    SendMulticast(GetData_Event_OK(Split(reads, '-', 1)));                    
                    if(Split(reads, '-', 1) == "EAlarm" && EAlarm){
                        if(IsStr(type, StudioLight)){
                            (*lightModules).StroboAll(5, 400);
                        }
                    }
                    else if(Split(reads, '-', 1) == "ENightLight" && ENightLight){
                        
                    }
                    else if(Split(reads, '-', 1) == "EOverCold" && EOverCold){

                    }
                    else if(Split(reads, '-', 1) == "EOverHot" && EOverHot){

                    }
                    for(int i = 0; i < Ut.size(); i++){
                        UDPTriggers tr = Ut.get(i);
                        if(tr.Enable && Split(reads, '-', 1) == tr.Type){
							String EVData = tr.Data;
							EVData.replace("%1", Split(reads, '-', 2));
                            if(tr.ActionType == (ActionsType)LightData && IsStr(type, StudioLight)){(*lightModules).TelnetRun(EVData);}
                            //else if(tr.ActionType == (ActionsType)SendURL){(*gtw).TelnetRun(tr.Data);}
                            else if(tr.ActionType == (ActionsType)SendGateway){(*gtw).SendData((*gtw).ParseJson("UDPData", EVData));}
                            else if(tr.ActionType == (ActionsType)SendsUDP){SendMulticast(EVData);}
                        }
                    }
                }
            }
            //SendMulticast(reads);
        }
    }
       
    if(Discover.IsTick()){  
        SendMulticast(GetData_Discover());
    }
}