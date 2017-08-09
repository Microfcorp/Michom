#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "10-KORPUSMG";
const char* password = "10707707";

ESP8266WebServer server(80);

String svet = "выкл";
String zvonok = "0";

const int zvonokpin = 14;

void setup() {
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
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(zvonokpin, INPUT);
  attachInterrupt(14, zzin, RISING);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

   server.on("/", [](){
    server.send(200, "text/html", "Helloy World");
  });
  //setligh -> url
  //...light <- url
  server.on("/setligh", [](){  
    if(svet == "вкл"){server.send(200, "text/html", ret("Off light")); svet = "выкл";}
    else {server.send(200, "text/html", ret("On light")); svet = "вкл";}
  });
  //getligh -> url
  //Light... <- url
  server.on("/getligh", [](){
    server.send(200, "text/html", GetData("Light" + svet));
  });
  //calling -> url
  //OK <- url
  server.on("/calling", [](){
    server.send(200, "text/html", ret("calling"));
  });
  //refresh -> url
  //Light.sv. <- url
  server.on("/refresh", [](){
    server.send(200, "text/html", GetData(svet + "/n" + zvonok));
  });

  server.onNotFound([](){
    server.send(200, "text/html", GetData("Not found"));
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
}

void zzin(){
  zvonok = "call";
}



