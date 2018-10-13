import urllib.request
import sys
import json
import socket

#s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#s.connect(("gmail.com",80))
#print(s.getsockname()[0])
#s.close()

device = ""
cmd = ""

print ("Успешно запущенно")

print ("Определяю адрес шлюза")
gateway = ""

try:
	urllib.request.urlopen('http://192.168.1.42')	
	gateway = "192.168.1.42"
	print ("Адрес шлюза равен 192.168.1.42. API будет использоваться")
except:
	gateway = "91.202.27.167"
	print ("Адрес шлюза равен 91.202.27.167. API будет использоваться")
	
print ("Адрес шлюза успешно определён")

print ("")

req = ""

if gateway == "192.168.1.42":
	print("Посылаю команду напрямую")
	my_web = urllib.request.urlopen('http://192.168.1.42/michome/api/getdevice.php')
	req = my_web.read().decode('UTF-8')
else:
	print("Посылаю команду через шлюз")
	my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/getdevice.php')
	req = my_web.read().decode('UTF-8')
	
jsonDate = json.loads(req)

i = 0

for val in jsonDate['ips']:
	print(jsonDate['ips'][i] + " as " + jsonDate['devicename'][i] + " as " + jsonDate['devicetype'][i])
	i = i + 1

print("Завершаю работу")