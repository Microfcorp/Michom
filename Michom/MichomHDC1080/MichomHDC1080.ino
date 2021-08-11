#define DebugConnection 1
#include <Michom.h>
#include <ClosedCube_HDC1080.h>
#include <LightModules.h>
#include <TimerLightModule.h>

ClosedCube_HDC1080 hdc1080; 

//const char *ssid = "10-KORPUSMG";
//const char *password = "10707707";

const char* id = "hdc1080_garadze";
const char* type = "hdc1080";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

RTOS rtos(604000);

Michome michome(id, type, host, host1);

ESP8266WebServer& server1 = michome.GetServer();
LightModules lm (michome);
Telnet& telnet = lm.GetTelnet();
TimerLightModule tlm(&lm);

bool IsRunRele = false;
bool AutoRun = true;

void setup ( void ) {
  lm.AddPin(10);
  
  lm.TelnetEnable = true;
  lm.init();
  tlm.init();
  michome.SetFormatSettings(1);
  michome.init(false);
  michome.TimeoutConnection = 500;
  hdc1080.begin(0x40);
  
  server1.on("/refresh", [](){ 
    server1.send(200, "text/html", "OK");
    SendData();
  });

  server1.on("/meteo", [](){ 
    String tmp = "<html><head><title>Метеоданные</title><meta charset=\"UTF-8\"></head><body><table><tbody>";
    tmp += "<tr><td>Температура: "+String(hdc1080.readTemperature())+"<td></tr>";
    tmp += "<tr><td>Влажность: "+String(hdc1080.readHumidity())+"<td></tr>";
    tmp += "</tbody></table></body><html>";
    server1.send(200, "text/html", tmp);
    SendData();
  });

  /*server1.on("/setlight", []() {
    bool HasChange = false; //можно ли изменить
    
    if(server1.hasArg("m")) //если не руками
      if(server1.arg("m") == "cron" && AutoRun){ HasChange = true;} //Если крон и можно менять, то ставим флаг на смену
      else if(server1.arg("m") == "cron" && !AutoRun){ HasChange = false;} //Если крон и нельзя менять, то не ставим флаг на смену
      else{ HasChange = true;} //Если не руками и не кроном, то ставим флаг на смену
    else{ HasChange = true;} //Если руками, то ставим флаг на смену

    if(!server1.hasArg("m") && server1.arg(0).toInt() == 0) AutoRun = true; //Если руками и выключаем, то разрешаем менять
    if(!server1.hasArg("m") && server1.arg(0).toInt() == 1) AutoRun = false; //Если руками и включаем, то запрещаем менять

    if(HasChange){
      digitalWrite(10, server1.arg(0).toInt());
      server1.send(200, "text/html", String(server1.arg(0).toInt()));
      IsRunRele = (server1.arg(0).toInt() == 1 ? true : false);
    }         
  });*/   
  
  SendData();
}

void loop ( void ) {
  michome.running();
  tlm.running();

  if(michome.GetSettingRead()){
    rtos.ChangeTime(michome.GetSettingToInt("update"));
  }
  
  if (rtos.IsTick())
    SendData();
}

void SendData(){
  michome.SendData(michome.ParseJson(String(type), String(hdc1080.readTemperature())+";"+String(hdc1080.readHumidity())));
}


