#ifndef Michom_h
#define Michom_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#define ToCharptr(str) (const_cast<char *>(str.c_str()))
#define ToCharArray(str) ((const char *)str.c_str())
#define BuiltLED 2
#define CountOptionFirmware 5

#define WaitConnectWIFI 30000
#define PasswordAPWIFi "a12345678"

#define DNS_PORT 53

#define WIFIMode WIFI_AP_STA //WIFI_AP_STA

#include "config.h"
#include <ModuleTypes.h>
extern "C" {
#include "user_interface.h"
}
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266SSDP.h>
#include <ESP8266LLMNR.h>
#include <DNSServer.h>
#include <Logger.h>
#include <RTOS.h>
#include <RKeyboard.h>
#include <Hash.h>
#ifndef NoFS
    #include <FS.h>
    #include <FSLoging.h>
    #include <FSFiles.h>
#endif
#include <WebPages.h>
#include <Telnet.h>


typedef struct WIFIConfig
{
    String SSID;
    String Password;
};

class Michome
{
        public:
                #ifdef ADCV
                    ADC_MODE(ADC_VCC);
                #endif
                //Объявление класса
                Michome(){};
                //Объявление класса
                Michome(const char* _ssid, const char* _password, const char* _id, const char* _type, const char* _host, const char* _host1);
                #ifndef NoFS
                //Объявление класса
                    Michome(const char* _id, const char* _type, const char* _host, const char* _host1);
                #endif
                //Отправить GET запрос
                String SendDataGET(String gateway, const char* host, int Port);
                //Отправить POST запрос
				String SendDataPOST(const char* gateway, const char* host, int Port, String Data);
                //Отправить данные на сервер
                void SendData(String Data);
                //Отправить стандартные данные на сервер
                void SendData();
                //Разделение строки по разделителю
                String Split(String data, char separator, int index);
                //Получить настройку с именем
                String GetSetting(String name);
                //Получить числовую настройку с именем
                int GetSettingToInt(String name);
                //Получить все настройки
                String GetSetting();
                //Если Файловая система разрешена
                #ifndef NoFS
                    //Получить SSID и пароль
                    WIFIConfig ReadSSIDAndPassword();
                    //Записать SSID и пароль
                    void WriteSSIDAndPassword(String ssid, String password);
                    //Записать SSID и пароль
                    void WriteSSIDAndPassword(String txt);
                #endif
                //Получить класс логгера
                Logger GetLogger();
                //Инициализация модуля с отправкой данных
                void init(bool senddata);
                //Инициализация модуля
                void init();
                //Основной цикл
                void running(void);
                //Выполнение все критических операций
                void yieldM(void);
				//Выполнение стековых операций
                void yieldWarn(void);				
                //Моргнуть светодиодом на плате
                void StrobeBuildLed(byte timeout);
                //Моргнуть светодиодом на плате информацию об ошибки
                void StrobeBuildLedError(int counterror, int statusled);
                //Получить WEB сервер
                ESP8266WebServer& GetServer();
                //Парсинг JSON данных
                String ParseJson(String type, String data); 
                //Установить формат настроек
                void SetFormatSettings(int count);
                //Считать ли настройки
                bool GetSettingRead();
				//Задает опцию прошивки
                void SetOptionFirmware(byte id, bool value){
					//if(id < 0 || id > CountOptionFirmware) return;
					OptionsFirmware[id] = value;
				}
				//Получает опцию прошивки
                bool GetOptionFirmware(byte id){
					//if(id < 0 || id > CountOptionFirmware) return false;
					return OptionsFirmware[id];
				}
                //Получены ли настройки
                bool IsSettingRead;
                //Таймаут сервера
                int TimeoutConnection = 5000;
                //Стандартное значение при поиске настройки
                int DefaultSettingInt = 1;
                //Отконфигурирован ди модуль
                bool IsConfigured = false;
                //Получает информацию о модуле по коду num
                String GetModule(byte num);
                //Время работы модуля
                long GetRunningTime(){return millis();};
                //Моргать при обновении прошивки через OTA
                bool IsBlinkOTA = true;
                //Если FS разрешена
                #ifndef NoFS
                    //Объект логов файловой системы
                    FSLoging FSLoger;                    
                #endif
                #if defined(WriteDataToFile) && !defined(NoFS)
                    //Объект логов данных
                    FSFiles DataFile(){return FSFiles("/datalog.txt");};
                #endif
        private:
            char ssid[WL_SSID_MAX_LENGTH]; 
            char password[WL_WPA_KEY_MAX_LENGTH];
            DNSServer dnsServer;
            const char* id; const char* type; const char* host; const char* host1;           
            MDNSResponder mdns;
            void _init(void);
            String settings;  
            int countsetting = 1;
            void CreateAP();
            bool IsReadConfig = false;
            long wifi_check;
			//Установить режим работы WIFI
			void ChangeWiFiMode(void);
			String GetMainWeb(void);
			bool OptionsFirmware[CountOptionFirmware]; //Модуль освещения - Модуль времени - UPD тригеры
};
#endif // #ifndef Michom_h