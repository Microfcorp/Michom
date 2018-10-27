#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <Logger.h>
#include <Michom.h>

const char *ssid = "10-KORPUSMG";
const char *password = "10707707";

const char* id = "LightStudio_Main";
const char* type = "LightStudio";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

long previousMillis = 0;   // здесь будет храниться время последнего изменения состояния светодиода 
long interval = 600000;

MDNSResponder mdns;

ESP8266WebServer server ( 80 );

Logger logg(host, host1);
Michome m;

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
      m.SendDataGET("/jsonrpc?request={\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Player.Open\",\"params\":{\"item\":{\"file\":\""+root["Params"][i]["file"].as<String>()+"\"}}}", "192.168.1.42", 8080);
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
    else if(root["Params"][i]["name"].as<String>() == "sleep"){
      //logg.Log((String)i + " sleep");
       delay((root["Params"][i]["times"].as<float>() * 1000) - delays);
    }
  }
  return tmp;
  //logg.Log(tmp);
}

void setup ( void ) {

ArduinoOTA.setHostname(id);
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  
  pinMode ( Keys[0], OUTPUT );
  pinMode ( Keys[1], OUTPUT );
  pinMode ( Keys[2], OUTPUT );
  digitalWrite ( Keys[0], LOW);
  digitalWrite ( Keys[1], LOW);
  digitalWrite ( Keys[2], LOW);
  
  Serial.begin ( 115200 );
  WiFi.begin ( ssid, password );
  Serial.println ( "" );
  
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( mdns.begin ( "esp8266", WiFi.localIP() ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on("/", [](){
    logg.Log("On main");
    server.send(404, "text/html", "Not found");    
  });
  //refresh -> url
  //Light.sv. <- url
  server.on("/refresh", [](){ 
    server.send(200, "text/html", "OK");
    conn();
  });

  server.on("/restart", [](){ 
    server.send(200, "text/html", "OK");
    ESP.reset();
  });
//Warning
  server.on("/getid", [](){ 
    server.send(200, "text/html", (String)id);
  });

  server.on("/gettype", [](){ 
    server.send(200, "text/html", (String)type);
  });
// /Warning
  server.on("/getnameandid", [](){
    String tmpe = (String)id + "/n" + (String)type;
    server.send(200, "text/html", tmpe);
  });

  server.on("/jsonget", [](){    
    server.send(200, "text/html", Parse(server.arg(0)));    
  });

  server.on("/setlight", [](){ 
    analogWrite(Keys[server.arg(0).toInt()], server.arg(1).toInt());
    server.send(200, "text/html", String(server.arg(0).toInt()) + " as " + String(server.arg(1).toInt()));    
  });

  server.on("/strobo", [](){ 
    server.send(200, "text/html", String(server.arg(0).toInt()) + " as " + String(server.arg(1).toInt()));
    int col = server.arg(1).toInt();
    for(int i = 0; i < col; i++){
        analogWrite(Keys[server.arg(0).toInt()], 1023);
        delay(server.arg(2).toInt());
        analogWrite(Keys[server.arg(0).toInt()], 0);
        delay(server.arg(2).toInt());
    }
  });

  server.on("/stroboall", [](){ 
    server.send(200, "text/html", String("all") + " as " + String(server.arg(0).toInt()));
    int col = server.arg(0).toInt();
    for(int i = 0; i < col; i++){
        analogWrite(Keys[0], 1023);
        analogWrite(Keys[1], 1023);
        analogWrite(Keys[2], 1023);
        delay(server.arg(1).toInt());
        analogWrite(Keys[0], 0);
        analogWrite(Keys[1], 0);
        analogWrite(Keys[2], 0);
        delay(server.arg(1).toInt());
    }
  });

  server.onNotFound([](){
    server.send(200, "text/html", "Not found");
  });
  
  server.begin();
  Serial.println ( "HTTP server started" );
 conn();
}

void loop ( void ) {
  mdns.update();
  server.handleClient();
  ArduinoOTA.handle();

  if (millis() - previousMillis > interval) {
    previousMillis = millis();   // запоминаем текущее время
    // если светодиод был выключен – включаем и наоборот :)
    conn();
  }
}

void conn(){
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host1, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  String dataaaa = parsejson("StudioLight", "");

  Serial.print("Data: ");
  Serial.println(dataaaa);

  String lengt = (String)dataaaa.length(); 
  
  // This will send the request to the server
  client.print(String("POST ") + "http://192.168.1.42/michome/getpost.php" + " HTTP/1.1\r\n" +
               "Host: " + "192.168.1.42" + "\r\n" + 
               "Content-Length: " + lengt + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded \r\n" +
               "Connection: close\r\n\r\n" +
               "6=" + dataaaa);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  delay(1000);
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  //client = null;
  lengt = "";
}

String parsejson(String type, String data){
  String temp = "";
  temp += "{";
  temp += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
  temp += "\"rssi\":\"" + String(WiFi.RSSI()) + "\",";
  temp += "\"type\":";
  temp += "\"" + type + "\",";
  if(type == "StudioLight"){    
  temp += "\"data\":{";
  temp += "\"status\": \"" + String("OK") + "\"} } \r\n";
  }
  temp += "     ";
  return temp; 
}

