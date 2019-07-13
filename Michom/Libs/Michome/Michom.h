#ifndef Michom_h
#define Michom_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266SSDP.h>
#include <Logger.h>
#include <RTOS.h>

class Michome
{
        public:
                //Объявление класса
                Michome(const char* _ssid, const char* _password, const char* _id, const char* _type, const char* _host, const char* _host1);
                //Отправить GET запрос
                String SendDataGET(String gateway, const char* host, int Port);
                //Отправить POST запрос
				String SendDataPOST(const char* gateway, const char* host, int Port, String Data);
                //Отправить данные на сервер
                String SendData(String Data);
                //Отправить стандартные данные на сервер
                String SendData();
                //Разделение строки по разделителю
                String Split(String data, char separator, int index);
                //Получить настройку с именем
                String GetSetting(String name);
                //Получить все настройки
                String GetSetting();
                //Получить класс логгера
                Logger GetLogger();
                //Инициализация модуля с отправкой данных
                void init(bool senddata);
                //Инициализация модуля
                void init();
                //Основной цикл
                void running(void);
                //Получить WEB сервер
                ESP8266WebServer& GetServer();
                //Парсинг JSON данных
                String ParseJson(String type, String data); 
                //Установить формат настроек
                void SetFormatSettings(int count);
                //Считать ли настройки
                bool GetSettingRead();
                //Получены ли настройки
                bool IsSettingRead;
        private:
            const char* ssid; const char* password; const char* id; const char* type; const char* host; const char* host1;
            MDNSResponder mdns;
            void _init(void);
            String settings;  
            int countsetting = 1;
};
#endif // #ifndef Michom_h