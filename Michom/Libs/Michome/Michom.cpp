#include "Michom.h"

ESP8266WebServer server(80);

//
// конструктор - вызывается всегда при создании экземпляра класса Michome
//
Michome::Michome(const char* _ssid, const char* _password, const char* _id, const char* _type, const char* _host, const char* _host1)
{
    String(_ssid).toCharArray(ssid, WL_SSID_MAX_LENGTH);
    String(_password).toCharArray(password, WL_WPA_KEY_MAX_LENGTH);
    id = _id;
    type = _type;
    host1 = _host1;
    host = _host;
    mdns = MDNSResponder();
    //this.server = server;
    IsReadConfig = false;
}

#ifndef NoFS
//
// конструктор - вызывается всегда при создании экземпляра класса Michome
//
Michome::Michome(const char* _id, const char* _type, const char* _host, const char* _host1)
{   
    //ssid = "";
    //password = "";
    String("").toCharArray(ssid, WL_SSID_MAX_LENGTH);
    String("").toCharArray(password, WL_WPA_KEY_MAX_LENGTH);
    id = _id;
    type = _type;
    host1 = _host1;
    host = _host;
    mdns = MDNSResponder();
    //this.server = server;
    IsReadConfig = true;
}
#endif

ESP8266WebServer& Michome::GetServer(){
    return server;
}

