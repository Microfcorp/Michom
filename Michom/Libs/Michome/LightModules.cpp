#include "LightModules.h"

Telnet telnLM(23);

//
// конструктор - вызывается всегда при создании экземпляра класса LightModules
//
LightModules::LightModules(Michome m)
{
    gtw = m;
}

Telnet& LightModules::GetTelnet(){
    return telnLM;
}

void LightModules::AddPin(LightPin Pin){
    Pins.add(Pin);
}

String LightModules::GetPins(){
    String tmp = "";
    for(int i = 0; i < Pins.size(); i++){
        tmp += (String)i + "(" + Pins.get(i).Pin + ") - " + String(Pins.get(i).Type == 0 ? "Relay" : "PWM")  + "<br />";
    }
    return tmp;
}

/*void LightModules::RunData(LightData LD){
    
}*/

void LightModules::SetLight(byte pin, PinType type, int brith){
    if(type == PWM)
        analogWrite(pin, brith);
    else if (type == Relay)
        digitalWrite(pin, (brith > 0 ? HIGH : LOW));
    
    //
    if(SaveState){
        FSFiles pinstext = FSFiles("/lm"+(String)pin+".txt");
        pinstext.WriteFile((String)pin + "=" + type + "=" + brith);
    }
}

void LightModules::SetLightID(byte id, int brith){
    SetLight(Pins.get(id).Pin, Pins.get(id).Type, brith);
}

void LightModules::SetLightAll(int brith){    
    for(int i = 0; i < Pins.size(); i++){
        SetLightID(i, brith); 
    }  
}

void LightModules::Strobo(byte pin, int col, int del){   
    col = col > 300 ? 300 : col;
    del = del > 1000 ? 1000 : del;
    bool stops = SaveState;    
    SaveState = false;
    for (int i = 0; i < col; i++) {
       SetLightID(pin, MaximumBrightnes);
       //gtw.yieldM();
       delay(del);
       SetLightID(pin, MinimumBrightnes);
       //gtw.yieldM();
       delay(del);
    }
    SaveState = stops;
}

void LightModules::StroboPro(byte pin, int col, int del, int pdel){ 
    col = col > 300 ? 300 : col;
    del = del > 1000 ? 1000 : del; 
    bool stops = SaveState;    
    SaveState = false;    
    for (int i = 0; i < col; i++) {
       SetLightID(pin, MaximumBrightnes);
       //gtw.yieldM();
       delay(del);
       SetLightID(pin, MinimumBrightnes);
       //gtw.yieldM();
       delay(pdel);
    }
    SaveState = stops;    
}

void LightModules::StroboAll(int col, int del){   
    col = col > 300 ? 300 : col;
    del = del > 1000 ? 1000 : del;
    bool stops = SaveState;    
    SaveState = false;
    for (int i = 0; i < col; i++) {
       SetLightAll(MaximumBrightnes);
       //gtw.yieldM();
       delay(del);
       SetLightAll(MinimumBrightnes);
       //gtw.yieldM();
       delay(del);
    }   
}

void LightModules::StroboAllPro(int col, int del, int pdel){   
    col = col > 300 ? 300 : col;
    del = del > 1000 ? 1000 : del;
    bool stops = SaveState;    
    SaveState = false;
    for (int i = 0; i < col; i++) {
       SetLightAll(MaximumBrightnes);
       //gtw.yieldM();
       delay(del);
       SetLightAll(MinimumBrightnes);
       //gtw.yieldM();
       delay(pdel);
    } 
    SaveState = stops;    
}

