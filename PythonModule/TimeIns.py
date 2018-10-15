import urllib.request
import sys

#s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#s.connect(("gmail.com",80))
#print(s.getsockname()[0])
#s.close()

device = ""
cmd = ""
date = ""

print ("Запуск...")

if len (sys.argv) > 3:
	device = sys.argv[2]
	cmd = sys.argv[1]
	date = sys.argv[3]
	print ("Успешно запущенно")
elif len (sys.argv) > 2:
	device = sys.argv[2]
	cmd = sys.argv[1]		
	print ("Успешно запущенно")
elif len (sys.argv) > 1:
	cmd = sys.argv[1]	
	print ("Успешно запущенно")
else:
	exit("Ошибка ключей!")

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
	my_web = urllib.request.urlopen('http://192.168.1.42/michome/api/timeins.php?type='+cmd+'&device='+device+"&date="+date)
	req = my_web.read().decode('UTF-8')
else:
	print("Посылаю команду через шлюз")
	my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/timeins.php?type='+cmd+'&device='+device+"&date="+date)
	req = my_web.read().decode('UTF-8')
	
if cmd == "oneday":
	print(req)
else:
	print("С "+req.split(';')[0]+" По "+req.split(';')[1]+" Количество "+req.split(';')[2]);


print("Завершаю работу")