//
// Инициализация в Setup
//
void Michome::init(bool senddata)
{
      _init();     
      
      int t1 = TimeoutConnection;
      TimeoutConnection = 1500;
      SendData(ParseJson("init", ""));
      TimeoutConnection = t1;
      
      if(senddata){
        SendData();
      }
}
//
// Инициализация в Setup
//
void Michome::init()
{
      init(false);     
}
//
// Инициализация в Setup
//
void Michome::_init(void)
{
    pinMode(BuiltLED, OUTPUT);
    #ifdef StartLED
        digitalWrite(BuiltLED, LOW);
    #endif
    #ifndef NoFS
        FSLoger.AddLogFile("Start CPU OK");
    #endif
    
      //ESP8266WebServer server = server;
      #ifndef NoSerial
         Serial.begin ( 115200 );
         Serial.setDebugOutput(true);
      #endif  
      
      Serial.println("");      
      
      ArduinoOTA.setHostname(id);     
      ArduinoOTA.onStart([this]() {
        Serial.println("Start");
        #ifndef NoFS
            FSLoger.AddLogFile("Update OTA Start");
        #endif
      });     
      ArduinoOTA.onEnd([this]() {
        Serial.println("\nEnd");
        #ifndef NoFS
            FSLoger.AddLogFile("Update OTA End");
        #endif
      });
      ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
        if(IsBlinkOTA){
            StrobeBuildLed(10);
        }
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      });
      ArduinoOTA.onError([this](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
          Serial.println("Auth Failed");
          #ifndef NoFS
              FSLoger.AddLogFile("Error OTA Auth Failed");
          #endif
        } else if (error == OTA_BEGIN_ERROR) {
          Serial.println("Begin Failed");
          #ifndef NoFS
              FSLoger.AddLogFile("Error OTA Begin Failed");
          #endif
        } else if (error == OTA_CONNECT_ERROR) {
          Serial.println("Connect Failed");
          #ifndef NoFS
              FSLoger.AddLogFile("Error OTA Connect Failed");
          #endif
        } else if (error == OTA_RECEIVE_ERROR) {
          Serial.println("Receive Failed");
          #ifndef NoFS
              FSLoger.AddLogFile("Error OTA Recive Failed");
          #endif
        } else if (error == OTA_END_ERROR) {
          Serial.println("End Failed");
          #ifndef NoFS
              FSLoger.AddLogFile("Error OTA End Failed");
          #endif
        }
      });
      ArduinoOTA.begin();      
      
      if(IsReadConfig){
           WIFIConfig cfg = ReadSSIDAndPassword();
           
           (cfg.SSID).toCharArray(ssid, WL_SSID_MAX_LENGTH);                               
           (cfg.Password).toCharArray(password, WL_WPA_KEY_MAX_LENGTH);
                               
           #if defined(DebugConnection)
            Serial.println("Setting readed " + cfg.SSID + " " + cfg.Password);
           #endif
      }         
      
      #if defined(DebugConnection)
        Serial.println("Connect to " + String(ssid) + " " + String(password));
      #endif
      
      #if defined(UsingFastStart)
        if(WiFi.status() != WL_CONNECTED){
            if (WiFi.getMode() != WIFIMode)
            {
                WiFi.mode(WIFIMode);
                wifi_set_sleep_type(NONE_SLEEP_T); //LIGHT_SLEEP_T and MODE_SLEEP_T
                delay(10);
            }
        }
      #else
        WiFi.disconnect(true);     
        if (WiFi.getMode() != WIFIMode)
        {
            WiFi.mode(WIFIMode);
            wifi_set_sleep_type(NONE_SLEEP_T); //LIGHT_SLEEP_T and MODE_SLEEP_T
            delay(10);
        }
      #endif

      WiFi.hostname(id);      
      
      if(WiFi.status() != WL_CONNECTED)
        WiFi.begin (ssid, password);
    
      if(ssid == "" && password == "") IsConfigured = false;
      else IsConfigured = true;
      
      long wifi_try = millis();      
      // Wait for connection
      while ( (WiFi.status() != WL_CONNECTED) && (ssid != "")) {
        delay ( 500 );
        Serial.print ( "." );      
        if (millis() - wifi_try > WaitConnectWIFI) break;
      }
      
      if(WiFi.status() != WL_CONNECTED){
          #ifndef NoFS
            FSLoger.AddLogFile("Error Connecting to WIFI");
            FSLoger.AddLogFile("Start AP");
          #endif 
          StrobeBuildLedError(2, LOW);
          CreateAP();
          IsConfigured = false;
      }
      
      #if defined(DebugConnection)
        Serial.println("");
      #endif
      
      String locals = (String)id;
      locals.replace('_', '-');
      locals.toLowerCase();
      char mdsnname[locals.length()];
      (locals).toCharArray(mdsnname, locals.length());
      if ( mdns.begin ( mdsnname, WiFi.localIP() ) ) {
        #if defined(DebugConnection)
            Serial.println("MDNS Starting");
        #endif
        mdns.addService("http", "tcp", 80);
      }
      LLMNR.begin(mdsnname);
      
      server.on("/", [this](){
       #ifndef NoFs
        if(!IsConfigured){
            server.send(200, "text/html", WebConfigurator());
        }
        else{
            server.send(200, "text/html", WebMain(type, id));    
        }                        
       #endif
       #ifdef NoFs
        server.send(200, "text/html", WebMain(type, id));
       #endif
      });
      
      server.on("/generate_204", [this](){  //Android captive portal. Maybe not needed. Might be handled by notFound handler.      
        server.send(200, "text/html", WebMain(type, id));
      });
      server.on("/fwlink", [this](){  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.     
        server.send(200, "text/html", WebMain(type, id));
      });        

      server.on("/restart", [this](){ 
        server.send(200, "text/html", "OK");
        #ifndef NoFs
        FSLoger.AddLogFile("Restart from WEB");
        #endif
        ESP.reset();
      });      

      server.on("/getnameandid", [this](){
        String tmpe = (String)Michome::id + "/n" + (String)Michome::type;
        server.send(200, "text/html", tmpe);
      });
      
      server.on("/getrssi", [this](){
        server.send(200, "text/html", String(WiFi.RSSI()));
      });
      
      server.on("/getmoduleinfo", [this](){
        String tmpe = (String)Michome::id + "/n" + (String)Michome::type + "/n" + String(WiFi.RSSI()) + "/n" + String(WiFi.localIP().toString()) + "/n";
        tmpe += String(ESP.getFlashChipRealSize());
        #if defined(ADCV)
            tmpe += "/n" + String(ESP.getVcc());
        #else
            tmpe += "/n" + String("null");
        #endif
        server.send(200, "text/html", tmpe);
      });
      
      #ifdef ADCV
           server.on("/getvcc", [this](){
            server.send(200, "text/html", String(ESP.getVcc()));
          });
      #endif
      
      server.on("/setsettings", [this](){         
        String settinga = "";
            for(int i=1; i < server.args(); i++) settinga += server.argName(i) + "=" + server.arg(i) + ";";
        Michome::countsetting = Split(Split(settinga, ';', 0), '=', 1).toInt();
        Michome::settings = settinga;
        IsSettingRead = true;
        Serial.println("Setting read OK");
        #ifndef NoFs
        FSLoger.AddLogFile("Setting read OK");
        #endif
        server.send(200, "text/html", settinga);
      });     
      
      server.on("/getsettings", [this](){
        server.send(200, "text/html", GetSetting());
      });
      
      server.on("/getdigital", [this](){
        int pin = server.arg("p").toInt();
        server.send(200, "text/html", String(digitalRead(pin)));
      });
      
      server.on("/getanalog", [this](){
        server.send(200, "text/html", String(analogRead(A0)));
      });    

      /*server.on("/updatemanager", HTTP_GET, [this](){
          const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
          server.sendHeader("Connection", "close");
          server.sendHeader("Access-Control-Allow-Origin", "*");
          server.send(200, "text/html", serverIndex);
        });
      server.on("/update", HTTP_POST, [this](){
          server.sendHeader("Connection", "close");
          server.sendHeader("Access-Control-Allow-Origin", "*");
          server.send(200, "text/plain", (Update.hasError())?"FAIL":"OK");
          ESP.restart();
        },[](){
          HTTPUpload& upload = server.upload();
          if(upload.status == UPLOAD_FILE_START){
            Serial.setDebugOutput(true);
            WiFiUDP::stopAll();
            Serial.printf("Update: %s\n", upload.filename.c_str());
            uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
            if(!Update.begin(maxSketchSpace)){//start with max available size
              Update.printError(Serial);
            }
          } else if(upload.status == UPLOAD_FILE_WRITE){
            if(Update.write(upload.buf, upload.currentSize) != upload.currentSize){
              Update.printError(Serial);
            }
          } else if(upload.status == UPLOAD_FILE_END){
            if(Update.end(true)){ //true to set the size to the current progress
              Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
              Update.printError(Serial);
            }
            Serial.setDebugOutput(false);
          }
          yield();
        });*/
      
    #ifndef NoFS
      
      server.on("/getconfig", [this](){
        WIFIConfig wf = ReadSSIDAndPassword();
        server.send(200, "text/html", wf.SSID + "<br />" + wf.Password);
      });
      
      server.on("/setconfig", [this](){
        String ss = server.arg("ssid");
        String pw = server.arg("password");
        WriteSSIDAndPassword(ss, pw);
        
        if(ss == "" && pw == "")
            IsConfigured = false;
        else
            IsConfigured = true;
        
        FSLoger.AddLogFile("Config Saved");
        WIFIConfig wf = ReadSSIDAndPassword();
        server.send(200, "text/html", wf.SSID + "<br />" + wf.Password);
        yieldM();
        delay(10);
        ESP.reset();
      });
      
      server.on("/resetconfig", [this](){
        WriteSSIDAndPassword("", "");        
        IsConfigured = false;
        
        FSLoger.AddLogFile("Config Reset");
        server.send(200, "text/html", "OK");
        ESP.reset();
      });
      
      server.on("/configurator", [this](){
        server.send(200, "text/html", WebConfigurator());    
      });

      server.on("/getlogs", [this](){
        server.send(200, "text/html", FSLoger.ReadLogFile());    
      });  
      
      server.on("/addlog", [this](){
        String setting = server.arg("log");
        FSLoger.AddLogFile(setting);
        server.send(200, "text/html", FSLoger.ReadLogFile());    
      });

      server.on("/clearlogs", [this](){
        FSLoger.ClearLogFile();
        server.send(200, "text/html", "OK");    
      });
      
      #ifdef WriteDataToFile
        server.on("/getdatalogs", [this](){
            server.send(200, "text/html", DataFile().ReadFile());    
        });
        
        server.on("/resetdatalogs", [this](){
            DataFile().ClearFile();
            server.send(200, "text/html", "OK");    
        });
      #endif

    #endif      
      
      server.on("/description.xml", HTTP_GET, [this](){
        SSDP.schema(server.client());
      });
      
      
      server.onNotFound([this](){
        server.send(404, "text/html", "Not found");
      });
      
      server.begin();
      dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
      dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
      
      SSDP.setDeviceType("upnp:rootdevice");
      SSDP.setSchemaURL("description.xml");
      SSDP.setHTTPPort(80);
      SSDP.setName(String(id));
      SSDP.setSerialNumber((String)ESP.getFlashChipId());
      SSDP.setURL("/");
      SSDP.setModelName(String("MichomModule-")+Michome::type);
      SSDP.setModelNumber("000000000001");
      SSDP.setModelURL("http://www.github.com/microfcorp/michome");
      SSDP.setManufacturer("Microf-Corp");
      SSDP.setManufacturerURL("http://www.microfcorp.ml");
      SSDP.begin();
      
      StrobeBuildLed(70);
      
      #ifdef UsingWDT
          ESP.wdtDisable();
          ESP.wdtEnable(WDTO_8S);
      #endif
}

