#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <Michom.h>
#include "GyverButton.h"
#include <MichomUDP.h>

//const char *ssid = "10-KORPUSMG";
//const char *password = "10707707";

const char* id = "Informetr_Pogoda";
const char* type = "Informetr";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

RTOS rtos(600000);//Запрос данных
RTOS rtos1(10000);//Время переключения экранов
RTOS rtos2(8200);//Врея показа дня
RTOS Button14(500);//Опрос кнопки режимов

//13
//10
GButton button14(13);//Кнопка смены режимов

long pogr = 1800; //Отсчет до времени показа дня

bool EtherFail = false; //Ошибка интернета
long Attempted = 0; //попытка соеденения

bool PokazType = true; //тип экрана (прогноз (сменный)) или домашний (статичный)

bool pause = false; // пауза обновления

Michome michome(id, type, host, host1);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
ESP8266WebServer& server1 = michome.GetServer();
MichomeUDP MUDP(michome);

String date[4][13] = {};

void setup ( void ) {

  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);

  lcd.init();
  delay(10);
  lcd.noBacklight();
  lcd.print("Informetr");

  server1.on("/onlight", []() {
    lcd.backlight();
    server1.send(200, "text/html", String("OK"));
  });

  server1.on("/offlight", []() {
    lcd.noBacklight();
    server1.send(200, "text/html", String("OK"));
  });
  
  server1.on("/refresh", []() {
    server1.send(200, "text/html", "OK");
    michome.SendData();
  });

  server1.on("/print", []() {
    lcd.clear();
    lcd.home();
    lcd.setCursor(0, 0);
    lcd.print(server1.arg("fl"));
    lcd.setCursor(0, 1);
    lcd.print(server1.arg("sl"));
    server1.send(200, "text/html", String("OK"));
  });

  server1.on("/test", []() {
    lcd.noBacklight();
    lcd.backlight();
    ToPrognoz();
    
    lcd.clear();
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);

    server1.send(200, "text/html", "Pin mode: " + String(digitalRead(12)) + "<br />Pin button1: " + String(digitalRead(14)) + "<br />System OK");
  });

  server1.on("/setdata", []() {
    //digitalWrite(Keys[server.arg(0).toInt()], server.arg(1).toInt());

    String datareads = server1.arg(0);
    
    int firstClosingBracket = datareads.lastIndexOf("error");

    if(firstClosingBracket != -1){
      lcd.print("Error Update");
      return;
    }
    
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(datareads);

    if (root["d"].as<int>() == 3) {
      lcd.backlight();
      EtherFail = true;
      Attempted += 1;
    }
    else if (root["d"].as<int>() == 4) {
      lcd.noBacklight();
      EtherFail = true;
      Attempted += 1;
    }
    else if (root["d"].as<int>() == 1) {
      lcd.backlight();
      EtherFail = false;
      Attempted = 0;
    }
    else if (root["d"].as<int>() == 0) {
      lcd.noBacklight();
      EtherFail = false;
      Attempted = 0;
    }
    else {
      EtherFail = true;
      Attempted += 1;
    }

    if (!EtherFail) {
      for (int i = 0; i < 3; i++) {
        date[i][0] = String(root["d"].as<int>());
        date[i][1] = String(IDtoIcon(root["data"][i]["4"].as<int>()));
        date[i][2] = String(IDtoIcon(root["data"][i]["4"].as<int>()));
        date[i][3] = String(root["data"][i]["0"].as<String>());
        date[i][4] = String(root["data"][i]["1"].as<String>());
        date[i][5] = String(root["data"][i]["2"].as<String>());
        date[i][6] = String(root["data"][i]["3"].as<String>());
        date[i][7] = String(root["temp"].as<String>());
        date[i][8] = String(root["time"].as<String>());
        date[i][9] = String(root["dawlen"].as<String>());
        date[i][10] = String(root["data"][i]["times"].as<String>());
        date[i][11] = String(root["tempgr"].as<String>());
        date[i][12] = String(root["hummgr"].as<String>());
      }

      lcd.clear();
      lcd.home();
      lcd.setCursor(0, 0);
      lcd.print("Updating...");
    }
    pause = false;
    server1.send(200, "text/html", String("OK"));
  });

  michome.init(true);
}
bool st = true;
int day = 0;
void plusday() {
  day++;
  if (day > 2) {
    day = 0;
  }
}
void loop ( void ) {

  michome.running();

  if (michome.GetSettingRead()) {
    rtos.ChangeTime(michome.GetSettingToInt("update"));
    rtos1.ChangeTime(michome.GetSettingToInt("timeupdate"));
    rtos2.ChangeTime(rtos1.GetTime() - pogr);

    if (michome.GetSetting("running") == "0") {
      rtos.Stop();
      rtos1.Stop();
      rtos2.Stop();
    }
    else {
      rtos.Start();
      rtos1.Start();
      rtos2.Start();
    }
  }

  if(!pause){
    if (rtos.IsTick())
      michome.SendData();
  
    if (rtos2.IsTick())
      i2();
  
    if (rtos1.IsTick())
      i1();
  }


  button14.tick();

  if(button14.isSingle()){
    PokazType =! PokazType;
    if(PokazType)
      ToPrognoz();
    else
      ToHomes();
    i1();  
  }
  else if(button14.isDouble()){
    pause = !pause;
    if(pause){
      lcd.setCursor(0, 1);
      lcd.print("P");
      lcd.blink();
    }
    else{
      lcd.setCursor(0, 1);
      lcd.print("R");
      lcd.noBlink();
    }
  }
  else if(button14.isTriple()){
    pause = true;
    lcd.clear();
    lcd.home();
    lcd.setCursor(0, 0);
    lcd.print("Start Update");
    michome.SendData();
  }
  
  /*bool tickss = Button14.IsTick();
  
  if (tickss && digitalRead(14) == LOW) {
    PokazType =! PokazType;
    if(PokazType)
      ToPrognoz();
    else
      ToHomes();
    i1();
  }*/
}

