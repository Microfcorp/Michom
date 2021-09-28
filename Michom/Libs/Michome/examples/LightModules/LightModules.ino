#include <Michom.h>
#include <LightModules.h>
#include <TimerLightModule.h>
#include <MichomUDP.h>

const char* id = "LightStudio_Elka";
const char* type = StudioLight; //стандартный тип модуля освещения
/////////настройки//////////////

const char* host = "192.168.1.42/michome/getpost.php";
const char* host1 = "192.168.1.42";

RTOS rtos(604000); //время опроса до сервера

Michome michome(id, type, host, host1); //инициальзация модуля Michome
LightModules lm (michome); //Инициализация модуля освещения
TimerLightModule tlm(&lm); //Инициализация подсистемы точного времени

ESP8266WebServer& server1 = michome.GetServer(); //Получение объекта веб-сервера

MichomeUDP MUDP(michome); //Создание класса UDP кнотроллера

//const int Keys[] = {9,10,4,5};

void setup ( void ) {
  lm.AddPin({4, Relay}); //Дабавить пин 4 с типом Реле 
  lm.AddPin({5, PWM}); //Дабавить пин 5 с типом PWM 
  
  lm.TelnetEnable = true; //Включена поддержка telnet запросов
  lm.SaveState = true; //Включено сохранение статуса выводов при перезапуске
  lm.init(); //Инициализация модуля освещения
  tlm.init(); //Инициализация подсистемы времени
  michome.init(true); //Инициализация модуля Michome
  michome.TimeoutConnection = LightModuleTimeoutConnection; //Таймаут соединения до шлюза
  
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
    if (michome.GetSetting("logging") == "1")
      rtos.Start();
    else
      rtos.Stop();
  }

  if (rtos.IsTick()) {
    michome.SendData();
  } 
}
