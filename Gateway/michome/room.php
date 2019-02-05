<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
<?
$temp1 = "";
$temp2 = "";
$temp3 = "";

$humm1 = "";
$humm2 = "";

$abc1 = "";
$abc2 = "";

$log1 = "";

$results = mysqli_query($link, "SELECT * FROM michom WHERE type='msinfoo' AND ip='192.168.1.10'");
while($row = $results->fetch_assoc()) {
	$temp1 = $row['temp'];
	$humm1 = $row['humm'];
	$abc1 = $row['dawlen'];
}
$results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.11'");
while($row = $results->fetch_assoc()) {
	$temp2 = $row['temp'];
}
$results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.12'");
while($row = $results->fetch_assoc()) {
	$humm2 = $row['humm'];
	$temp3 = $row['temp'];
}
$results = mysqli_query($link, "SELECT * FROM michom WHERE `date` >= CURDATE() AND `type`='Log' AND ip='192.168.1.10'");
while($row = $results->fetch_assoc()) {
	$log1 = $log1 + 1;
}
?>
<html>
<head>
<title>Управление Michome</title>
<script type="text/javascript">	
	//var caz = document.getElementById("cazestvo").value;
	function createXMLHttp() {
        if (typeof XMLHttpRequest != "undefined") { // для браузеров аля Mozilla
            return new XMLHttpRequest();
        } else if (window.ActiveXObject) { // для Internet Explorer (all versions)
            var aVersions = [
                "MSXML2.XMLHttp.5.0",
                "MSXML2.XMLHttp.4.0",
                "MSXML2.XMLHttp.3.0",
                "MSXML2.XMLHttp",
                "Microsoft.XMLHttp"
            ];
            for (var i = 0; i < aVersions.length; i++) {
                try {
                    var oXmlHttp = new ActiveXObject(aVersions[i]);
                    return oXmlHttp;
                } catch (oError) {}
            }
            throw new Error("Невозможно создать объект XMLHttp.");
        }
    }

// фукнция Автоматической упаковки формы любой сложности
function getRequestBody(oForm) {
    var aParams = new Array();
    for (var i = 0; i < oForm.elements.length; i++) {
        var sParam = encodeURIComponent(oForm.elements[i].name);
        sParam += "=";
        sParam += encodeURIComponent(oForm.elements[i].value);
        aParams.push(sParam);
    }
    return aParams.join("&");
}
// функция Ajax POST
function postAjax(url, oForm, callback) {
    // создаем Объект
    var oXmlHttp = createXMLHttp();
    // получение данных с формы
    var sBody = oForm;
    // подготовка, объявление заголовков
    oXmlHttp.open("POST", url, true);
    oXmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	//oXmlHttp.addHeader("Access-Control-Allow-Origin", "*");
    // описание функции, которая будет вызвана, когда придет ответ от сервера
    oXmlHttp.onreadystatechange = function() {
        if (oXmlHttp.readyState == 4) {
            if (oXmlHttp.status == 200) {
                callback(oXmlHttp.responseText);
            } else {
                callback('error' + oXmlHttp.statusText);
            }
        }
    };
    // отправка запроса, sBody - строка данных с формы
    oXmlHttp.send(sBody);
}
    </script>

<script>	
function Giron(q){
	var host = '<?echo $_SERVER['HTTP_HOST'];?>';
	
	if(host != "192.168.1.42"){
	//console.log('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'setlight?p='+p+'%26s='+size);
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.12' +'&cmd='+ 'setlight?p=3%26s='+q, "", function(){});
	}
	else{
		//console.log('http://192.168.1.34/setlight?p='+p+'&s='+size);
		postAjax('http://192.168.1.12/setlight?p=3&s='+q, "", function(){});
	}
	//sleep(500);
   }
</script>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome. План комнат</H1>
	<div style='float: left; background-color: #D4EB66; width: 400px; height: 300px'>
	<p style="text-align: center">Зал</p>
	<!-- <p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;" id="light1">Центральная люстра: <? //echo(mysqli_query($link, "SELECT * FROM michom  WHERE ip = '192.168.1.11'")->fetch_assoc()['data']);?> <a href="#" style="font-size: 11pt; font-family: Verdana, Arial, Helvetica, sans-serif;" OnClick="setlight(light1)">Изменить состояние</a></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;" id="light1">Прожектор: <? //echo(mysqli_query($link, "SELECT * FROM michom  WHERE ip = '192.168.1.46'")->fetch_assoc()['data']);?> <a href="#" style="font-size: 11pt; font-family: Verdana, Arial, Helvetica, sans-serif;" OnClick="setlight(light2)">Изменить состояние</a></p> -->
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp1);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Давление: <? echo($abc1);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Влажность: <? echo($humm1);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Всего за сегодня "Нанов": <? echo($log1);?></p>
	<a href="studiolight.php" style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Управление освещением</a>
	<p><a href="#" onclick="Giron('1')" style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Включить гирлянду</a></p>
	<p><a href="#" onclick="Giron('0')" style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Выключить гирлянду</a></p>
	</div>
	<div style='float: left; margin-left:10px; background-color: green; width: 400px; height: 300px'>
	<p style="text-align: center">Улица</p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp2);?></p>
	</div>
	<div style='clear: left; margin-top:10px; float: left; background-color: cyan; width: 400px; height: 300px'>
	<p style="text-align: center">Летний домик</p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp3);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Влажность: <? echo($humm2);?></p>
	</div>
	<div style='float: left; margin-top:10px; margin-left:10px; background-color: green; width: 400px; height: 300px'>
	<p style="text-align: center">Улица</p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp2);?></p>
	</div>
</body>
</html>