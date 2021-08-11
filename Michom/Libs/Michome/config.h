#ifndef config_h
#define config_h

#define NoCheckWIFI //Отключить проверку WIFI соеденения
#define DebugConnection //Выводить в консоль к кому подключаться
#define NoAutoReconect //Отключить автоматический реконект
#define WriteDataToFile //Записывать все данные в отдельный файл
//#define ADCV //Включить измерение напряжения
#define NoAddLogSendData //Не записываль в лог о том, что передаем информацию
#define NoDataAddLogSendData //Не записывать в лог передаваемую информацию
#define TimeSending //Записывать в лог время передачи данных
//#define UsingWDT //Использовать сторожевой таймер
//#define NoScanWIFi //Не сканировать сети в конфигураторе
#define StartLED //Светить светодиодам при запуске
#define UsingFastStart //Использовать быструю загрузку - не отключаться от сети при перезапуске

#endif