#include <Michom.h>

const char* id = "Logger";
const char* type = "Log";
/////////настройки//////////////

Michome michome(id, type);

Logger debuging = michome.GetLogger();

ESP8266WebServer& server1 = michome.GetServer();

void setup(void) 
{      
    server1.on("/printlog", [](){
        debuging.Log("On printlog");        
        server1.send(200, "text/html", String("OK"));    
    });    
    michome.init(true);
}

void loop(void)
{
    michome.running();
}