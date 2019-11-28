#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Michom.h>
#define NoSerial

#define Run() irsend.sendNEC(0x42BD50AF, 32); delay(100)
#define Input() irsend.sendNEC(0x42BD08F7, 32); delay(100)
#define Mode() irsend.sendNEC(0x42BD48B7, 32); delay(100)
#define VolumeUp() irsend.sendNEC(0x42BDE01F, 32); delay(100)
#define VolumeDown() irsend.sendNEC(0x42BD6897, 32); delay(100)
#define Default() irsend.sendNEC(0x42BD00FF, 32); delay(100)
#define BasUp() irsend.sendNEC(0x42BD906F, 32); delay(100)
#define BasDown() irsend.sendNEC(0x42BDD02F, 32); delay(100)
#define TreblUp() irsend.sendNEC(0x42BD8877, 32); delay(100)
#define TreblDown() irsend.sendNEC(0x42BDC837, 32); delay(100)
#define SurrUp() irsend.sendNEC(0x42BD40BF, 32); delay(100)
#define SurrDown() irsend.sendNEC(0x42BD20DF, 32); delay(100)
#define CenterUp() irsend.sendNEC(0x42BDC03F, 32); delay(100)
#define CenterDown() irsend.sendNEC(0x42BDA05F, 32); delay(100)
#define SWUp() irsend.sendNEC(0x42BDB04F, 32); delay(100)
#define SWDown() irsend.sendNEC(0x42BD10EF, 32); delay(100)

//const char *ssid = "10-KORPUSMG";
//const char *password = "10707707";

const char* id = "StudioLight_Main";
const char* type = "StudioLight";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

Michome michome(id, type, host, host1);

RTOS rtos(605000);
RTOS rtos1(100);
//RTOS rtos2(100);

ESP8266WebServer& server1 = michome.GetServer();

Logger debug = michome.GetLogger();

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

int RStructures[] =
{ 0, 961,
  1, 11,
  2, 746
};

RKeyboard keyboard(A0, RStructures, 6);

#define MAX_SRV_CLIENTS 1
WiFiServer telnet(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];
bool IsData = false;
String teln = "";

bool Current = false;
bool YesCurrent = true;

const int Keys[] = {12, 13, 15};

String Parse(String txt) {
  String tmp = "";
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(txt);
  int leg = root["Params"].size();
  int delays = 0;
  tmp += "Name = " + root["name"].as<String>() + "<br />";
  for (int i = 0; i < leg; i++) {
    //tmp += root["Params"][i]["name"].as<String>() + "<br />";
    if (root["Params"][i]["name"].as<String>() == "playmusic") {
      //http://192.168.1.42:8080/jsonrpc?request={%22jsonrpc%22:%222.0%22,%22id%22:%221%22,%22method%22:%22Player.Open%22,%22params%22:{%22item%22:{%22file%22:%22'+file+'%22}}}
      michome.SendDataGET("/jsonrpc?request={\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Player.Open\",\"params\":{\"item\":{\"file\":\"" + root["Params"][i]["file"].as<String>() + "\"}}}", "192.168.1.42", 8080);
      delays = 0;
    }
    else if (root["Params"][i]["name"].as<String>() == "setlight") {
      analogWrite(Keys[root["Params"][i]["pin"].as<int>()], root["Params"][i]["brightness"].as<int>());
      delays = 0;
      //logg.Log((String)i + " Setlight");
    }
    else if (root["Params"][i]["name"].as<String>() == "setlightall") {
      analogWrite(Keys[0], root["Params"][i]["brightness"].as<int>());
      analogWrite(Keys[1], root["Params"][i]["brightness"].as<int>());
      analogWrite(Keys[2], root["Params"][i]["brightness"].as<int>());
      delays = 0;
      //logg.Log((String)i + " Setlight");
    }
    else if (root["Params"][i]["name"].as<String>() == "strobo") {
      int col = root["Params"][i]["col"];
      for (int iq = 0; iq < col; iq++) {
        analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 1023);
        delay(root["Params"][i]["times"].as<int>());
        analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 0);
        delay(root["Params"][i]["times"].as<int>());
      }
      delays = col * (root["Params"][i]["times"].as<int>() * 2);
      //logg.Log((String)i + " strobo");
    }
    else if (root["Params"][i]["name"].as<String>() == "strobopro") {
      int col = root["Params"][i]["col"];
      for (int iq = 0; iq < col; iq++) {
        analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 1023);
        delay(root["Params"][i]["times"].as<int>());
        analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 0);
        delay(root["Params"][i]["nostrob"].as<int>());
      }
      delays = col * ((root["Params"][i]["times"].as<int>() + root["Params"][i]["nostrob"].as<int>()) * 2);
      //logg.Log((String)i + " strobo");
    }
    else if (root["Params"][i]["name"].as<String>() == "stroboall") {
      int col = root["Params"][i]["col"];
      for (int iq = 0; iq < col; iq++) {
        analogWrite(Keys[0], 1023);
        analogWrite(Keys[1], 1023);
        analogWrite(Keys[2], 1023);
        delay(root["Params"][i]["times"].as<int>());
        analogWrite(Keys[0], 0);
        analogWrite(Keys[1], 0);
        analogWrite(Keys[2], 0);
        delay(root["Params"][i]["times"].as<int>());
      }
      delays = col * (root["Params"][i]["times"].as<int>() * 2);
      //logg.Log((String)i + " stroboall");
    }
    else if (root["Params"][i]["name"].as<String>() == "stroboallpro") {
      int col = root["Params"][i]["col"];
      for (int iq = 0; iq < col; iq++) {
        analogWrite(Keys[0], 1023);
        analogWrite(Keys[1], 1023);
        analogWrite(Keys[2], 1023);
        delay(root["Params"][i]["times"].as<int>());
        analogWrite(Keys[0], 0);
        analogWrite(Keys[1], 0);
        analogWrite(Keys[2], 0);
        delay(root["Params"][i]["nostrob"].as<int>());
      }
      delays = col * ((root["Params"][i]["times"].as<int>() + root["Params"][i]["nostrob"].as<int>()) * 2);
      //logg.Log((String)i + " stroboall");
    }
    else if (root["Params"][i]["name"].as<String>() == "sleep") {
      //logg.Log((String)i + " sleep");
      delay((root["Params"][i]["times"].as<float>() * 1000) - delays);
    }
  }
  return tmp;
  //logg.Log(tmp);
}

