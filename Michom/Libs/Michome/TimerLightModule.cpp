#include "TimerLightModule.h"

TimerLightModule::TimerLightModule(LightModules *m){
    light = m;
    gtw = &(*light).GetMichome();
	(*gtw).SetOptionFirmware(TimerLightModules, true);
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
    int countQ = (*gtw).Split(rd, '|', 0).toInt();
    String data = (*gtw).Split(rd, '|', 1);
    for(int i = 0; i < countQ; i++){
        String str = (*gtw).Split(data, '!', i);
        TimeLightModuleQ qq = {((byte)(*gtw).Split(str, ';', 0).toInt()), ((byte)(*gtw).Split(str, ';', 1).toInt()), ((byte)(*gtw).Split(str, ';', 2).toInt()), ((byte)(*gtw).Split(str, ';', 3).toInt()), ((*gtw).Split(str, ';', 4).toInt()), ((*gtw).Split(str, ';', 5).toInt() == 1)};
        Qs.add(qq);
    }    
}

void TimerLightModule::init(){
	(*gtw).preInit();
    ESP8266WebServer& server1 = (*gtw).GetServer();
    
    server1.on("/qconfig", [&](){
        String html = ("<head>"+AJAXJs+ChangeTypeJS+"<title>Конфигурация таймеров</title><meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"+AutoChangeTime+"</head><body><p>Время на модуле: <span id='timemod'>"+(*gtw).GetFormattedTime()+"</span><br /><a href='qsettings'>Настройка системы таймеров</a></p><table><tbody>");
        html += F("<span><em>Обрабите внимание, что время таймера должно увеличиваться</em></span>");
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
        byte hour = (*gtw).Split(times, ':', 0).toInt();
        byte minute = (*gtw).Split(times, ':', 1).toInt();
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
            TimeLightModuleQ tm = {20, 02, 0, 0, MaximumBrightnes, false};
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
        for(int i = 0; i < Qs.size(); i++){
            TimeLightModuleQ em = Qs.get(i);
            if(em.Enable){
                if(!em.IsDynamic){
                    if(em.Hour == (*gtw).GetHours() && em.Minutes == (*gtw).GetMinutes()){
                        (*light).AddBuferState(em.Pin, em.State);
                    }
                }
                else{
                    if(em.Hour*60+em.Minutes <= (*gtw).GetHours()*60+(*gtw).GetMinutes()){
                        (*light).AddBuferState(em.Pin, em.State);
                    }
                }
            }
        }
    (*light).RunBuffer();
}