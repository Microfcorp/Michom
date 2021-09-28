#include <Michom.h>
#include <LightModules.h>
#include <TimerLightModule.h>
#include <MichomUDP.h>
#include <GyverButton.h>

#define ButtonPin 10

const char* id = "LightStudio_Workstation";
const char* type = StudioLight; //стандартный тип модуля освещения
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

RTOS rtos(604000); //время опроса до сервера

Michome michome(id, type, host, host1); //инициальзация модуля Michome
LightModules lm (michome); //Инициализация модуля освещения
TimerLightModule tlm(&lm); //Инициализация подсистемы точного времени

ESP8266WebServer& server1 = michome.GetServer(); //Получение объекта веб-сервера

MichomeUDP MUDP(michome); //Созлдание класса UDP кнотроллера

GButton butt1(ButtonPin); //Класс кнопки
byte clicks = 0; //Количетво нажатий

void setup ( void ) {
  lm.AddPin({14, PWM}); //Дабавить пин 5 с типом PWM 
  
  lm.TelnetEnable = true; //Включена поддержка telnet запросов
  lm.SaveState = true; //Включено сохранение статуса выводов при перезапуске
  lm.init(); //Инициализация модуля освещения
  tlm.init(); //Инициализация подсистемы времени
  michome.init(true); //Инициализация модуля Michome
  michome.TimeoutConnection = LightModuleTimeoutConnection; //Таймаут соединения до шлюза
  michome.SetOptionFirmware(1, true);
  michome.SetOptionFirmware(2, true);
  
  MUDP.lightModules = &lm; //Ссылка на объект модуля освещения
  MUDP.timerLightModules = &tlm; //Ссылка на объект подсисетмы времени
  MUDP.EAlarm = true; //Включено событие EAlarm
  MUDP.init(); //Инициализация модуля UDP
  
  server1.on("/refresh", [](){ 
    server1.send(200, "text/html", "OK");
    michome.SendData();
  });
}

void loop ( void ) {
  michome.running(); //Цикличная функция работы
  lm.running(); //Цикличная функция работы
  tlm.running(); //Цикличная функция работы
  MUDP.running(); //Цикличная функция работы

  if (michome.GetSettingRead()) {
    rtos.ChangeTime(michome.GetSettingToInt("update"));
    butt1.setClickTimeout(michome.GetSettingToInt("clicktimeout"));
    if (michome.GetSetting("logging") == "1")
      rtos.Start();
    else
      rtos.Stop();
  }

  if (rtos.IsTick()) {
    michome.SendData();
  } 

  butt1.tick();

  if (butt1.hasClicks()){clicks = butt1.getClicks(); Serial.println("Clicks="+String(clicks));}
  else clicks = 0;
 
  if (clicks == 2) {
    lm.SetLightID(0, MinimumBrightnes);
  }
  else if (clicks == 1) {
    lm.SetLightID(0, MaximumBrightnes);
  }
  if(clicks != 0 && clicks != 1 && clicks != 2) michome.SendData(michome.ParseJson("get_button_press", String(ButtonPin)+"="+String(clicks)));
}
