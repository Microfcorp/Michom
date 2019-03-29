# Smart Home Michom
Michome is the system smart home. It consists of modules. Each module works independently from other modules. In this repository you will find both the operating system via the gateway and via the computer. 

Description of folders: 

#### WindowsFormApplication1 - Console for windows. 

#### Michom - the firmware for the modules. 

#### Michomeclient - program to work through a gateway and framework 

#### Gateway - scripts gateway 

#### MichomeAndroidGateway - application for Android with Apache Cordova

#### Michomeframework - framework to work through the gateway 

#### PythonModule - scripts to work through a gateway

<br>

Description of the library/framework (only through a gateway): 
```C#
michomeframework.Gateway gtw = new michomeframework.Gateway(); //initialization of an object 

michomeframework.Gateway gtw = new michomeframework.Gateway(string ip); //initialization of an object as URI

gtw.Connect(string ip); //connect to the gateway by ip address (***.***.***.***); 

gtw.Disconnect(); //disconnect from the gateway 

(String)gtw.Getdata(string device_ip, string type); //returns a string of data in json format. 'type' - type of requested data 

(String)gtw.Setdata(string device, string data); //Send data to the device

(String)michomeframework.Gateway.Setdata(string device, string data); //Send data to the device

(Image)gtw.Getimage(string type, int start, int count); //receive schedule changes(temper, humm, dawlen) 

(NameAndId)gtw.Getdevices(); //get the info of all modules 
```