void handleIr() {
  for (uint8_t i = 0; i < server1.args(); i++) {
    if (server1.argName(i) == "code") {
      uint32_t code = strtoul(server1.arg(i).c_str(), NULL, 10);
      irsend.sendNEC(code, 32);
      delay(100);
      server1.send(200, "text/html", String(code));
    }
  }
}

void setup ( void ) {

  pinMode ( Keys[0], OUTPUT );
  pinMode ( Keys[1], OUTPUT );
  pinMode ( Keys[2], OUTPUT );
  pinMode (A0, INPUT);
  pinMode (5, 2);
  digitalWrite ( Keys[0], LOW);
  digitalWrite ( Keys[1], LOW);
  digitalWrite ( Keys[2], LOW);

  server1.on("/jsonget", []() {
    server1.send(200, "text/html", Parse(server1.arg(0)));
  });

  server1.on("/setlight", []() {
    analogWrite(Keys[server1.arg(0).toInt()], server1.arg(1).toInt());
    server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()));
  });

  server1.on("/setlightall", []() {
    analogWrite(Keys[0], server1.arg(0).toInt());
    analogWrite(Keys[1], server1.arg(0).toInt());
    analogWrite(Keys[2], server1.arg(0).toInt());
    server1.send(200, "text/html", "all as " + String(server1.arg(0).toInt()));
  });

  server1.on("/strobo", []() {
    server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()));
    int col = server1.arg(1).toInt();
    for (int i = 0; i < col; i++) {
      analogWrite(Keys[server1.arg(0).toInt()], 1023);
      delay(server1.arg(2).toInt());
      analogWrite(Keys[server1.arg(0).toInt()], 0);
      delay(server1.arg(2).toInt());
    }
  });

  server1.on("/strobopro", []() {
    server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()) + " as " + String(server1.arg(2).toInt()) + "/" + String(server1.arg(3).toInt()));
    int col = server1.arg(1).toInt();
    for (int i = 0; i < col; i++) {
      analogWrite(Keys[server1.arg(0).toInt()], 1023);
      delay(server1.arg(2).toInt());
      analogWrite(Keys[server1.arg(0).toInt()], 0);
      delay(server1.arg(3).toInt());
    }
  });

  server1.on("/stroboall", []() {
    server1.send(200, "text/html", String("all") + " as " + String(server1.arg(0).toInt()));
    int col = server1.arg(0).toInt();
    for (int i = 0; i < col; i++) {
      analogWrite(Keys[0], 1023);
      analogWrite(Keys[1], 1023);
      analogWrite(Keys[2], 1023);
      delay(server1.arg(1).toInt());
      analogWrite(Keys[0], 0);
      analogWrite(Keys[1], 0);
      analogWrite(Keys[2], 0);
      delay(server1.arg(1).toInt());
    }
  });

  server1.on("/stroboallpro", []() {
    server1.send(200, "text/html", String("all") + " as " + String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()) + "/" + String(server1.arg(2).toInt()));
    int col = server1.arg(0).toInt();
    for (int i = 0; i < col; i++) {
      analogWrite(Keys[0], 1023);
      analogWrite(Keys[1], 1023);
      analogWrite(Keys[2], 1023);
      delay(server1.arg(1).toInt());
      analogWrite(Keys[0], 0);
      analogWrite(Keys[1], 0);
      analogWrite(Keys[2], 0);
      delay(server1.arg(2).toInt());
    }
  });

  server1.on("/ir", handleIr);

  server1.on("/refresh", []() {
    server1.send(200, "text/html", "OK");
    michome.SendData();
  });

  michome.SetFormatSettings(3);
  michome.init(true);
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  telnet.begin();
  telnet.setNoDelay(true);
}

