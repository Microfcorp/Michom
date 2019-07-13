#include <ArduinoJson.h>
#include <Michom.h>

const char *ssid = "10-KORPUSMG";
const char *password = "10707707";

const char* id = "StudioLight_Main";
const char* type = "StudioLight";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

Michome michome(ssid, password, id, type, host, host1);

RTOS rtos(600000);

ESP8266WebServer& server1 = michome.GetServer();

Logger debug = michome.GetLogger();

#define MAX_SRV_CLIENTS 2
WiFiServer telnet(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];
bool IsData = false;
String teln = "";

const int Keys[] = {12,13,15};

String Parse(String txt){
  String tmp = "";
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(txt);
  int leg = root["Params"].size();
  int delays = 0;
  tmp += "Name = "+root["name"].as<String>()+"<br />";
  for(int i=0; i < leg; i++){
    tmp += root["Params"][i]["name"].as<String>() + "<br />";
    if(root["Params"][i]["name"].as<String>() == "playmusic"){
      //http://192.168.1.42:8080/jsonrpc?request={%22jsonrpc%22:%222.0%22,%22id%22:%221%22,%22method%22:%22Player.Open%22,%22params%22:{%22item%22:{%22file%22:%22'+file+'%22}}}
      michome.SendDataGET("/jsonrpc?request={\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Player.Open\",\"params\":{\"item\":{\"file\":\""+root["Params"][i]["file"].as<String>()+"\"}}}", "192.168.1.42", 8080);
      delays = 0;
    }
    else if(root["Params"][i]["name"].as<String>() == "setlight"){
         analogWrite(Keys[root["Params"][i]["pin"].as<int>()], root["Params"][i]["brightness"].as<int>());
         delays = 0;
         //logg.Log((String)i + " Setlight");
    }
    else if(root["Params"][i]["name"].as<String>() == "strobo"){
         int col = root["Params"][i]["col"];
         for(int iq = 0; iq < col; iq++){
            analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 1023);
            delay(root["Params"][i]["times"].as<int>());
            analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 0);
            delay(root["Params"][i]["times"].as<int>());
          }
          delays = col * (root["Params"][i]["times"].as<int>() * 2);
          //logg.Log((String)i + " strobo");
    }
    else if(root["Params"][i]["name"].as<String>() == "strobopro"){
         int col = root["Params"][i]["col"];
         for(int iq = 0; iq < col; iq++){
            analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 1023);
            delay(root["Params"][i]["times"].as<int>());
            analogWrite(Keys[root["Params"][i]["pin"].as<int>()], 0);
            delay(root["Params"][i]["nostrob"].as<int>());
          }
          delays = col * ((root["Params"][i]["times"].as<int>() + root["Params"][i]["nostrob"].as<int>()) * 2);
          //logg.Log((String)i + " strobo");
    }
    else if(root["Params"][i]["name"].as<String>() == "stroboall"){
         int col = root["Params"][i]["col"];
         for(int iq = 0; iq < col; iq++){
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
    else if(root["Params"][i]["name"].as<String>() == "stroboallpro"){
         int col = root["Params"][i]["col"];
         for(int iq = 0; iq < col; iq++){
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
    else if(root["Params"][i]["name"].as<String>() == "sleep"){
      //logg.Log((String)i + " sleep");
       delay((root["Params"][i]["times"].as<float>() * 1000) - delays);
    }
  }
  return tmp;
  //logg.Log(tmp);
}

void setup ( void ) {
  
  pinMode ( Keys[0], OUTPUT );
  pinMode ( Keys[1], OUTPUT );
  pinMode ( Keys[2], OUTPUT );
  digitalWrite ( Keys[0], LOW);
  digitalWrite ( Keys[1], LOW);
  digitalWrite ( Keys[2], LOW);

  server1.on("/jsonget", [](){    
    server1.send(200, "text/html", Parse(server1.arg(0)));    
  });

  server1.on("/setlight", [](){ 
    analogWrite(Keys[server1.arg(0).toInt()], server1.arg(1).toInt());
    server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()));    
  });

  server1.on("/strobo", [](){ 
    server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()));
    int col = server1.arg(1).toInt();
    for(int i = 0; i < col; i++){
        analogWrite(Keys[server1.arg(0).toInt()], 1023);
        delay(server1.arg(2).toInt());
        analogWrite(Keys[server1.arg(0).toInt()], 0);
        delay(server1.arg(2).toInt());
    }
  });

  server1.on("/strobopro", [](){ 
    server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()) + " as " + String(server1.arg(2).toInt()) + "/" + String(server1.arg(3).toInt()));
    int col = server1.arg(1).toInt();
    for(int i = 0; i < col; i++){
        analogWrite(Keys[server1.arg(0).toInt()], 1023);
        delay(server1.arg(2).toInt());
        analogWrite(Keys[server1.arg(0).toInt()], 0);
        delay(server1.arg(3).toInt());
    }
  });

  server1.on("/stroboall", [](){ 
    server1.send(200, "text/html", String("all") + " as " + String(server1.arg(0).toInt()));
    int col = server1.arg(0).toInt();
    for(int i = 0; i < col; i++){
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
  
  server1.on("/stroboallpro", [](){ 
    server1.send(200, "text/html", String("all") + " as " + String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()) + "/" + String(server1.arg(2).toInt()));
    int col = server1.arg(0).toInt();
    for(int i = 0; i < col; i++){
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
  
  michome.SetFormatSettings(2);
  michome.init(true);
  telnet.begin();
  telnet.setNoDelay(false);
}

void loop ( void ) {
  michome.running();  
  
  uint8_t i;
  //check if there are any new clients
  if (telnet.hasClient()){
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      //find free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected()){
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = telnet.available();
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = telnet.available();
    serverClient.stop();
  }
  for(i = 0; i < MAX_SRV_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()){
      if(serverClients[i].available()){
        //get data from the telnet client and push it to the UART       
        while(serverClients[i].available()){
          teln += char(serverClients[i].read());
        }
        IsData = true;     
      }
    }
  }
  

  if(IsData){

    String type = michome.Split(teln, ';', 0);

    debug.Log(teln);

    if(type == "setlight"){ //setlight;0;1023 pin;val
      analogWrite(Keys[michome.Split(teln, ';', 1).toInt()], michome.Split(teln, ';', 2).toInt());
    }
    else if(type == "strobo"){ //strobo;2;4;100 pin;col;sleep
      int col = michome.Split(teln, ';', 2).toInt();
      for(int i = 0; i < col; i++){
          analogWrite(Keys[michome.Split(teln, ';', 1).toInt()], 1023);
          delay(michome.Split(teln, ';', 3).toInt());
          analogWrite(Keys[michome.Split(teln, ';', 1).toInt()], 0);
          delay(michome.Split(teln, ';', 3).toInt());
      }
    }
    else if(type == "strobopro"){ //strobopro;10;0;100;50 col;pin;sleep;sleep2
      int col = michome.Split(teln, ';', 1).toInt();
      for(int i = 0; i < col; i++){
          analogWrite(Keys[michome.Split(teln, ';', 2).toInt()], 1023);
          delay(michome.Split(teln, ';', 3).toInt());
          analogWrite(Keys[michome.Split(teln, ';', 2).toInt()], 0);
          delay(michome.Split(teln, ';', 4).toInt());
      }
    }
    else if(type == "stroboall"){ //stroboall;10;100 col;sleep
      int col = michome.Split(teln, ';', 1).toInt();
      for(int i = 0; i < col; i++){
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
    else if(type == "stroboallpro"){ //stroboallpro;10;100;50 col;sleep;sleep2
      int col = michome.Split(teln, ';', 1).toInt();
      for(int i = 0; i < col; i++){
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
    
    IsData = false;
    teln = "";
    delay(100);
  }

  if(michome.GetSettingRead()){
    rtos.ChangeTime(michome.GetSetting("update").toInt());
    if(michome.GetSetting("logging") == "1")
      rtos.Start();
    else
      rtos.Stop();
  }

  if (rtos.IsTick()) {
    michome.SendData();
  }
}
