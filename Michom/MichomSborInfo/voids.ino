String parsejson(String type, String data){
  String temp = "";
  temp += "{";
  temp += "\"ip\": \"" + WiFi.localIP().toString() + "\",";
  temp += "\"type\":";
  temp += "\"" + type + "\",";
  if(type == "msinfoo"){    
  temp += "\"data\": {";
  temp += "\"davlen\": \"" + String(bmp.readPressure()/133.3) + "\",";
  temp += "\"temperbmp\": \"" + String(bmp.readTemperature()) + "\",";
  temp += "\"visot\": \"" + String(bmp.readAltitude()) + "\",";
  temp += "\"temper\": \"" + String(dht.readTemperature()) + "\",";
  temp += "\"humm\": \"" + String(dht.readHumidity()) + "\" } } \r\n";
  }
  return temp; 
}