void loop ( void ) {
  michome.running();
  uint8_t i;
  //check if there are any new clients
  if (telnet.hasClient()) {
    //find free/disconnected spot
    if (!serverClients[0] || !serverClients[0].connected()) {
      if (serverClients[0]) serverClients[0].stop();
      serverClients[0] = telnet.available();
      serverClients[0].setTimeout(100);
      //continue;
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = telnet.available();
    serverClient.stop();
  }
  if (serverClients[0] && serverClients[0].connected()) {
    if (serverClients[0].available()) {
      //get data from the telnet client and push it to the UART
      while (serverClients[0].available()) {
        String teln = serverClients[0].readStringUntil('\t');

        String type = michome.Split(teln, ';', 0);
        if (type == "setlight") { //setlight;0;1023 pin;val
          analogWrite(Keys[michome.Split(teln, ';', 1).toInt()], michome.Split(teln, ';', 2).toInt());
        }
        else if (type == "setlightall") { //setlightall;1023 val
          analogWrite(Keys[0], michome.Split(teln, ';', 1).toInt());
          analogWrite(Keys[1], michome.Split(teln, ';', 1).toInt());
          analogWrite(Keys[2], michome.Split(teln, ';', 1).toInt());
        }
        else if (type == "strobo") { //strobo;2;4;100 pin;col;sleep
          int col = michome.Split(teln, ';', 2).toInt();
          for (int i = 0; i < col; i++) {
            analogWrite(Keys[michome.Split(teln, ';', 1).toInt()], 1023);
            delay(michome.Split(teln, ';', 3).toInt());
            analogWrite(Keys[michome.Split(teln, ';', 1).toInt()], 0);
            delay(michome.Split(teln, ';', 3).toInt());
          }
        }
        else if (type == "strobopro") { //strobopro;10;0;100;50 col;pin;sleep;sleep2
          int col = michome.Split(teln, ';', 1).toInt();
          for (int i = 0; i < col; i++) {
            analogWrite(Keys[michome.Split(teln, ';', 2).toInt()], 1023);
            delay(michome.Split(teln, ';', 3).toInt());
            analogWrite(Keys[michome.Split(teln, ';', 2).toInt()], 0);
            delay(michome.Split(teln, ';', 4).toInt());
          }
        }
        else if (type == "stroboall") { //stroboall;10;100 col;sleep
          int col = michome.Split(teln, ';', 1).toInt();
          for (int i = 0; i < col; i++) {
            analogWrite(Keys[0], 1023);
            analogWrite(Keys[1], 1023);
            analogWrite(Keys[2], 1023);
            delay(michome.Split(teln, ';', 2).toInt());
            analogWrite(Keys[0], 0);
            analogWrite(Keys[1], 0);
            analogWrite(Keys[2], 0);
            delay(michome.Split(teln, ';', 2).toInt());
          }
        }
        else if (type == "stroboallpro") { //stroboallpro;10;100;50 col;sleep;sleep2
          int col = michome.Split(teln, ';', 1).toInt();
          for (int i = 0; i < col; i++) {
            analogWrite(Keys[0], 1023);
            analogWrite(Keys[1], 1023);
            analogWrite(Keys[2], 1023);
            delay(michome.Split(teln, ';', 2).toInt());
            analogWrite(Keys[0], 0);
            analogWrite(Keys[1], 0);
            analogWrite(Keys[2], 0);
            delay(michome.Split(teln, ';', 3).toInt());
          }
        }
      }
    }
  }

  if (michome.GetSettingRead()) {
    rtos.ChangeTime(michome.GetSettingToInt("update"));
    rtos1.ChangeTime(michome.GetSettingToInt("adcread"));
    if (michome.GetSetting("logging") == "1")
      rtos.Start();
    else
      rtos.Stop();
  }

  if (rtos.IsTick()) {
    michome.SendData();
  }

  if (rtos1.IsTick()) {
    int KeyPress = keyboard.PresedKey();
    if (KeyPress == 0) {
      VolumeUp();
    }
    else if (KeyPress == 1) {
      VolumeDown();
    }
    else if (KeyPress == 2) {
      Run();
    }
  }

  Current = digitalRead(5);
  if (Current != YesCurrent) {
    YesCurrent = Current;
    if (Current) {
      analogWrite(Keys[0], 0);
      analogWrite(Keys[1], 0);
      analogWrite(Keys[2], 0);
    }
    else {
      analogWrite(Keys[0], 1023);
      analogWrite(Keys[1], 1023);
      analogWrite(Keys[2], 1023);
    }
    michome.SendData(michome.ParseJson("get_button_press", String(Current)));
  }
}
