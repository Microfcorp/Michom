<?php include_once("/var/www/html/site/mysql.php"); ?>

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

function Graphics(type,module,device){
	if(type == "col"){
	  var txt= document.getElementById("textcmd").value;
	  document.getElementById('img1').src = "grafick.php?type="+module+"&period="+txt;
	}
	else if(type == "day"){
		var txt= document.getElementById("daycmd").value;
	    document.getElementById('img1').src = "grafick.php?type="+module+"&period="+(txt*144);
	}
	else if(type == "curday"){		
		var txt= "";
		postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/timeins.php?device='+device+'&type=oneday', "", function(d){document.getElementById('img1').src = "grafick.php?type="+module+"&period="+d;});			    
	}
}
function Rezim(d){
	document.getElementById("ulpog").style.display = "none";
	document.getElementById("temper").style.display = "none";
	document.getElementById("vlazn").style.display = "none";
	document.getElementById("dawlen").style.display = "none";
	document.getElementById(d).style.display = "block";
}

function selected(device,module,date){
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/timeins.php?device='+device+'&type=selday&date='+date, "", function(d){
		
		var arr = d.split(';');
		document.getElementById('img1').src = "grafick.php?type="+module+"&period="+arr[2]+"&start="+arr[0];
		
		});			    
		
}
function CurDate(){
	var date = new Date();
	
	return date.getFullYear() + "-" + date.getMonth() + "-" + date.getDate();
}
//selected('192.168.1.11','tempul',CurDate());
</script>
</head>

<body>
<?php include_once("/var/www/html/site/verh.php"); ?>

<div>
<input value="График уличной погоды" OnClick="Rezim('ulpog')" type="button" />
<input value="График комнатной температуры" OnClick="Rezim('temper')" type="button" />
<input value="График комнатной влажности" OnClick="Rezim('vlazn')" type="button" />
<input value="График комнатного давления" OnClick="Rezim('dawlen')" type="button" />
</div>

<div style="display:block;" id="ulpog">
<p style="color:red;">Просмотр графика температуры на улице</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','tempul','192.168.1.11')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','tempul','192.168.1.11')" type="button" /></br>
<input value="За сегодня" OnClick="Graphics('curday','tempul','192.168.1.11')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.11','tempul',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="temper">
<p style="color:red;">Просмотр графика температуры в доме</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','temp','192.168.1.11')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','temp','192.168.1.10')" type="button" /></br>
<input value="За сегодня" OnClick="Graphics('curday','temp','192.168.1.10')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','temp',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="vlazn">
<p style="color:red;">Просмотр графика влажности в доме</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','humm','192.168.1.10')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','humm','192.168.1.10')" type="button" /></br>
<input value="За сегодня" OnClick="Graphics('curday','humm','192.168.1.10')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','vlazn',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="dawlen">
<p style="color:red;">Просмотр графика давления в доме</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','dawlen','192.168.1.10')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','dawlen','192.168.1.10')" type="button" /></br>
<input value="За сегодня" OnClick="Graphics('curday','dawlen','192.168.1.10')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','dawlen',this.value)" type="date" id='vibday' /></p>
</div>

<img id="img1" src="grafick.php?type=tempul&period=144"></img>

</body>
</html>