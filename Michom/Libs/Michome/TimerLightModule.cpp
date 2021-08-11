#include "TimerLightModule.h"

TimerLightModule::TimerLightModule(LightModules *m){
    light = m;
    gtw = (*light).GetMichome();
}

void TimerLightModule::Save(){
    int countQ = Qs.size();
    String sb = ((String)countQ) + "|";
    for(int i = 0; i < countQ; i++){
        TimeLightModuleQ em = Qs.get(i);
        sb += String(em.Hour) + ";" + String(em.Minutes) + ";" + String(em.Enable) + ";" + String(em.Pin) + ";" + String(em.State) + ";" + (em.IsDynamic ? "1" : "0") + "!";
    }                   
    fstext.WriteFile(sb);
}

void TimerLightModule::Load(){
    String rd = fstext.ReadFile();
    int countQ = gtw.Split(rd, '|', 0).toInt();
    String data = gtw.Split(rd, '|', 1);
    for(int i = 0; i < countQ; i++){
        String str = gtw.Split(data, '!', i);
        TimeLightModuleQ qq = {((byte)gtw.Split(str, ';', 0).toInt()), ((byte)gtw.Split(str, ';', 1).toInt()), ((byte)gtw.Split(str, ';', 2).toInt()), ((byte)gtw.Split(str, ';', 3).toInt()), (gtw.Split(str, ';', 4).toInt()), (gtw.Split(str, ';', 5).toInt() == 1)};
        Qs.add(qq);
    }
    LoadNTP();
}

void TimerLightModule::init(){
    ESP8266WebServer& server1 = gtw.GetServer();
    
    server1.on("/qconfig", [&](){
        String html = ("<head>"+AJAXJs+ChangeTypeJS+"<title>Конфигурация таймеров</title><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><script>function AutoChangeTime(){postAjax('/timemodule', GET, '', function(d){timemod.innerHTML = d;}); window.setTimeout('AutoChangeTime()',1000);} AutoChangeTime();</script></head><body><p>Время на модуле: <span id='timemod'>"+timeClient.getFormattedTime()+"</span></p><p><a href='qsettings'>Настройка системы таймеров</a></p><table><tbody>");
        for(int i = 0; i < Qs.size(); i++){
            TimeLightModuleQ em = Qs.get(i);
            html += (String)"<tr><form action='/setqconfig'><input name='id' type='hidden' value='"+i+"' /><td>Состояние: <input type='checkbox' " + (em.Enable == 1 ? "checked": "") +" name='en' /></td><td>Время: <input value='"+(em.Hour < 10 ? "0" : "")+em.Hour+":"+(em.Minutes < 10 ? "0" : "")+em.Minutes+"' type='time' name='ctime' /></td><td>Пин: <select onload='changepin(this.value, "+i+")' onchange='changepin(this.value, "+i+")' name='pin'>"+GetPinsHTML(em.Pin)+"</select></td><td><span id='valuepin"+i+"'>Значение:</span> <input id='maxpin"+i+"' type='number' maxlength='4' min='"+MinimumBrightnes+"' max='"+MaximumBrightnes+"' name='state' value='"+em.State+"' /> " + "</td><td>В диапазоне: <input type='checkbox' " + (em.IsDynamic ? "checked": "") +" name='isdyn' /></td><td><input type='submit' value='Сохранить' /></td><td><a href='/remove?id="+i+"'>Удалить</a></td></form></tr>";
        }   
        html += ("<tr><td><a href='/addqtimer'>Добавить новый</a></td></tr></tbody></table><br /><a href='/'>Главная</a></body>");
        server1.send(200, "text/html", html);
    });
    server1.on("/setqconfig", [&](){
        int id = server1.arg("id").toInt();
        byte en = server1.arg("en") == "on"; 
        String times = server1.arg("ctime"); 
        byte hour = gtw.Split(times, ':', 0).toInt();
        byte minute = gtw.Split(times, ':', 1).toInt();
        byte pin = server1.arg("pin").toInt();
        int state = server1.arg("state").toInt();
        bool isdyn = server1.arg("isdyn") == "on";
        
        TimeLightModuleQ tm = {hour, minute, en, pin, state, isdyn};
        Qs.set(id, tm);
        Save();
        _running();
        server1.send(200, "text/html", "<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/qconfig' /></head>Таймер №" + (String)id + " сохранен");
    });
    server1.on("/addqtimer", [&](){
        if(Qs.size() >= MaximumTimers){
            server1.send(200, "text/html", "<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/qconfig' /></head>ОШИБКА! Превышено максимальное число таймеров (" + (String)MaximumTimers + ")");
        }
        else{
            TimeLightModuleQ tm = {20, 02, 0, 0, StateOn, false};
            Add(tm);
            server1.send(200, "text/html", "<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/qconfig' /></head>Новый таймер добавлен");
        }
    });
    server1.on("/remove", [&](){       
        int id = server1.arg("id").toInt();
        Qs.remove(id);
        Save();
        server1.send(200, "text/html", "<head><meta charset=\"UTF-8\"><meta http-equiv='refresh' content='1;URL=/qconfig' /></head>Таймер №" + (String)id + " удален");
    });
    server1.on("/saveqsettings", [&](){
        String ntps = server1.arg("ntpserver");
        int utco = server1.arg("utco").toInt()*60*60;
        settings.WriteFile(ntps + ";" + (String)utco);
        LoadNTP();
        server1.send(200, "text/html", "<meta http-equiv='refresh' content='1;URL=/qconfig' />OK");
    });
    server1.on("/qsettings", [&](){
        String tmp = RussianHead("Настройка системы таймеров");
        tmp += (String)"<form action='saveqsettings'><table><tr><td>NTP Сервер:<td><td><input type='text' name='ntpserver' value='"+_NTPServer+"' /></td></tr><tr><td>UTC смещение:<td><td><input type='number' name='utco' value='"+_utcoffset/60/60+"' /></td></tr></table><input type='submit' value='Сохранить' /></form><br /><a href='/'>Главная</a>>><a href='/qconfig'>Таймеры</a>";
        server1.send(200, "text/html", tmp);
    });
    server1.on("/timemodule", [&](){
        server1.send(200, "text/html", timeClient.getFormattedTime());
    });
    
    timeClient.begin();
    Load();
}

void TimerLightModule::Add(TimeLightModuleQ tm){
    Qs.add(tm);
    Save();
}

void TimerLightModule::running(){
    if (timers.IsTick()) {
        _running();
    }
}

void TimerLightModule::_running(){
    timeClient.update();
        for(int i = 0; i < Qs.size(); i++){
            TimeLightModuleQ em = Qs.get(i);
            if(em.Enable){
                if(!em.IsDynamic){
                    if(em.Hour == timeClient.getHours() && em.Minutes == timeClient.getMinutes()){
                        (*light).AddBuferState(em.Pin, em.State);
                    }
                }
                else{
                    if(em.Hour*60+em.Minutes <= timeClient.getHours()*60+timeClient.getMinutes()){
                        (*light).AddBuferState(em.Pin, em.State);
                    }
                }
            }
        }
    (*light).RunBuffer();
}