void Michome::CreateAP(void){
    WiFi.softAP(Michome::id, PasswordAPWIFi);
    
    IPAddress myIP = WiFi.softAPIP(); //192.168.4.1 is default
	Serial.print("AP IP address: ");
	Serial.println(myIP);    
}

//
// Цикл в Loop
//
void Michome::running(void)
{
#ifdef UsingWDT
    ESP.wdtFeed();   // покормить пёсика
#endif
    
#ifndef NoAutoReconect
  #pragma NoReconnecting
  if ((WiFi.status() != WL_CONNECTED) && (ssid != "")) {
      #ifndef NoFS
          FSLoger.AddLogFile("Reconecting to WIFI");
      #endif 
      Serial.println("Reconecting to WIFI...");   
      WiFi.disconnect(true);
      WiFi.begin(ssid, password);
      long wifi_try = millis();
      while (WiFi.status() != WL_CONNECTED) {
         delay(500);
         #ifdef UsingWDT
             ESP.wdtFeed();   // покормить пёсика
         #endif
         Serial.print(".");
         if (millis() - wifi_try > 10000) break;
      }
      Serial.println("");
  }
#endif

#ifndef NoCheckWIFI
if((WiFi.status() != WL_CONNECTED) && (millis() - wifi_check > 10000)){
    wifi_check = millis();
    #ifdef UsingWDT
        ESP.wdtFeed();   // покормить пёсика
    #endif
    Serial.println("Connection lost");
    #ifndef NoFS
          FSLoger.AddLogFile("Connection lost");
    #endif
}
#endif

  //mdns.update();
  server.handleClient();
  ArduinoOTA.handle();
  dnsServer.processNextRequest();
}