/*String LightModules::JSONParse(String text){
    //Serial.println("jsonp");
    String tmp = "";
      DynamicJsonBuffer jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(text);
      int leg = root["Params"].size();
      int delays = 0;
      tmp += "Name = " + root["name"].as<String>() + "<br />";
      for (int i = 0; i < leg; i++) {
        //tmp += root["Params"][i]["name"].as<String>() + "<br />";
        if (root["Params"][i]["name"].as<String>() == "playmusic") {
          //http://192.168.1.42:8080/jsonrpc?request={%22jsonrpc%22:%222.0%22,%22id%22:%221%22,%22method%22:%22Player.Open%22,%22params%22:{%22item%22:{%22file%22:%22'+file+'%22}}}
          //gtw.SendDataGET("/jsonrpc?request={\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Player.Open\",\"params\":{\"item\":{\"file\":\"" + root["Params"][i]["file"].as<String>() + "\"}}}", "192.168.1.42", 8080);
          delays = 0;
        }
        else if (root["Params"][i]["name"].as<String>() == "setlight") {
          SetLightID(root["Params"][i]["pin"].as<int>(), root["Params"][i]["brightness"].as<int>());
          delays = 0;
          //logg.Log((String)i + " Setlight");
        }
        else if (root["Params"][i]["name"].as<String>() == "setlightall") {
          SetLightAll(root["Params"][i]["brightness"].as<int>());
          delays = 0;
          //logg.Log((String)i + " Setlight");
        }
        else if (root["Params"][i]["name"].as<String>() == "strobo") {
          int col = root["Params"][i]["col"];
          Strobo(root["Params"][i]["pin"].as<int>(), col, root["Params"][i]["times"].as<int>());
          delays = col * (root["Params"][i]["times"].as<int>() * 2);
          //logg.Log((String)i + " strobo");
        }
        else if (root["Params"][i]["name"].as<String>() == "strobopro") {
          int col = root["Params"][i]["col"];
          StroboPro(root["Params"][i]["pin"].as<int>(), col, root["Params"][i]["times"].as<int>(), root["Params"][i]["nostrob"].as<int>());
          delays = col * ((root["Params"][i]["times"].as<int>() + root["Params"][i]["nostrob"].as<int>()) * 2);
          //logg.Log((String)i + " strobo");
        }
        else if (root["Params"][i]["name"].as<String>() == "stroboall") {
          int col = root["Params"][i]["col"];
          StroboAll(col, root["Params"][i]["times"].as<int>());
          delays = col * (root["Params"][i]["times"].as<int>() * 2);
          //logg.Log((String)i + " stroboall");
        }
        else if (root["Params"][i]["name"].as<String>() == "stroboallpro") {
          int col = root["Params"][i]["col"];
          StroboAllPro(col, root["Params"][i]["times"].as<int>(), root["Params"][i]["nostrob"].as<int>());
          delays = col * ((root["Params"][i]["times"].as<int>() + root["Params"][i]["nostrob"].as<int>()) * 2);
          //logg.Log((String)i + " stroboall");
        }
        else if (root["Params"][i]["name"].as<String>() == "sleep") {
          //logg.Log((String)i + " sleep");
          //delay((root["Params"][i]["times"].as<float>() * 1000) - delays);
        }
      }
      return tmp;
      //logg.Log(tmp);
}*/
int LightModules::StartFade(FadeData data){
    for(int i = 0; i < Fades.size(); i++){
        if(GetFade(i).Pin == data.Pin) StopFade(i);
    }
    countfade++;
    data.IsRun = true;    
    Fades.add(data);
    SetLightID(data.Pin, data.MinV);
}
FadeData LightModules::GetFade(int id){
    return Fades.get(id);
}
void LightModules::StopFade(int id){
    Fades.remove(id);
    countfade--;
}
void LightModules::SetFade(int id, FadeData fd){
    Fades.set(id, fd);
}
void LightModules::StopAllFade(){
    for(int i = 0; i < Fades.size(); i++){
        FadeData fd = GetFade(i);
        fd.IsRun = false;
        SetFade(i, fd);
    }
}

bool LightModules::AddBuferState(byte pin, int brith){
    for(int i = 0; i < Bufers.size(); i++){
        BufferData bf = Bufers.get(i);
        if(bf.Pin == pin){
            Bufers.set(i, {pin, brith});
            return true;
        }
    }
    Bufers.add({pin, brith});
    return false;
}

void LightModules::RunBuffer(){
    for(int i = 0; i < Bufers.size(); i++){
        BufferData bf = Bufers.get(i); 
        SetLightID(bf.Pin, bf.Brig);
    }
}

