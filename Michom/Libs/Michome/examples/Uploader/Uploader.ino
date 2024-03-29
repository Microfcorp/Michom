#include <Michom.h>

const char* id = "Logger";
const char* type = "Log";
/////////настройки//////////////

Michome michome(id, type);

ESP8266WebServer& server1 = michome.GetServer();

void setup(void) 
{      
    server1.on("/logstatus", [](){ 
        server1.send(200, "text/html", String("OK"));    
    });    
    michome.init(true);
}

void loop(void)
{
    michome.running();
}