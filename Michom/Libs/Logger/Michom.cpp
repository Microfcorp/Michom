#include "Michom.h"

//
// конструктор - вызывается всегда при создании экземпляра класса RoboCraft
//
Michome::Michome()
{

}

//
// просто говорим "Hello" :)
//
String Michome::SendDataGET(String gateway, const char* host, int Port)
{
          Serial.print("connecting to ");
		  Serial.println(host);
  
		  // Use WiFiClient class to create TCP connections
		  WiFiClient client;
		  const int httpPort = Port;
		  if (!client.connect(host, httpPort)) {
			Serial.println("connection failed");
			return "connection failed";
		  }		

		  
		  // This will send the request to the server
		  client.print(String("GET ") + (String)gateway + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
		  unsigned long timeout = millis();
		  while (client.available() == 0) {
			if (millis() - timeout > 5000) {
			  Serial.println(">>> Client Timeout !");
			  client.stop();
			  return ">>> Client Timeout !";
			}
		  }
		  delay(1000);
		  String r = "";
		  // Read all the lines of the reply from server and print them to Serial
		  while(client.available()){
			String line = client.readStringUntil('\r');
			r += line + "<br />";
		  }
		  
		  return r;
}
String Michome::SendDataPOST(const char* gateway, const char* host, int Port, String Data)
{
          Serial.print("connecting to ");
		  Serial.println(host);
  
		  // Use WiFiClient class to create TCP connections
		  WiFiClient client;
		  const int httpPort = Port;
		  if (!client.connect(host, httpPort)) {
			Serial.println("connection failed");
			return "connection failed";
		  }
		  
		  String dataaaa = Data;

		  Serial.print("Data: ");
		  Serial.println(dataaaa);

		  String lengt = (String)dataaaa.length(); 
		  
		  // This will send the request to the server
		  client.print(String("POST ") + "http://" + (String)gateway + " HTTP/1.1\r\n" +
					   "Host: " + (String)host + "\r\n" + 
					   "Content-Length: " + lengt + "\r\n" +
					   "Content-Type: application/x-www-form-urlencoded \r\n" +
					   "Connection: close\r\n\r\n" +
					   dataaaa);
		  unsigned long timeout = millis();
		  while (client.available() == 0) {
			if (millis() - timeout > 5000) {
			  Serial.println(">>> Client Timeout !");
			  client.stop();
			  return ">>> Client Timeout !";
			}
		  }
		  delay(1000);
		  String r = "";
		  // Read all the lines of the reply from server and print them to Serial
		  while(client.available()){
			String line = client.readStringUntil('\r');
			r += line + "<br />";
		  }
		  
		  return r;
}