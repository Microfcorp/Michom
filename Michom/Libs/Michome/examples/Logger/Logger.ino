#include <Michom.h>

const char *ssid = "10-KORPUSMG";
const char *password = "10707707";

const char* id = "Logger";
const char* type = "Log";
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

Michome michome(ssid, password, id, type, host, host1);

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