import urllib.request
import sys
import json
import time

path = ""

print ("Запуск...")

if len (sys.argv) > 1:
	path = sys.argv[1]
	print ("Успешно запущенно")
else:
	exit("Ошибка ключей!")
	

def Send(deistv, pin, light, delay):
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		#exit('http://192.168.1.34/'+deistv+'?p='+pin+"&q="+light+"&d="+delay)
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p='+pin+"&q="+light+"&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p='+pin+"%26q="+light+"%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	
	
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

print ("")

handle = open(path, "r")
data = handle.read()

jsonDate = json.loads(data)

print("Начинаю выполнение сценария "+jsonDate['name'])

for val in jsonDate['params']:
	if val['name'] == "sleep":
		print("Начинаю выполнять команду "+val['name'])
		time.sleep(int(val['time']))
	elif val['name'] == "setlight":
		print("Начинаю выполнять команду "+val['name'])
		Send(deistv='setlight', pin=val['pin'], light=val['brightness'], delay="")
	elif val['name'] == "strobo":
		print("Начинаю выполнять команду "+val['name'])
		Send(deistv='strobo', pin=val['pin'], light=val['col'], delay=val['times'])
	elif val['name'] == "stroboall":
		print("Начинаю выполнять команду "+val['name'])
		Send(deistv='stroboall', pin=val['col'], light=val['times'], delay='')


print("Завершаю работу")