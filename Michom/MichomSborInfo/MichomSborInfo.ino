#include <Adafruit_BMP085.h>
#include <Michom.h>
#include <DHT.h>

#define DHTPIN 14     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

/////////настройки//////////////
const char* ssid = "10-KORPUSMG";
const char* password = "10707707";

const char* id = "sborinfo_tv";
const char* type = "msinfoo";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

RTOS rtos(600000);

Michome michome(ssid, password, id, type, host, host1);

DHT dht(DHTPIN, DHTTYPE, 15);
Adafruit_BMP085 bmp;

ESP8266WebServer& server1 = michome.GetServer();

void setup() {
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP185 sensor, check wiring!");
  }
  dht.begin();  

  michome.SetFormatSettings(1);
  michome.init(false);  
  
  SendData();
}
void loop() {
  michome.running();

  if(michome.GetSettingRead()){
    rtos.ChangeTime(michome.GetSetting("update").toInt());
  }

  if (rtos.IsTick()) {
    SendData();
  }
}

void SendData(){
  michome.SendData(michome.ParseJson(String(type), String(bmp.readPressure()/133.3)+";"+String(bmp.readTemperature())+";"+String(bmp.readAltitude())+";"+String(dht.readTemperature())+";"+String(dht.readHumidity())));
}

