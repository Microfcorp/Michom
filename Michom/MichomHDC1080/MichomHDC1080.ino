#define DebugConnection 1
#include <Michom.h>
#include <ClosedCube_HDC1080.h>

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

void setup ( void ) {
  michome.SetFormatSettings(1);
  michome.init(false);
  hdc1080.begin(0x40);
  
  server1.on("/refresh", [](){ 
    server1.send(200, "text/html", "OK");
    SendData();
  });  
  SendData();
}

void loop ( void ) {
  michome.running();

  if(michome.GetSettingRead()){
    rtos.ChangeTime(michome.GetSettingToInt("update"));
  }
  
  if (rtos.IsTick())
    SendData();
}

void SendData(){
  michome.SendData(michome.ParseJson(String(type), String(hdc1080.readTemperature())+";"+String(hdc1080.readHumidity())));
}