void LightModules::init(){
    bool stops = SaveState;    
    SaveState = false;
    for(int i = 0; i < Pins.size(); i++){
        pinMode(Pins.get(i).Pin, OUTPUT); 
        SetLightID(i, 0);
    }

    if(stops){
        for(int i = 0; i < Pins.size(); i++){
            FSFiles pinstext = FSFiles("/lm"+(String)Pins.get(i).Pin+".txt");
            String rdd = pinstext.ReadFile();
            int typepin = gtw.Split(rdd, '=', 1).toInt();
            int br = gtw.Split(rdd, '=', 2).toInt();
            SetLight(Pins.get(i).Pin, (PinType)typepin, br);
        }
    } 
    SaveState = stops;    
    
    ESP8266WebServer& server1 = gtw.GetServer();
    
      /*server1.on("/jsonget", [&]() {
         JSONParse(server1.arg(0));
        server1.send(200, "text/html", "OK");
      });*/

      server1.on("/setlight", [&]() {
        SetLightID(server1.arg(0).toInt(), server1.arg(1).toInt());
        server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()));
      });

      server1.on("/setlightall", [&]() {
        SetLightAll(server1.arg(0).toInt());
        server1.send(200, "text/html", "all as " + String(server1.arg(0).toInt()));
      });

      server1.on("/strobo", [&]() {
        server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()));
        Strobo(server1.arg(0).toInt(), server1.arg(1).toInt(), server1.arg(2).toInt());
      });

      server1.on("/strobopro", [&]() {
        server1.send(200, "text/html", String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()) + " as " + String(server1.arg(2).toInt()) + "/" + String(server1.arg(3).toInt()));
        StroboPro(server1.arg(0).toInt(), server1.arg(1).toInt(), server1.arg(2).toInt(), server1.arg(3).toInt());
      });

      server1.on("/stroboall", [&]() {
        server1.send(200, "text/html", String("all") + " as " + String(server1.arg(0).toInt()));
        StroboAll(server1.arg(0).toInt(), server1.arg(1).toInt());
      });

      server1.on("/stroboallpro", [&]() {
        server1.send(200, "text/html", String("all") + " as " + String(server1.arg(0).toInt()) + " as " + String(server1.arg(1).toInt()) + "/" + String(server1.arg(2).toInt()));
        StroboAllPro(server1.arg(0).toInt(), server1.arg(1).toInt(), server1.arg(2).toInt());
      });
      
      
      server1.on("/startfadeup", [&]() {
        server1.send(200, "text/html", "FadeUp start");
        StartFade(CreateFadeData(Up, server1.arg(1).toInt(), server1.arg(0).toInt(), server1.arg(2).toInt(), 0));
      });     
      
      server1.on("/startfadedown", [&]() {
        server1.send(200, "text/html", "FadeDown start");
        StartFade(CreateFadeData(Down, server1.arg(1).toInt(), server1.arg(0).toInt(), server1.arg(2).toInt(), 0));
      });
      
      server1.on("/stopfade", [&]() {
        server1.send(200, "text/html", "Sumeer stop");
        StopAllFade();
      });
      
      server1.on("/getfades", [&]() {
        server1.send(200, "text/html", String(Fades.size()));
      });
      
      server1.on("/getpins", [&]() {
        server1.send(200, "text/html", String(GetPins()));
      });
      
      server1.on("/calculatetimesum", [&]() {
        server1.send(200, "text/html", String((server1.arg(1).toInt()*server1.arg(0).toInt())/1000) + " seconds");
      });
           
      server1.on("/remotepins", [&]() {
        String tmp = RussianHead("Управление выводами");
        for(int i = 0; i < Pins.size(); i++){
            tmp += (String)"<p>" + i + " (" + String(Pins.get(i).Type == 0 ? "Relay" : "PWM") + ") " + String(Pins.get(i).Type == 0 ? "" : (String)"<input type='number' maxlength='4' min='"+MinimumBrightnes+"' max='"+MaximumBrightnes+"' id='pwm"+(String)(i+1)+(String)"' />") + " <a href='#' onclick=\"postAjax(\'setlight?p="+i+"&q="+String(Pins.get(i).Type == 0 ? MaximumBrightnes : "'+pwm"+(String)(i+1)+(String)".value+'")+"\', GET, \'\', function(d){}); return false;\">Применить значение</a> <a href='#' onclick=\"postAjax(\'setlight?p="+i+"&q="+MinimumBrightnes+"\', GET, \'\', function(d){}); return false;\">Выключить</a> "  + "</p>";
        }
        server1.send(200, "text/html", AJAXJs + tmp + (String)"<br /><a href='/'>Главная</a>");
      });
     
      
    if(TelnetEnable){
        telnLM.Init();
    }
}

