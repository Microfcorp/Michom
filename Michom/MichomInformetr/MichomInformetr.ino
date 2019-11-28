#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <Michom.h>

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

long pogr = 1800; //Отсчет до времени показа дня

bool EtherFail = false;
long Attempted = 0;

bool PokazType = true;

//Logger logg(host, host1);
Michome michome(id, type, host, host1);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

ESP8266WebServer& server1 = michome.GetServer();

byte Dozd[] = {
  0x04,
  0x0A,
  0x11,
  0x0E,
  0x00,
  0x02,
  0x08,
  0x02
};

byte groza[] = {
  0x04,
  0x0A,
  0x11,
  0x0E,
  0x04,
  0x06,
  0x02,
  0x02
};

byte oblazn[] = {
  0x04,
  0x0A,
  0x11,
  0x0E,
  0x00,
  0x00,
  0x00,
  0x00
};

byte soln[] = {
  0x00,
  0x00,
  0x04,
  0x0E,
  0x1F,
  0x0E,
  0x04,
  0x00
};

byte sneg[] = {
  0x04,
  0x0A,
  0x11,
  0x0E,
  0x00,
  0x04,
  0x0A,
  0x04
};

byte gradus[] = {
  0x18,
  0x18,
  0x03,
  0x04,
  0x04,
  0x04,
  0x03,
  0x00
};

byte watchh[] = {
  0x0E,
  0x15,
  0x15,
  0x15,
  0x17,
  0x11,
  0x11,
  0x0E
};

byte homes[] = {
  0x00,
  0x00,
  0x04,
  0x0E,
  0x1F,
  0x1F,
  0x1B,
  0x1B
};

String date[4][13] = {};

int IDtoIcon(int id) {
  if (id == 0) {
    return 2;
  }
  else if (id == 1) {
    return 0;
  }
  else if (id == 2) {
    return 0;
  }
  else if (id == 3) {
    return 4;
  }
  else if (id == 4) {
    return 3;
  }
  else if (id == 5) {
    return 1;
  }
  else {
    return 5;
  }
}

void ToHomes(){
  lcd.createChar(0, homes);
  lcd.createChar(1, watchh);
  lcd.createChar(2, groza);
  lcd.createChar(3, soln);
  lcd.createChar(4, sneg);
  lcd.createChar(5, gradus);
}

void ToPrognoz(){
  lcd.createChar(0, Dozd);
  lcd.createChar(1, oblazn);
  lcd.createChar(2, groza);
  lcd.createChar(3, soln);
  lcd.createChar(4, sneg);
  lcd.createChar(5, gradus);
}

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

  server1.on("/refresh", []() {
    server1.send(200, "text/html", "OK");
    michome.SendData();
  });

  server1.on("/offlight", []() {
    lcd.noBacklight();
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

    server1.send(200, "text/html", String("OK"));
  });

  michome.SetFormatSettings(3);
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
    rtos.ChangeTime(michome.GetSetting("update").toInt());
    rtos1.ChangeTime(michome.GetSetting("timeupdate").toInt());
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

  if (rtos.IsTick())
    michome.SendData();

  if (rtos2.IsTick())
    i2();

  if (rtos1.IsTick())
    i1();

  bool tickss = Button14.IsTick();
  /*if (tickss && )
    lcd.backlight();*/
  
  if (tickss && digitalRead(14) == LOW) {
    PokazType =! PokazType;
    if(PokazType)
      ToPrognoz();
    else
      ToHomes();
    i1();
  }
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

