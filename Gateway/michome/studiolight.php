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
   
   function Strobo(p, s, d) {
	   
	var size = s;

	var host = '<?echo $_SERVER['HTTP_HOST'];?>';
	
	if(host != "192.168.1.42"){
	//console.log('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'setlight?p='+p+'%26s='+size);
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'strobo?p='+p+'%26s='+size+'%26t='+d, "", function(){});
	}
	else{
		//console.log('http://192.168.1.34/setlight?p='+p+'&s='+size);
		postAjax('http://192.168.1.34/strobo?p='+p+'&s='+size+'&t='+d, "", function(){});
	}	
   }
   function Stroboall(s, d) {
	   
	var size = s;

	var host = '<?echo $_SERVER['HTTP_HOST'];?>';
	
	if(host != "192.168.1.42"){
	//console.log('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'setlight?p='+p+'%26s='+size);
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ '192.168.1.34' +'&cmd='+ 'stroboall?s='+size+'%26t='+d, "", function(){});
	}
	else{
		//console.log('http://192.168.1.34/setlight?p='+p+'&s='+size);
		postAjax('http://192.168.1.34/stroboall?&s='+size+'&t='+d, "", function(){});
	}	
   }
  </script>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome. План комнат. Управление освещением</H1>
	
	<div style='float: left; background-color: #D4EB66; width: 420px; height: auto'>
	
	<p>Свет 1: <input type="range" min="0" max="1023" oninput="sizePic(0, this.value)" value="0"><input type="number" min="0" max="1023" oninput="sizePic(0, this.value)" value="0"><input type="button" onclick="sizePic(0, 1023)" value="На всю"><input type="button" onclick="sizePic(0, 0)" value="На 0"></p>
	<p>Свет 2: <input type="range" min="0" max="1023" oninput="sizePic(1, this.value)" value="0"><input type="number" min="0" max="1023" oninput="sizePic(1, this.value)" value="0"><input type="button" onclick="sizePic(1, 1023)" value="На всю"><input type="button" onclick="sizePic(1, 0)" value="На 0"></p>
	<p>Свет 3: <input type="range" min="0" max="1023" oninput="sizePic(2, this.value)" value="0"><input type="number" min="0" max="1023" oninput="sizePic(2, this.value)" value="0"><input type="button" onclick="sizePic(2, 1023)" value="На всю"><input type="button" onclick="sizePic(2, 0)" value="На 0"></p>
	<br />
	<p>Свет 1 Стробо: <input type="number" min="0" max="100" id="sb1" value="3"><input type="number" min="0" max="500" id="st1" value="30"><input type="button" onclick="Strobo(0, document.getElementById('sb1').value, document.getElementById('st1').value)" value="Старт"></p>
	<p>Свет 2 Стробо: <input type="number" min="0" max="100" id="sb2" value="3"><input type="number" min="0" max="500" id="st2" value="30"><input type="button" onclick="Strobo(1, document.getElementById('sb2').value, document.getElementById('st2').value)" value="Старт"></p>
	<p>Свет 3 Стробо: <input type="number" min="0" max="100" id="sb3" value="3"><input type="number" min="0" max="500" id="st3" value="30"><input type="button" onclick="Strobo(2, document.getElementById('sb3').value, document.getElementById('st3').value)" value="Старт"></p>
	<br />
	<p>Стробо: <input type="number" min="0" max="100" id="sb4" value="3"><input type="number" min="0" max="500" id="st4" value="30"><input type="button" onclick="Stroboall(document.getElementById('sb4').value, document.getElementById('st4').value)" value="Старт"></p>
	</div>
</body>
</html>