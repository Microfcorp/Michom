#ifndef FSLoging_h
#define FSLoging_h
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include <FS.h>

#define LogFileName "/logfile.txt"

#ifndef NoFS
class FSLoging
{
        public:
            void AddLogFile(String textadd){
                String rd = ReadLogFile();
                rd += textadd + "<br />";
                WriteLogFile(rd);
            }
            String ReadLogFile(){
                SPIFFS.begin();//инициальзация фс       
                File f = SPIFFS.open(LogFileName, "r");
                if (!f) {
                    Serial.println("file open failed");  //  "открыть файл не удалось"
                    SPIFFS.end();//денициализация фс
                    return "";
                }
                else{
                    String cfg = f.readString();
                    SPIFFS.end();//денициализация фс                        
                    return cfg;
                }    
            }
            void WriteLogFile(String text){
                SPIFFS.begin();//инициальзация фс
                File f = SPIFFS.open(LogFileName, "w");
                if (!f) {
                    Serial.println("file open failed");  //  "открыть файл не удалось"
                    SPIFFS.end();//денициализация фс
                    return;
                }
                else{
                    f.print(text);
                    SPIFFS.end();//денициализация фс                     
                    return;
                }
            }
            void ClearLogFile(){
                WriteLogFile("");
            }
};
#endif 
#endif // #ifndef Michom_h