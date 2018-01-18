String parsejson(String type, String data){
  String temp = "";
  temp += "{";
  temp += "\"ip\": \"" + WiFi.localIP().toString() + "\",";
  temp += "\"type\":";
  temp += "\"" + type + "\",";
  if(type == "msinfoo"){    
  temp += "\"data\": {";
  temp += "\"davlen\": \"NOT CONNECTED\",";
  temp += "\"temper\": \"" + String(dht.readTemperature()) + "\",";
  temp += "\"humm\": \"" + String(dht.readHumidity()) + "\" } } \r\n";
  }
  return temp; 
}

