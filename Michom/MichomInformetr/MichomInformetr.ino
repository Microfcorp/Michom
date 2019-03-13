#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <Michom.h>

const char *ssid = "10-KORPUSMG";
const char *password = "10707707";

const char* id = "Informetr_Pogoda";
const char* type = "Informetr";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

long previousMillis = 0;   // здесь будет храниться время последнего изменения состояния светодиода 
long interval = 400000;

long previousMillis1 = 0;   // здесь будет храниться время последнего изменения состояния светодиода 
long interval1 = 10000;

//Logger logg(host, host1);
Michome michome(ssid, password, id, type, host, host1);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

ESP8266WebServer& server1 = michome.GetServer();

JsonObject& Parse(String txt){  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(txt); 
  
  return root;
  //logg.Log(tmp);
}

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

byte outhouse[] = {
  0x00,
  0x04,
  0x0A,
  0x11,
  0x11,
  0x0E,
  0x00,
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

String date[2][9] = {};

int IDtoIcon(int id){
  if(id == 0){
    return 2;
  }
  else if(id == 1){
    return 0;
  }
  else if(id == 2){
    return 0;
  }
  else if(id == 3){
    return 4;
  }
  else if(id == 4){
    return 3;
  }
  else if(id == 5){
    return 1;
  }
  else{
    return 5;
  }
}

void setup ( void ) {    

  lcd.begin();
  lcd.createChar(0, Dozd);
  lcd.createChar(1, oblazn);
  lcd.createChar(2, groza);
  lcd.createChar(3, soln);
  lcd.createChar(4, sneg);
  lcd.createChar(5, gradus);
  lcd.createChar(6, outhouse);
  lcd.createChar(7, watchh);
  lcd.backlight();
  lcd.print("Hello, world!");

  server1.on("/onlight", [](){ 
   lcd.backlight();
   server1.send(200, "text/html", String("OK"));    
  });
  
  server1.on("/offlight", [](){ 
   lcd.noBacklight();
   server1.send(200, "text/html", String("OK"));    
  });
  
  server1.on("/setdata", [](){ 
    //digitalWrite(Keys[server.arg(0).toInt()], server.arg(1).toInt());
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(server1.arg(0)); 

    if(root["d"].as<int>() == 1){
      lcd.backlight();
    }
    else{
      lcd.noBacklight();
    }

    date[0][0] = String(root["d"].as<int>());
    date[0][1] = String(IDtoIcon(root["4"].as<int>()));
    date[0][2] = String(IDtoIcon(root["4"].as<int>()));
    date[0][3] = String(root["0"].as<String>());
    date[0][4] = String(root["1"].as<String>());
    date[0][5] = String(root["2"].as<String>());
    date[0][6] = String(root["3"].as<String>());
    date[0][7] = String(root["temp"].as<String>());
    date[0][8] = String(root["time"].as<String>());
    date[0][9] = String(root["dawlen"].as<String>());
  
    lcd.clear();
    lcd.home();
    lcd.setCursor(0, 0);
    lcd.write(IDtoIcon(root["4"].as<int>()));
    lcd.setCursor(0, 1);
    lcd.write(IDtoIcon(root["4"].as<int>()));
    lcd.setCursor(2, 0);
    lcd.print(root["0"].as<String>());
    lcd.write(5);
    lcd.setCursor(2, 1);
    lcd.print(root["1"].as<String>());
    lcd.write(5);
    lcd.setCursor(9, 0);
    lcd.print(root["2"].as<String>() + "m/s");
    lcd.setCursor(9, 1);
    lcd.print(root["3"].as<String>() + "mm");
    server1.send(200, "text/html", String("OK"));    
  });

  michome.init();
}
bool st = true;
void loop ( void ) {

  michome.running();

  if (millis() - previousMillis > interval) {
    previousMillis = millis();   // запоминаем текущее время
    michome.SendData(michome.ParseJson(String(type), ""));
  }

  if (millis() - previousMillis1 > interval1) {
    previousMillis1 = millis();   // запоминаем текущее время
    if(date[0][0].toInt() == 1){
       lcd.backlight();
    }
    else{
       lcd.noBacklight();
    }
    lcd.clear();
    lcd.home();   
    if(st){                    
        lcd.setCursor(0, 0);
        lcd.write(date[0][1].toInt());
        lcd.setCursor(0, 1);
        lcd.write(date[0][2].toInt());
        lcd.setCursor(2, 0);
        lcd.print(date[0][3]);
        lcd.write(5);
        lcd.setCursor(2, 1);
        lcd.print(date[0][4]);
        lcd.write(5);
        lcd.setCursor(9, 0);
        lcd.print(date[0][5] + "m/s");
        lcd.setCursor(9, 1);
        lcd.print(date[0][6] + "mm");
        st = false;
    }
    else{
      lcd.setCursor(0, 0);
      lcd.write(6);
      lcd.setCursor(3, 0);
      lcd.print(date[0][7]);
      lcd.setCursor(0, 1);
      lcd.write(7);
      lcd.setCursor(2, 1);
      lcd.print(date[0][8]);
      lcd.setCursor(10, 0);
      lcd.print(date[0][9]);
      st = true;
    }
  }
}