void LightModules::TelnetRun(String telnd){
    String type = gtw.Split(telnd, ';', 0);
        if (type == "setlight") { //setlight;0;1023 pin;val
          SetLightID((gtw.Split(telnd, ';', 1).toInt()), gtw.Split(telnd, ';', 2).toInt());
        }
        else if (type == "setlightall") { //setlightall;1023 val
          SetLightAll(gtw.Split(telnd, ';', 1).toInt());
        }
        else if (type == "strobo") { //strobo;2;4;100 pin;col;sleep
          int col = gtw.Split(telnd, ';', 2).toInt();
          Strobo(Pins.get(gtw.Split(telnd, ';', 1).toInt()).Pin, col, gtw.Split(telnd, ';', 3).toInt());
        }
        else if (type == "strobopro") { //strobopro;10;0;100;50 col;pin;sleep;sleep2
          int col = gtw.Split(telnd, ';', 1).toInt();
          StroboPro(Pins.get(gtw.Split(telnd, ';', 1).toInt()).Pin, col, gtw.Split(telnd, ';', 3).toInt(), gtw.Split(telnd, ';', 4).toInt());
        }
        else if (type == "stroboall") { //stroboall;10;100 col;sleep
          int col = gtw.Split(telnd, ';', 1).toInt();
          StroboAll(col, gtw.Split(telnd, ';', 2).toInt());
        }
        else if (type == "stroboallpro") { //stroboallpro;10;100;50 col;sleep;sleep2
          int col = gtw.Split(telnd, ';', 1).toInt();
          StroboAllPro(col, gtw.Split(telnd, ';', 2).toInt(), gtw.Split(telnd, ';', 3).toInt());
        }
        else if (type == "fadestart") { //fadestart;10;100;50 col;sleep;sleep2
          int col = gtw.Split(telnd, ';', 1).toInt();
          FadeData l1 = CreateFadeData((FadeType)gtw.Split(telnd, ';', 2).toInt(), gtw.Split(telnd, ';', 3).toInt(), gtw.Split(telnd, ';', 4).toInt(), gtw.Split(telnd, ';', 5).toInt(), gtw.Split(telnd, ';', 6).toInt());
          StartFade(l1);
        }
        else if (type == "fadestop") { //fadedown;10;100;50 col;sleep;sleep2
          int col = gtw.Split(telnd, ';', 1).toInt();
          StopFade(gtw.Split(telnd, ';', 2).toInt());
        }
        else if (type == "stopallfade") { //fadestop;
          StopAllFade();
        }
}

void LightModules::running(){
    if(TelnetEnable){
        telnLM.Running();
        
        if(telnLM.IsDataAvalible()){
            TelnetRun(telnLM.GetData());
        }
    }
    
    for(int i = 0; i < countfade; i++){
        FadeData fd = GetFade(i);
        
        if(fd.IsRun){
            if(millis() - fd.Interval > fd.CurMillis) {
               fd.CurMillis = millis();   // запоминаем текущее время
     
                if(fd.Type == Up)
                    fd.CurV++;
                else if(fd.Type == Down)
                    fd.CurV--;
                else if(fd.Type == Stop)
                    StopFade(i);
        
               bool stops = SaveState;    
               SaveState = false; 
               SetLightID(fd.Pin, fd.CurV);
               SaveState = stops;
               if(fd.CurV == fd.MaxV) fd.IsRun = false;              
               //delay(1);
               gtw.yieldM();
            }     
        }
        SetFade(i, fd);        
        if(!fd.IsRun) StopFade(i);
        if(i >= Fades.size()) break;       
    }
}