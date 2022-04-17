#ifndef InformetrModules_h
#define InformetrModules_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#define InformetrModuleTimeoutConnection 3000
#define DaysMaximum 6
#define PathToPrognoz "/michome/api/getprognoz.php?type=json"

#include <Michom.h>
#include <LinkedList.h>
#include <ArduinoJson.h>
//#ifdef IsLCDI2C
	#include <LiquidCrystal_I2C.h>
	#include <Wire.h>
	#include <lcd/symbols_inf.h>
//#endif

typedef enum SymbolsBank { BIndoor, BOutDoor, Day };
typedef struct LCDData
{	
    char DayTemp[6]; //Дневная температура
    char NightTemp[6]; //Ночная температура
    char Wind[6]; //Скорость ветра
	char Press[6]; //Давление
	char ToDate[16]; //На дату
	byte IconDay; //Иконка
	byte IconNight; //Иконка
};
typedef struct LCDDataPrint //для вывода на дисплей
{
    SymbolsBank Symbols; //Банк с иконками
    //byte IconsLine[2]; //Иконки по строкам
    LCDData Data; //Погодгые данные
};


typedef struct IndoorData
{		
    LCDData Data;
};

typedef struct OutdoorData
{
    LCDData Data[DaysMaximum];
};

typedef struct ServerData //для хранения с сервера в ram
{
    IndoorData Indoor; //Домашние данные
    OutdoorData Outdoor; //Интернет данные
    String ServerTime; //Серверное время
    bool LightEnable; //Управление подсветкой
};


class InformetrModule
{
        public:
                //Объявление класса
                InformetrModule(Michome *m);
                InformetrModule(){};
				//#ifdef IsLCDI2C
					void SetDisplaySize(byte adress, byte x, byte y);					
				//#endif
				void init();
				void running();
				void startUpdate();
				void printLCD(LCDDataPrint dt);
				bool BacklightEnable = false; //Включение подстветки
				bool PokazType = true; //тип экрана (прогноз (сменный)) или домашний (статичный)
				void InversePokazType(){PokazType =! PokazType; if(!PokazType) i1(); else i2();}
				bool pause = false; // пауза обновления и отображения				
				bool IsAutoUpdate = true; //автоматически обновлять данные по таймеру		
                
        private:
            Michome *gtw;
			RTOS rtos = RTOS(600000);//Запрос данных
			
			RTOS rtos1 = RTOS(10000);//Время переключения экранов
			RTOS rtos2 = RTOS(8200);//Врея показа дня
			
			RTOS LightOff = RTOS(600000);//Время до отключения подсветки
			RTOS UpdateLight = RTOS(30);//Включение подсветки
			long pogr = 1800; //Отсчет до времени показа дня
			bool EtherFail = false; //Ошибка интернета
			long Attempted = 0; //попытка соеденения						
			bool IsRunLight = false; //Принудительное включение подсветки
			bool IsReadData = false; //Данные были прочитаны
			byte displayH, displayW;
			
			ServerData Server;
			void parse(String datareads);
			void printpause();
			void i1();
			void i2();
			void nodat();
			void PrintETError();
			bool st = true;
			byte day = 0;
			byte maxday = 0;
			void plusday() {
				day++;
				if (day > maxday-1) 
					day = 0;
			}
			
			//#ifdef IsLCDI2C
				void ChangeLight(){
					if(BacklightEnable || IsRunLight || Server.LightEnable)
						lcd.backlight();
					else lcd.noBacklight(); //Выключаем свет
				}
				void ToHomes(){
				  lcd.createChar(0, homes);
				  lcd.createChar(1, watchh);
				  lcd.createChar(2, groza);
				  lcd.createChar(3, soln);
				  lcd.createChar(4, sneg);
				  lcd.createChar(5, gradus);
				}

				void ToPrognoz(){
				  lcd.createChar(0, Dozd);
				  lcd.createChar(1, oblazn);
				  lcd.createChar(2, groza);
				  lcd.createChar(3, soln);
				  lcd.createChar(4, sneg);
				  lcd.createChar(5, gradus);
				}
				LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
			//#endif
            
};
#endif // #ifndef InformetrModules_h