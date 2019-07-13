<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
<?
$page = !empty($_GET['p']) ? $_GET['p'] * 15 : 0;

$results = mysqli_query($link, "SELECT * FROM logging WHERE `id` > ".$page . " ");

$serv = [];

while($row = $results->fetch_assoc()) {
    $serv[] = Array($row['id'],$row['ip'],$row['type'],$row['rssi'],$row['log'],$row['date']);
}

//$serv = array_reverse($serv);

function GetIPName($ip){
    if($ip == "localhost"){
        return "Малинка";
    }
    elseif($ip == "192.168.1.10"){
        return "Модуль сбора информации";
    }
    elseif($ip == "192.168.1.11"){
        return "Модуль уличного термометра";
    }
    elseif($ip == "192.168.1.12"){
        return "Модуль 'Царского света'";
    }
    elseif($ip == "192.168.1.13"){
        return "Модуль информетра";
    }
    elseif($ip == "192.168.1.14"){
        return "Модуль HDC1080";
    }
    elseif($ip == "192.168.1.34"){
        return "Модуль освещения";
    }
}
?>
<!Doctype html>
<html>
<head>
<title>Управление Michome. Логи</title>
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
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome. Логи</H1>			

    <table>
        <tbody>
            <tr>
                <td>ID</td>
                <td>IP</td>
                <td>Тип</td>
                <td>RSSI</td>
                <td>Сообщение</td>
                <td>Дата</td>
            </tr>
            <?
                for($i = 0; $i < 15 & $i < count($serv); $i++){
                    echo "<tr>";
                    echo "<td>".$serv[$i][0]."</td>";
                    echo "<td title='".GetIPName($serv[$i][1])."'>".$serv[$i][1]."</td>";
                    echo "<td>".$serv[$i][2]."</td>";
                    echo "<td>".$serv[$i][3]."</td>";
                    echo "<td>".$serv[$i][4]."</td>";
                    echo "<td>".$serv[$i][5]."</td>";
                    echo "</tr>";
                }
            ?>
        </tbody>
    </table>
    <a href="logger.php?p=<? echo ($page/15 - 1); ?>"><<</a>
    <a href="logger.php?p=<? echo ($page/15 + 1); ?>">>></a>
    <br />
    <a href="logger.php?p=<? echo (count($serv)/15); ?>">Последняя</a>
    <a href="logger.php?p=<? echo (0); ?>">Первая</a>
</body>
<?php //include_once("/var/www/html/site/footer.php"); ?>
</html>