void PrintETError() {
  lcd.noBlink();
  lcd.clear();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("Ethernet Error");
  lcd.setCursor(0, 1);
  lcd.print("Attempt " + String(Attempted));
  michome.SendData();
}

void i1() {
  lcd.noBlink();
  if (!EtherFail) {    
    if (date[0][0].toInt() == 1 || digitalRead(12) == LOW) {
      lcd.backlight();
    }
    else {
      lcd.noBacklight();
    }

    lcd.clear();
    lcd.home();
    
    if (PokazType) {
      ToPrognoz();
      lcd.setCursor(0, 0);
      lcd.noBlink();
      lcd.setCursor(0, 0);
      lcd.write(date[day][1].toInt());
      lcd.setCursor(0, 1);
      lcd.write(date[day][2].toInt());
      lcd.setCursor(2, 0);
      lcd.print(date[day][3]);
      lcd.write(5);
      lcd.setCursor(2, 1);
      lcd.print(date[day][4]);
      lcd.write(5);
      lcd.setCursor(9, 0);
      lcd.print(date[day][5] + "m/s");
      lcd.setCursor(9, 1);
      lcd.print(date[day][6] + "mm");
      plusday();
    }
    else {
      ToHomes();
      lcd.setCursor(0, 0);
      lcd.write(0);
      lcd.setCursor(2, 0);
      lcd.print(date[0][7]);
      lcd.write(5);
      lcd.setCursor(9, 0);
      lcd.print(date[1][9]);
      
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.setCursor(2, 1);
      lcd.print(date[0][11]);
      lcd.write(5);
      lcd.setCursor(9, 1);
      lcd.print(date[0][12] + "%");
    }
  }
  else {
    PrintETError();
  }
}

void i2() {
  if (!EtherFail) {
    if (PokazType) {
      lcd.clear();
      lcd.home();
      lcd.setCursor(0, 0);
      lcd.print(date[day][10]);
      lcd.blink();
    }
  }
  else {
    PrintETError();
  }
}

