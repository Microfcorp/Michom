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
void Michome::init(bool senddata)
{
      _init();
      if(senddata){
        Serial.println(SendData());
      }
      SendData(ParseJson("init", ""));
}
//
// Инициализация в Setup
//
void Michome::init()
{
      _init();
      SendData(ParseJson("init", ""));
}
//
// Инициализация в Setup
//
void Michome::_init(void)
{
      //ESP8266WebServer server = server;
      Serial.begin ( 115200 );
      WiFi.begin ( ssid, password );
      
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
        if (error == OTA_AUTH_ERROR) {
          Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
          Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
          Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
          Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
          Serial.println("End Failed");
        }
      });
      ArduinoOTA.begin();
      
      // Wait for connection
      while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 500 );
        Serial.print ( "." );
      }

      if ( mdns.begin ( "esp8266", WiFi.localIP() ) ) {}
      
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
    //Warning

      server.on("/getnameandid", [this](){
        String tmpe = (String)Michome::id + "/n" + (String)Michome::type;
        server.send(200, "text/html", tmpe);
      });
      
      server.on("/getrssi", [this](){
        server.send(200, "text/html", String(WiFi.RSSI()));
      });
      
      server.on("/getmoduleinfo", [this](){
        String tmpe = (String)Michome::id + "/n" + (String)Michome::type + "/n" + String(WiFi.RSSI()) + "/n" + String(WiFi.localIP().toString());
        server.send(200, "text/html", tmpe);
      });
      
      server.on("/setsettings", [this](){
        String setting = server.arg(0);
        Michome::settings = setting;
        IsSettingRead = true;
        server.send(200, "text/html", "OK");
      });
      
      server.on("/getsettings", [this](){
        server.send(200, "text/html", GetSetting());
      });
      
      server.on("/description.xml", HTTP_GET, [this](){
        SSDP.schema(server.client());
      });
      
      server.onNotFound([this](){
        server.send(404, "text/html", "Not found");
      });
      
      server.begin();
      
      SSDP.setDeviceType("upnp:rootdevice");
      SSDP.setSchemaURL("description.xml");
      SSDP.setHTTPPort(80);
      SSDP.setName(String(id));
      SSDP.setSerialNumber("100070700105");
      SSDP.setURL("/");
      SSDP.setModelName(String("MichomModule-")+Michome::type);
      SSDP.setModelNumber("000000000001");
      SSDP.setModelURL("http://www.github.com/microfcorp/michome");
      SSDP.setManufacturer("Microf-Corp");
      SSDP.setManufacturerURL("http://www.microfcorp.ml");
      SSDP.begin();
              
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

String Michome::GetSetting(String name){
    //update=6000;log=1    
    for(int i = 0; i < countsetting; i++){
        if(Split(Split(settings, ';', i), '=', 0) == name){
            return Split(Split(settings, ';', i), '=', 1);
        }
    }
    return String("");
}

String Michome::GetSetting(){
    return settings;
}

void Michome::SetFormatSettings(int count){
    countsetting = count;
}

bool Michome::GetSettingRead()
{
    if(IsSettingRead){
        IsSettingRead = false;
        return true;
    }
    return false;
}
  
//
// 
//
String Michome::SendDataGET(String gateway, const char* host, int Port)
{ 
		  // Use WiFiClient class to create TCP connections
		  WiFiClient client;
		  const int httpPort = Port;
		  if (!client.connect(host, httpPort)) {
			return "connection failed";
		  }		
		  
		  // This will send the request to the server
		  client.print(String("GET ") + (String)gateway + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
		  unsigned long timeout = millis();
		  while (client.available() == 0) {
			if (millis() - timeout > 5000) {
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
		  // Use WiFiClient class to create TCP connections
		  WiFiClient client;
		  const int httpPort = Port;
		  if (!client.connect(host, httpPort)) {
			return "connection failed";
		  }		  
		  
		  // This will send the request to the server
		  client.print(String("POST ") + "http://" + (String)gateway + " HTTP/1.1\r\n" +
					   "Host: " + (String)host + "\r\n" + 
					   "Content-Length: " + (String)Data.length() + "\r\n" +
					   "Content-Type: application/x-www-form-urlencoded \r\n" +
					   "Connection: close\r\n\r\n" +
					   Data);
		  unsigned long timeout = millis();
		  while (client.available() == 0) {
			if (millis() - timeout > 5000) {
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
String Michome::SendData()
{
    SendData(ParseJson(String(type), ""));
}
String Michome::SendData(String Data)
{         
          // Use WiFiClient class to create TCP connections
          WiFiClient client;
          const int httpPort = 80;
          if (!client.connect(host1, httpPort)) {
            Serial.println("connection failed");
          }         
          
          // This will send the request to the server
          client.print(String("POST ") + "http://" + host + " HTTP/1.1\r\n" +
                       "Host: " + host1 + "\r\n" + 
                       "Content-Length: " + (String)Data.length() + "\r\n" +
                       "Content-Type: application/x-www-form-urlencoded \r\n" +
                       "Connection: close\r\n\r\n" +
                       "6=" + Data);
                       
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
          Serial.println("Data sending");
          //client = null;
          return line;         
}
Logger Michome::GetLogger()
{
      return Logger(host, host1);
}
String Michome::Split(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
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
      else if(type == "LightStudio"){    
          temp += "\"data\":{";
          temp += "\"status\": \"" + String("OK") + "\"}";
      }
      else if(type == "Informetr"){    
          temp += "\"data\":{";
          temp += "\"data\": \"" + String("GetData") + "\"}";
      }
      else if(type == "Log"){    
          temp += "\"data\":{";
          temp += "\"log\": \"" + String("On Running") + "\"}";
      }
      else if(type == "hdc1080"){    
          temp += "\"data\":{";
          temp += "\"temper\": \"" + Split(data, ';', 0) + "\",";
          temp += "\"humm\": \"" + Split(data, ';', 1) + "\"}";
      }
      else if(type == "termometr"){    
          temp += "\"data\":{";
          temp += "\"temper\": \"" + data + "\"}";
      }
      else if(type == "msinfoo"){    
          temp += "\"data\":{";
          temp += "\"davlen\": \"" + Split(data, ';', 0) + "\",";
          temp += "\"temperbmp\": \"" + Split(data, ';', 1) + "\",";
          temp += "\"visot\": \"" + Split(data, ';', 2) + "\",";
          temp += "\"temper\": \"" + Split(data, ';', 3) + "\",";
          temp += "\"humm\": \"" + Split(data, ';', 4) + "\" }";
      }
      else if(type == "init"){    
          temp += "\"data\":{";
          temp += "\"type\": \"" + String(Michome::type) + "\",";
          temp += "\"id\": \"" + String(Michome::id) + "\" }";
      }
      else{
          temp += "\"data\":\"" + data + "\"";
      }
      temp += "}         \r\n";
      return temp;
}