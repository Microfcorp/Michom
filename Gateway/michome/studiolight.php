<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
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
  function sleep(ms) {
ms += new Date().getTime();
while (new Date() < ms){}
}

   function sizePic(p, s) {
    var size = s;

	var host = '<?echo $_SERVER['HTTP_HOST'];?>';
	
	if(host != "192.168.1.42"){
	//console.log('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'setlight?p='+p+'%26s='+size);
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'setlight?p='+p+'%26s='+size, "", function(){});
	}
	else{
		//console.log('http://192.168.1.34/setlight?p='+p+'&s='+size);
		postAjax('http://192.168.1.34/setlight?p='+p+'&s='+size, "", function(){});
	}
	sleep(500);
   }
  </script>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome. План комнат. Управление освещением</H1>
	
	<div style='float: left; background-color: #D4EB66; width: 420px; height: 250px'>
	
	<p>Свет 1: <input type="range" min="0" max="255" oninput="sizePic(0, this.value)" value="0"><input type="number" min="0" max="255" oninput="sizePic(0, this.value)" value="0"><input type="button" onclick="sizePic(0, 255)" value="На всю"><input type="button" onclick="sizePic(0, 0)" value="На 0"></p>
	<p>Свет 2: <input type="range" min="0" max="255" oninput="sizePic(1, this.value)" value="0"><input type="number" min="0" max="255" oninput="sizePic(1, this.value)" value="0"><input type="button" onclick="sizePic(1, 255)" value="На всю"><input type="button" onclick="sizePic(1, 0)" value="На 0"></p>
	<p>Свет 3: <input type="range" min="0" max="255" oninput="sizePic(2, this.value)" value="0"><input type="number" min="0" max="255" oninput="sizePic(2, this.value)" value="0"><input type="button" onclick="sizePic(2, 255)" value="На всю"><input type="button" onclick="sizePic(2, 0)" value="На 0"></p>
	
	</div>
</body>
</html>