import urllib.request
import sys
import socket
		
print ("Успешно запущенно")

print ("Определяю адрес шлюза")

gateway = ""
device = ""
cmd = ""

try:
	urllib.request.urlopen('http://192.168.1.42')	
	gateway = "192.168.1.42"
	print ("Адрес шлюза равен 192.168.1.42. API будет использоваться")
except:
	gateway = "91.202.27.167"
	print ("Адрес шлюза равен 91.202.27.167. API будет использоваться")
	
print ("Адрес шлюза успешно определён")
#print ("")
#print ("Начинаю авторизацию")
#login = b'Lexap'
#password = b'Mart2005'
#mydata = b'login='+login+b'&password='+password
#
#my_req = urllib.request.Request('http://'+gateway+'/site/secur.php', data=mydata,method='POST')
#my_form = urllib.request.urlopen(my_req)
#req = my_form.read().decode('UTF-8')
#
#if req == "OK":
#	print("Авторизовался успешно. Продолжаю")
#else:
#	exit("Авторизация неудачна")	

def send():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.42/michome/api/setcmd.php?device='+device+'&cmd='+cmd)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://192.168.1.42/michome/api/setcmd.php?device='+device+'&cmd='+cmd)
		print("Ответ: " + my_web.read().decode('UTF-8'))

print ("")

a = ""
while a != "exit":
	a = input("Введите адрес устройства и комманду:")
	if a != "exit":
		device = a.split(' ')[0]
		cmd = a.split(' ')[1]
		send()		
		
print("Завершаю работу")