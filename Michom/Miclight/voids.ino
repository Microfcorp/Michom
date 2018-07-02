String parsejson(String type, String data){
  String temp = "";
  temp += "{";
  temp += "\"ip\": \"" + WiFi.localIP().toString() + "\",";
  temp += "\"type\":";
  temp += "\"" + type + "\",";
  if(type == "get_light_status"){    
  temp += "\"data\": {";
  temp += "\"status\": \"" + data + "\" } } \r\n";
  }
  return temp; 
}

