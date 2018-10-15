import urllib.request
import sys
import socket
from tkinter import *
 
print ("Успешно запущенно")

gateway = ""
deistv = "setlight"
pin = "0"
light = "1023"
delay = "50"

print ("Определяю адрес шлюза")
try:
	urllib.request.urlopen('http://192.168.1.42')	
	gateway = "192.168.1.42"
	print ("Адрес шлюза равен 192.168.1.42. API использоваться не будет")
except:
	gateway = "91.202.27.167"
	print ("Адрес шлюза равен 91.202.27.167. API будет использоваться")
	
print ("Адрес шлюза успешно определён")

def send1on():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p='+pin+"&q=1023&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p='+pin+"%26q=1023%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
		
def send1off():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p='+pin+"&q=0&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p='+pin+"%26q=0%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
def send2on():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+"?p=1&q=1023&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p=1'+"%26q=1023%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
		
def send2off():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p=1'+"&q=0&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p=1'+"%26q=0%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
def send3on():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p=2'+"&q=1023&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p=2'+"%26q=1023%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
		
def send3off():
	if gateway == "192.168.1.42":
		print("Посылаю команду напрямую")
		my_web = urllib.request.urlopen('http://192.168.1.34/'+deistv+'?p=2'+"&q=0&d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))
	else:
		print("Посылаю команду через шлюз")
		my_web = urllib.request.urlopen('http://91.202.27.167/michome/api/setcmd.php?device=192.168.1.34&cmd='+deistv+'?p=2'+"%26q=0%26d="+delay)
		print("Ответ: " + my_web.read().decode('UTF-8'))

		
root = Tk()
root.title("Lighting UI")
root.geometry("450x340")
 
btn = Button(text="Включить свет 1", background="#555", foreground="#ccc",
             padx="20", pady="8", font="16", command=send1on)
btn.pack()

btn1 = Button(text="Выключить свет 1", background="#555", foreground="#ccc",
             padx="20", pady="8", font="16", command=send1off)
btn1.pack()


btn21 = Button(text="Включить свет 2", background="#555", foreground="#ccc",
             padx="20", pady="8", font="16", command=send2on)
btn21.pack()


btn22 = Button(text="Выключить свет 2", background="#555", foreground="#ccc",
             padx="20", pady="8", font="16", command=send2off)
btn22.pack()

btn223 = Button(text="Включить свет 3", background="#555", foreground="#ccc",
             padx="20", pady="8", font="16", command=send3on)
btn223.pack()

btn223 = Button(text="Выключить свет 3", background="#555", foreground="#ccc",
             padx="20", pady="8", font="16", command=send3off)
btn223.pack()

root.mainloop()	
	
print("Завершаю работу")