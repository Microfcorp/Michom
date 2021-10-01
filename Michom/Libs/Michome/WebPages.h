#ifndef WebPages_h
#define WebPages_h
    static const String XNR = " function createXMLHttp() {if (typeof XMLHttpRequest != \"undefined\") {return new XMLHttpRequest();} else if (window.ActiveXObject) { var aVersions = [\"MSXML2.XMLHttp.5.0\",\"MSXML2.XMLHttp.4.0\",\"MSXML2.XMLHttp.3.0\",\"MSXML2.XMLHttp\",\"Microsoft.XMLHttp\"];for (var i = 0; i < aVersions.length; i++) {try {var oXmlHttp = new ActiveXObject(aVersions[i]);return oXmlHttp;} catch (oError) {}}throw new Error(\"Невозможно создать объект XMLHttp.\");}}; ";
    static const String AJAXJs = "<script>var GET = 'GET'; var POST = 'POST'; var HEAD = 'HEAD'; "+XNR+" function postAjax(url, type, data, callback) { var oXmlHttp = createXMLHttp();var sBody = data;oXmlHttp.open(type, url, true);oXmlHttp.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");oXmlHttp.onreadystatechange = function() {if (oXmlHttp.readyState == 4) {callback(oXmlHttp.responseText);}};oXmlHttp.send(sBody);}</script>";
    static const String ChangeTypeJS = "<script>var isrel = false; function changepin(id, iq){postAjax('/getpins', GET, '', function(d){var lines = d.split('<br />'); for(var i = 0; i < lines.length; i++){var ids = parseInt(lines[i][0]); if(ids == id){if(lines[i].split('-')[1].substring(1).trim() == 'Relay'){document.getElementById('valuepin'+iq).innerHTML = 'Значение'+(isrel ? '(Релейный)' : '(PWM)')+':';}}}})}</script>";
	    //static const String ChangeTypeJS = isrelayJS + "<script>function changepin(id, i){isrelay(id); document.getElementById('valuepin'+i).innerHTML = 'Значение'+(isrel ? '(Релейный)' : '(PWM)')+':';}</script>";
    static String RussianHead(String title){
        return ("<head><title>"+title+"</title><meta charset=\"UTF-8\"></head>");
    }
	static String GetColorRssi(int rssi){
        if(rssi >= -50) return F("green");
        else if(rssi >= -65) return F("lightgreen");
        else if(rssi >= -75) return F("yellow");
        else if(rssi >= -85) return F("darkred");
        else if(rssi >= -100) return F("gray");
    }
	static String SVGRSSI(int rssi){
		String tmp = F("<?xml version=\"1.0\" ?> <svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" style=\"width: 32px; height: 16px;\"> <g>");
		if(rssi >= -100) tmp += F("<rect x=\"1.775\" y=\"13.16\" width=\"4.131\" height=\"14.312\"/>"); //первая палочка
		if(rssi >= -85) tmp += F("<rect x=\"8.648\" y=\"9.895\" width=\"4.13\" height=\"17.578\"/>"); //вторая
		if(rssi >= -75) tmp += F("<rect x=\"15.133\" y=\"5.188\" width=\"4.129\" height=\"22.285\"/>"); //третья
		if(rssi >= -65) tmp += F("<rect x=\"21.567\" y=\"0\" width=\"4.13\" height=\"27.473\"/>"); //четвертая
		tmp += F("</g></svg>");
		return tmp;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
    static String WebConfigurator(String SSID, String Password, String Gateway, bool UseGetaway){
        String div = RussianHead("Сетевые настройки модуля");
        #ifndef NoScanWIFi
		  div += "<h3>Доступные WIFI сети</h3>";
          int n = WiFi.scanNetworks();
          if(n != 0)
          {
            for (int i = 0; i < n; ++i)
            {
              div += "<p>";
              div += "<a href=\"#\" onclick=\"Change('"+String(WiFi.SSID(i))+"'); return false;\">"+String(WiFi.SSID(i))+""+SVGRSSI(WiFi.RSSI(i))+"</a>";
              div += "</p>";              
            }
          }  
        #endif
        return ("<!Doctype html><html><head><title>Конфигурация модуля</title><meta charset=\"UTF-8\"><script>function Change(d){ssid.value = d;}</script></head><body><div>"+div+"<div><br /><form action=\"/setconfig\" method=\"get\"><p>SSID: <input type=\"text\" value=\""+SSID+"\" id=\"ssid\" name=\"ssid\"></p><p>Пароль: <input value=\""+Password+"\" type=\"text\" name=\"password\"></p><p>Адрес шлюза: <input type=\"text\" value=\""+Gateway+"\" name=\"geteway\"></p><p>Использовать шлюз: <input type=\"checkbox\" "+(UseGetaway ? "checked" : "")+" name=\"usegetaway\"></p><p><input type=\"submit\" value=\"Сохранить и перезагрузить\"></p></form></body></html>");
    }
    static String WebMain(String type, String id, bool IsTimers, bool IsUDP, bool SendGetaway){
        int rssi = WiFi.RSSI();
        
        return (("<html> <meta http-equiv='refresh' content='60;URL=/' /> <title> ")+WiFi.localIP().toString()+(" - Общая информация</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><div style='background: linear-gradient(45deg, #10ebf3, #87c7ff);'><p>Тип модуля: <span style='color: red;'>")+type+("</span></p><p>ID модуля: <span style='color: red;'>")+id+("</span></p></div><div><p>Время работы: <span style='color: red;'>")+ (String)(millis()/1000/60/60)+" часов "+(String)(millis()/1000/60)+" минут "+(String)(millis()/1000)+" секунд</span></p></div><div style='background: linear-gradient(45deg, #10ebf3, #87c7ff);'><p>"+(WiFi.status() != WL_CONNECTED ? "Ошибка подключения к" : "Подключен к сети:")+" <span style='color: red;'>"+(String)WiFi.SSID()+("</span></p><p>Уровень сигнала: <span style='color: ")+GetColorRssi(rssi)+(";'>")+(String)rssi+(" dBm</span> "+SVGRSSI(rssi)+"</p></div>")
        + "<div><p><a href='/configurator'>Настройки модуля</a></p>"
        + "<div><p><a href='/getlogs'>Системные логи</a></p>"
		#ifdef WriteDataToFile
			+ (SendGetaway ? "<div><p><a href='/getdatalogs'>Журнал передаваемых на шлюз данных</a></p>" : "")
		#endif
        + (type == StudioLight ? String("<p><a href='/getpins'>Просмотреть доступные выводы</a></p><p><a href='/remotepins'>Управление выводами</a></p>") : "")
        + (IsTimers ? String("<p><a href='/qconfig'>Конфигурация таймеров</a></p>") : "")
        + (IsUDP ? String("<p><a href='/udptrigger?type=show'>Конфигурация UDP триггеров</a></p>") : "")
        + (type == Termometr ? String("<p><a href='/gettemp'>Посмотреть температуру</a></p>") : "")
        + String("</div></html>")); 
    }
#endif // #ifndef WebPages_h