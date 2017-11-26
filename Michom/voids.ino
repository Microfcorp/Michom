String parsejson(String type, String data){
  String temp = "";
  temp += "{";
  temp += "\"ip\": \"" + WiFi.localIP().toString() + "\",";
  temp += "\"type\":";
  temp += "\"" + type + "\",";
  if(type == "DHT"){    
  temp += "\"data\": {";
  temp += "\"temper\": \"" + String(dht.readTemperature()) + "\",";
  temp += "\"humm\": \"" + String(dht.readHumidity()) + "\"";
  temp += "}";
  }
  temp += "}"; 
  return temp; 
}




