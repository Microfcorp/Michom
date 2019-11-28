#ifndef WebPages_h
#define WebPages_h
    static inline String WebConfigurator(){
        String div = "";
        #ifndef NoScanWIFi
          int n = WiFi.scanNetworks();
          if(n != 0)
          {
            for (int i = 0; i < n; ++i)
            {
              div += "<p>";
              div += "<a href=\"#\" onclick=\"Change('"+String(WiFi.SSID(i))+"')\">"+String(WiFi.SSID(i))+" ("+String(WiFi.RSSI(i))+" dBm)</a>";
              div += "</p>";              
            }
          }  
        #endif
        return ("<!Doctype html><html><head><title>Конфигурация модуля</title><meta charset=\"UTF-8\"><script>function Change(d){ssid.value = d;}</script></head><body><div>"+div+"<div><br /><form action=\"/setconfig\" method=\"get\"><p>SSID: <input type=\"text\" id=\"ssid\" name=\"ssid\"></p><p>Пароль: <input type=\"text\" name=\"password\"></p><p><input type=\"submit\" value=\"Отправить\"></p></form></body></html>");
    }
#endif // #ifndef Michom_h