void Michome::StrobeBuildLed(byte timeout){
    digitalWrite(BuiltLED, LOW);
    delay(timeout);
    digitalWrite(BuiltLED, HIGH);
}
void Michome::StrobeBuildLedError(int counterror, int statusled){
    for(int i = 0; i < counterror; i++)
        StrobeBuildLed(30);
    digitalWrite(BuiltLED, statusled);
}

#ifndef NoFS

#pragma NoFS

WIFIConfig Michome::ReadSSIDAndPassword(){
    SPIFFS.begin();//инициальзация фс       
    WIFIConfig cf;
    
    File f = SPIFFS.open("/config.txt", "r");
    if (!f) {
        Serial.println("file open failed");  //  "открыть файл не удалось"
        SPIFFS.end();//денициализация фс
        cf.SSID = "";
        cf.SSID = "";
        return cf;
    }
    else{
        String cfg = f.readString();
        SPIFFS.end();//денициализация фс
        
        cf.SSID = Split(cfg, '\n', 0);
        cf.Password = Split(cfg, '\n', 1);
        
        return cf;
    }    
}

void Michome::WriteSSIDAndPassword(String ssid, String password){
    SPIFFS.begin();//инициальзация фс
    
    
    File f = SPIFFS.open("/config.txt", "w");
    if (!f) {
        Serial.println("file open failed");  //  "открыть файл не удалось"
        SPIFFS.end();//денициализация фс
        return;
    }
    else{
        String writestr = ssid + "\n" + password;
        f.print(writestr);
        SPIFFS.end();//денициализация фс                     
        return;
    }    
}

