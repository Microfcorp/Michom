API documentation

getdata.php?devece&cmd - device-if you want to filter data by a certain ip, but not necessarily (in this case, the data will be from the last received device). cmd-command from the list (temperature - temperature; textultemp - just a text string of temperature; humm - humidity; tempertemp - temperature; dawlen - pressure; posledob - date of last update; cursvet lighting module status; sobit - all events). The data comes in json format.

getdevice.php - Getting the JSON names, types and ip of all modules. Deprecated, but supported

getdevicenew.php - Getting the JSON names, types and ip of all modules. New

setcmd.php?device&cmd - Send a command to device with cmd command. Returns the answer
