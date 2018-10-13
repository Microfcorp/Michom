import urllib.request
import sys
import socket

#s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#s.connect(("gmail.com",80))
#print(s.getsockname()[0])
#s.close()

deistv = ""
pin = ""
light = ""
delay = "30"

print ("Запуск...")

if len (sys.argv) > 3:
	if sys.argv[1] == "0":
		deistv = "setlight"
	elif sys.argv[1] == "1":
		deistv = "strobo"
	elif sys.argv[1] == "2":
		deistv = "stroboall"
	pin = sys.argv[2]
	light = sys.argv[3]
elif len (sys.argv) > 4:
	if sys.argv[1] == "0":
		deistv = "setlight"
	elif sys.argv[1] == "1":
		deistv = "strobo"
	elif sys.argv[1] == "2":
		deistv = "stroboall"
	pin = sys.argv[2]
	light = sys.argv[3]
	delay = sys.argv[4]
else:
	exit("Ошибка ключей!")

		
print ("Успешно запущенно")

print ("Определяю адрес шлюза")
gateway = ""

try:
	urllib.request.urlopen('http://192.168.1.42')	
	gateway = "192.168.1.42"
	print ("Адрес шлюза равен 192.168.1.42. API использоваться не будет")
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

print ("")

if gateway == "192.168.1.42":
	print("Посылаю команду напрямую")
	my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p='+pin+"&q="+light+"&d="+delay)
	print("Ответ: " + my_web.read().decode('UTF-8'))
else:
	print("Посылаю команду через шлюз")
	my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p='+pin+"%26q="+light+"%26d="+delay)
	print("Ответ: " + my_web.read().decode('UTF-8'))
print("Завершаю работу")