void Michome::WriteSSIDAndPassword(String txt){
    SPIFFS.begin();//инициальзация фс
    
    
    File f = SPIFFS.open("/config.txt", "w");
    if (!f) {
        Serial.println("file open failed");  //  "открыть файл не удалось"
        SPIFFS.end();//денициализация фс
        return;
    }
    else{
        f.print(txt);
        SPIFFS.end();//денициализация фс                     
        return;
    }    
}

#endif

String Michome::GetSetting(String name){
    //update=6000;log=1    
    for(int i = 0; i < countsetting; i++){
        if(Split(Split(settings, ';', i), '=', 0) == name){
            return Split(Split(settings, ';', i), '=', 1);
        }
    }
    return String("");
}

int Michome::GetSettingToInt(String name){
    //update=6000;log=1    
    for(int i = 0; i < countsetting; i++){
        if(Split(Split(settings, ';', i), '=', 0) == name){
            return Split(Split(settings, ';', i), '=', 1).toInt();
        }
    }
    return DefaultSettingInt;
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
          if((WiFi.status() != WL_CONNECTED))
              return "";
          
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
          if((WiFi.status() != WL_CONNECTED))
              return "";
          
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
void Michome::SendData()
{
    SendData(ParseJson(String(type), ""));
}
void Michome::SendData(String Data)
{  
          #ifdef TimeSending
            unsigned long starttime = millis();
          #endif
          
          if((WiFi.status() != WL_CONNECTED))
              return;
       
          #if !defined(NoFS) && !defined(NoAddLogSendData) && !defined(NoDataAddLogSendData)
              FSLoger.AddLogFile("Sending data: " + Data);             
          #endif         
                   
          // Use WiFiClient class to create TCP connections
          WiFiClient client;
          const int httpPort = 80;
          if (!client.connect(host1, httpPort)) {
            Serial.println("CF");
            #ifndef NoFS
            FSLoger.AddLogFile("Connection Failed");
            #endif
            return;
          }         
          
          // This will send the request to the server
          client.print(String("POST ") + "http://" + host + " HTTP/1.1\r\n" +
                       "Host: " + host1 + "\r\n" + 
                       "Content-Length: " + (String)Data.length() + "\r\n" +
                       "Content-Type: application/x-www-form-urlencoded \r\n" +
                       "Connection: close\r\n\r\n" +
                       "6=" + Data);
                       
          
          client.stop();
          /*
          //while (client.available() == 0) {
            if (millis() - timeout > TimeoutConnection) {
              //Serial.println("Error");
              #if !defined(NoFS) && defined(NoAddLogSendData)
              FSLoger.AddLogFile("Send data failed");
              #endif
              client.stop();
              return;
            }
          //}
          */
          
          /*delay(1000);
          // Read all the lines of the reply from server and print them to Serial
          String line = "";
          while(client.available()){
            line = client.readStringUntil('\r');
          }*/
          
          //Serial.println();
          
          Serial.println("Data sending");
          #if !defined(NoFS) && !defined(NoAddLogSendData)
          FSLoger.AddLogFile("Send data OK");
          #endif

          //return line; 

          #ifdef TimeSending
              unsigned long endtime = millis();                  
              FSLoger.AddLogFile("Time Sending: " + String(endtime - starttime));
          #endif
          yield();
}
String Michome::GetModule(byte num){
    if(num == 0) return id;        
    else if(num == 1) return type;
    else return "";
}
void Michome::yieldM(void){
    yield();
    running();
    yield();
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
      #if defined(WriteDataToFile) && !defined(NoFS)
        DataFile().AddTextToFile("Sending data: " + data);
      #endif
              
      String temp = "";
      temp += "{";
      temp += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
      temp += "\"rssi\":\"" + String(WiFi.RSSI()) + "\",";
      temp += "\"secretkey\":\"" + sha1(String("MICHoMeMoDuLe")) + "\",";
      temp += "\"secret\":\"" + String("MICHoMeMoDuLeORIGINALFIRMWARE") + "\",";
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
      else if(type == "get_button_press"){    
          temp += "\"data\":{";
          temp += "\"status\": \"" + data + "\" }";
      }
      else{
          temp += "\"data\":\"" + data + "\"";
      }
      temp += "}         \r\n";
      return temp;
}