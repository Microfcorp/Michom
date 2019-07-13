<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
<?php require_once("/var/www/html/michome/lib/michom.php"); 
      $API = new MichomeAPI('192.168.1.42', $link);
?>
<html>
<head>
<title>Управление Michome</title>
<script>
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

function CurDate(){
	var date = new Date();
	
	return date.getFullYear() + "-" + date.getMonth() + "-" + date.getDate();
}
</script>
</head>

<body>
<?php include_once("/var/www/html/site/verh.php"); ?>

<H2 style='color: red;'>Управление Michome. Календарь информации. Интересные факты</H2>

<div id="year">
<H4 style='color: aqua;'>За этот год:</H4>

<p>_____Максимальная температура на улице в этом году равна <?php echo (max($API->GetTemperatureDiap('192.168.1.11', '1', (Date("Y")).'-01-01 00:00:00')['data'])); ?> градусов</p>
<p>_____Минимальная температура на улице в этом году равна <?php echo (min($API->GetTemperatureDiap('192.168.1.11', '1', (Date("Y")).'-01-01 00:00:00')['data'])); ?> градусов</p>

<p>_______Максимальная температура на улице в этом месяце равна <?php echo (max($API->GetTemperatureDiap('192.168.1.11', '1', (Date("Y")).'-'.(Date("m")).'-01 00:00:00')['data'])); ?> градусов</p>
<p>_______Минимальная температура на улице в этом месяце равна <?php echo (min($API->GetTemperatureDiap('192.168.1.11', '1', (Date("Y")).'-'.(Date("m")).'-01 00:00:00')['data'])); ?> градусов</p>
</div>
</body>
</html>