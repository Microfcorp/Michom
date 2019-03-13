#include "Michom.h"

ESP8266WebServer server(80);

//
// конструктор - вызывается всегда при создании экземпляра класса Michome
//
Michome::Michome(const char* _ssid, const char* _password, const char* _id, const char* _type, const char* _host, const char* _host1)
{
    ssid = _ssid;
    password = _password;
    id = _id;
    type = _type;
    host1 = _host1;
    host = _host;
    mdns = MDNSResponder();
    //this.server = server;
}

ESP8266WebServer& Michome::GetServer(){
    return server;
}

//
// Инициализация в Setup
//
void Michome::init(void)
{
      //ESP8266WebServer server = server;
      Serial.begin ( 115200 );
      WiFi.begin ( ssid, password );
      Serial.println ( "" );
      
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
      
      server.on("/", [this](){
        //logg.Log("On main");
        server.send(404, "text/html", "Not found");    
      });
      //refresh -> url
      server.on("/refresh", [this](){ 
        server.send(200, "text/html", "OK");
        SendData(ParseJson(String(type), ""));
      });

      server.on("/restart", [this](){ 
        server.send(200, "text/html", "OK");
        ESP.reset();
      });
      
    //Warning
      server.on("/getid", [this](){ 
        server.send(200, "text/html", (String)id);
      });

      server.on("/gettype", [this](){ 
        server.send(200, "text/html", (String)type);
      });
    // /Warning

      server.on("/getnameandid", [this](){
        String tmpe = (String)Michome::id + "/n" + (String)Michome::type;
        server.send(200, "text/html", tmpe);
      });
      
      server.onNotFound([this](){
        server.send(404, "text/html", "Not found");
      });
      
      server.begin();
      Serial.println ( "HTTP server started" );
      Serial.println(SendData(ParseJson(String(type), "")));
}

//
// Цикл в Loop
//
void Michome::running(void)
{
  mdns.update();
  server.handleClient();
  ArduinoOTA.handle();
}

//
// 
//
String Michome::SendDataGET(String gateway, const char* host, int Port)
{
          Serial.print("connecting to ");
		  Serial.println(host);
  
		  // Use WiFiClient class to create TCP connections
		  WiFiClient client;
		  const int httpPort = Port;
		  if (!client.connect(host, httpPort)) {
			Serial.println("connection failed");
			return "connection failed";
		  }		

		  
		  // This will send the request to the server
		  client.print(String("GET ") + (String)gateway + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
		  unsigned long timeout = millis();
		  while (client.available() == 0) {
			if (millis() - timeout > 5000) {
			  Serial.println(">>> Client Timeout !");
			  client.stop();
			  return ">>> Client Timeout !";
			}
		  }
		  delay(1000);
		  String r = "";
		  // Read all the lines of the reply from server and print them to Serial
		  while(client.available()){
			String line = client.readStringUntil('\r');
			r += line + "<br />";
		  }
		  
		  return r;
}
String Michome::SendDataPOST(const char* gateway, const char* host, int Port, String Data)
{
          Serial.print("connecting to ");
		  Serial.println(host);
  
		  // Use WiFiClient class to create TCP connections
		  WiFiClient client;
		  const int httpPort = Port;
		  if (!client.connect(host, httpPort)) {
			Serial.println("connection failed");
			return "connection failed";
		  }
		  
		  String dataaaa = Data;

		  Serial.print("Data: ");
		  Serial.println(dataaaa);

		  String lengt = (String)dataaaa.length(); 
		  
		  // This will send the request to the server
		  client.print(String("POST ") + "http://" + (String)gateway + " HTTP/1.1\r\n" +
					   "Host: " + (String)host + "\r\n" + 
					   "Content-Length: " + lengt + "\r\n" +
					   "Content-Type: application/x-www-form-urlencoded \r\n" +
					   "Connection: close\r\n\r\n" +
					   dataaaa);
		  unsigned long timeout = millis();
		  while (client.available() == 0) {
			if (millis() - timeout > 5000) {
			  Serial.println(">>> Client Timeout !");
			  client.stop();
			  return ">>> Client Timeout !";
			}
		  }
		  delay(1000);
		  String r = "";
		  // Read all the lines of the reply from server and print them to Serial
		  while(client.available()){
			String line = client.readStringUntil('\r');
			r += line + "<br />";
		  }
		  
		  return r;
}
String Michome::SendData(String Data)
{
          Serial.print("connecting to ");
          Serial.println(host);
          
          // Use WiFiClient class to create TCP connections
          WiFiClient client;
          const int httpPort = 80;
          if (!client.connect(host1, httpPort)) {
            Serial.println("connection failed");
            return "Error";
          }
          
          String dataaaa = Data;

          Serial.print("Data: ");
          Serial.println(dataaaa);

          String lengt = (String)dataaaa.length(); 
          
          // This will send the request to the server
          client.print(String("POST ") + "http://" + host + " HTTP/1.1\r\n" +
                       "Host: " + host1 + "\r\n" + 
                       "Content-Length: " + lengt + "\r\n" +
                       "Content-Type: application/x-www-form-urlencoded \r\n" +
                       "Connection: close\r\n\r\n" +
                       "6=" + dataaaa);
          unsigned long timeout = millis();
          while (client.available() == 0) {
            if (millis() - timeout > 5000) {
              Serial.println(">>> Client Timeout !");
              client.stop();
              return "Error";
            }
          }
          delay(1000);
          // Read all the lines of the reply from server and print them to Serial
          String line = "";
          while(client.available()){
            line = client.readStringUntil('\r');
          }
          
          Serial.println();
          Serial.println("closing connection");
          //client = null;
          lengt = "";
          return line;
}
String Michome::ParseJson(String type, String data){
      String temp = "";
      temp += "{";
      temp += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
      temp += "\"rssi\":\"" + String(WiFi.RSSI()) + "\",";
      temp += "\"type\":";
      temp += "\"" + type + "\",";
      if(type == "StudioLight"){    
          temp += "\"data\":{";
          temp += "\"status\": \"" + String("OK") + "\"}";
      }
      else if(type == "Informetr"){    
          temp += "\"data\":{";
          temp += "\"data\": \"" + String("GetData") + "\"}";
      }
      else{
          temp += "\"data\":\"" + data + "\"";
      }
      temp += "}         \r\n";
      return temp;
}