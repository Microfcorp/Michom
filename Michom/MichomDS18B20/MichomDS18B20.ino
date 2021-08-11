#include <Michom.h>
#include <OneWire.h>

//const char *ssid = "10-KORPUSMG";
//const char *password = "10707707";

const char* id = "termometr_okno";
const char* type = "termometr";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

RTOS rtos(600000);

Michome michome(id, type, host, host1);

ESP8266WebServer& server1 = michome.GetServer();
OneWire ds(10);

float getTemp(){
  byte i;
    byte data[12];
    byte addr[8];
    float celsius;
      
    ds.reset();
    //ds.select(addr);
    ds.write(0xCC);
    ds.write(0x44, 1); // команда на измерение температуры

    delay(1000);

    ds.reset();
    //ds.select(addr); 
    ds.write(0xCC);
    ds.write(0xBE); // команда на начало чтения измеренной температуры

    // считываем показания температуры из внутренней памяти датчика
    for ( i = 0; i < 9; i++) {
        data[i] = ds.read();
    }

    int16_t raw = (data[1] << 8) | data[0];
    // датчик может быть настроен на разную точность, выясняем её 
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7; // точность 9-разрядов, 93,75 мс
    else if (cfg == 0x20) raw = raw & ~3; // точность 10-разрядов, 187,5 мс
    else if (cfg == 0x40) raw = raw & ~1; // точность 11-разрядов, 375 мс

    // преобразование показаний датчика в градусы Цельсия 
    celsius = (float)raw / 16.0;
    Serial.print("t=");
    Serial.println(celsius);
   return celsius;
} 


const int led = 13;

void setup ( void ) {
  server1.on("/refresh", [](){ 
    server1.send(200, "text/html", "OK");
    SendData();
 });  
 
   server1.on("/gettemp", [](){ 
    server1.send(200, "text/html", String(getTemp())+"C");
    SendData();
 });    
 
  michome.init(false);
  SendData();
}

void loop ( void ) {
  michome.running();

  if(michome.GetSettingRead()){
    rtos.ChangeTime(michome.GetSetting("update").toInt());
  }
  
  if (rtos.IsTick()) {
    SendData();
  }
}

void SendData(){
  michome.SendData(michome.ParseJson(String(type), String(getTemp())));
}

