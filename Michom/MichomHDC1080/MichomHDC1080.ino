#include <Michom.h>
#include <ClosedCube_HDC1080.h>

ClosedCube_HDC1080 hdc1080; 

const char *ssid = "10-KORPUSMG";
const char *password = "10707707";

const char* id = "hdc1080_remyank";
const char* type = "hdc1080";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

long previousMillis = 0;   // здесь будет храниться время последнего изменения состояния светодиода 
long interval = 600000;

Michome michome(ssid, password, id, type, host, host1);

ESP8266WebServer& server1 = michome.GetServer();

void setup ( void ) {
  michome.init();
  hdc1080.begin(0x40);
  michome.SendData(michome.ParseJson(String(type), String(hdc1080.readTemperature())+";"+String(hdc1080.readHumidity())));
}

void loop ( void ) {
  michome.running();
  
  if (millis() - previousMillis > interval) {
    previousMillis = millis();   // запоминаем текущее время
    michome.SendData(michome.ParseJson(String(type), String(hdc1080.readTemperature())+";"+String(hdc1080.readHumidity())));
  }
}


