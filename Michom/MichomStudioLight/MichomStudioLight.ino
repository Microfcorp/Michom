#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


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

const int Keys[] = {12,13,15};

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

  server.on("/getid", [](){ 
    server.send(200, "text/html", (String)id);
  });

  server.on("/gettype", [](){ 
    server.send(200, "text/html", (String)type);
  });

  server.on("/getnameandid", [](){
    String tmpe = (String)id + "/n" + (String)type;
    server.send(200, "text/html", tmpe);
  });

  server.on("/setlight", [](){ 
    analogWrite(Keys[server.arg(0).toInt()], server.arg(1).toInt());
    server.send(200, "text/html", String(server.arg(0).toInt()) + " as " + String(server.arg(1).toInt()));
  });

  server.on("/strobo", [](){ 
    int col = server.arg(1).toInt();
    for(int i = 0; i < col; i++){
        analogWrite(Keys[server.arg(0).toInt()], 255);
        delay(server.arg(2).toInt());
        analogWrite(Keys[server.arg(0).toInt()], 0);
        delay(server.arg(2).toInt());
    }
    server.send(200, "text/html", String(server.arg(0).toInt()) + " as " + String(server.arg(1).toInt()));
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

