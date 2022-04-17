#ifndef TimeSystem_h
#define TimeSystem_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
//#include <NTPClient.h>

//#define UTC3 10800 //Utc+3
//#define NTPServer "pool.ntp.org"
//#define NTPServerMaxLenght 50
//#define NTPTimer 60000

class TimeSystem
{
        public:
                //Объявление класса
                TimeSystem(long startm){
					StartM = startm;
				}
				long DifTime(){
					return StartM - millis();
				}
        private:                       
            long StartM;
            //long CurM;
};
#endif // #ifndef TimeSystem_h