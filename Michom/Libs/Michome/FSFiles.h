#ifndef FSFiles_h
#define FSFiles_h
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include <FS.h>

#ifndef NoFS
class FSFiles
{
        public:
            FSFiles(String path){
                FilePath = path;
            }
            
            void AddTextToFile(String textadd){
                String rd = ReadFile();
                rd += textadd + "<br />";
                WriteFile(rd);
            }
            String ReadFile(){
                SPIFFS.begin();//инициальзация фс       
                File f = SPIFFS.open(FilePath, "r");
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
            void WriteFile(String text){
                SPIFFS.begin();//инициальзация фс
                File f = SPIFFS.open(FilePath, "w");
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
            void ClearFile(){
                WriteFile("");
            }
        private:
            String FilePath = "/file.txt";
};
#endif 
#endif // #ifndef Michom_h