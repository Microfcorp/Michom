<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
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

function Graphics(type,module,device,value){
	if(type == "col"){
	  var txt= value;
	  document.getElementById('img1').src = "grafick.php?type="+module+"&period="+txt;
	  Start("type="+module+"&period="+txt);
	}
	else if(type == "day"){
		var txt= value;
	    document.getElementById('img1').src = "grafick.php?type="+module+"&period="+(txt*144);
		Start("type="+module+"&period="+(txt*144));
	}
	else if(type == "curday"){		
		var datea = '<?php echo(date("Y-m-d")); ?>';
		selected(device,module,datea);
		//postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/timeins.php?device='+device+'&type=oneday', "", function(d){document.getElementById('img1').src = "grafick.php?type="+module+"&period="+d;});			    
	}
}
function Rezim(d){
	document.getElementById("ulpog").style.display = "none";
	document.getElementById("temper").style.display = "none";
	document.getElementById("vlazn").style.display = "none";
	document.getElementById("dawlen").style.display = "none";
	document.getElementById("visota").style.display = "none";
    document.getElementById("batareya").style.display = "none";
	document.getElementById(d).style.display = "block";
}

function selected(device,module,date){
	//p-11-13-2018 18-40
	
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/timeins.php?device='+device+'&type=selday&date='+date, "", function(d){
		
		var arr = d.split(';');
		document.getElementById('img1').src = "grafick.php?type="+module+"&period="+arr[2]+"&start="+arr[0];
		Start("type="+module+"&period="+arr[2]+"&start="+arr[0]);
	});	

	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/getphoto.php?date='+date, "", function(d){
		document.getElementById('img2').src = "/site/image/graphical/"+d;
	});		
		
}
function CurDate(){
	var date = new Date();
	
	return date.getFullYear() + "-" + date.getMonth() + "-" + date.getDate();
}
function Load(){
	Graphics('curday','tempul','192.168.1.11',"")
}

window.setTimeout("Load()",10);
</script>
<script>
function Setn(id){
	//alert(id);
	temphist.innerHTML = "  "+id;
}
function Start(resp){
	postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/grafick.php?'+resp, "", function(d){
        
        while (maps.firstChild) {
            maps.removeChild(maps.firstChild);
        }
		var json = JSON.parse(d);
		//alert(json[0][0]);
		for(var i=0; i < json[0].length; i++){
			var str = json[0][i];
			var radius = 4;
			var x = str.split(';')[0];
			var y = str.split(';')[1];
			///////
			var area = document.createElement('area');
			area.shape = "circle";
			area.coords = x+","+y+","+radius;
			area.target = "_blank";
			area.alt = "hyacinth";
			area.setAttribute("onclick", "Setn('"+str.split(';')[2]+" было "+str.split(';')[3]+"')");
			maps.appendChild(area);
			
		}
	});
}
</script>
<style>
/* скрываем чекбоксы и блоки с содержанием */
.hide,
.hide + label ~ div {
    display: none;
}
/* вид текста label */
.hide + label {
    margin: 0;
    padding: 0;
    color: green;
    cursor: pointer;
    display: inline-block;
}
/* вид текста label при активном переключателе */
.hide:checked + label {
    color: blue;
    border-bottom: 0;
}
/* когда чекбокс активен показываем блоки с содержанием  */
.hide:checked + label + div {
    display: block; 
    background: #efefef;
    -moz-box-shadow: inset 3px 3px 10px #7d8e8f;
    -webkit-box-shadow: inset 3px 3px 10px #7d8e8f;
    box-shadow: inset 1.4px 1.4px 10px #7d8e8f;
    margin-left: 20px;
    padding: 10px;
    /* чуточку анимации при появлении */
     -webkit-animation:fade ease-in 0.4s; 
     -moz-animation:fade ease-in 0.4s;
     animation:fade ease-in 0.4s; 
}

@-moz-keyframes fade {
    from { opacity: 0; }
to { opacity: 1 }
}
@-webkit-keyframes fade {
    from { opacity: 0; }
to { opacity: 1 }
}
@keyframes fade {
    from { opacity: 0; }
to { opacity: 1 }   
}

.temphis{
	padding-left: 10px;
	box-shadow: inset 10px 4px 20px 1px #1ea52e;
	color: blue;
}
.temphis:hover{
	box-shadow: inset 1px 4px 20px 1px #1ea52e;
	color: red;
}
</style>
</head>

<body>
<?php include_once("/var/www/html/site/verh.php"); ?>

<div>
<input value="График уличной температуры" OnClick="Rezim('ulpog')" type="button" />
<input value="График температуры батереи системы отопления" OnClick="Rezim('batareya')" type="button" />
<input value="График комнатной температуры" OnClick="Rezim('temper')" type="button" />
<input value="График комнатной влажности" OnClick="Rezim('vlazn')" type="button" />
<input value="График комнатного давления" OnClick="Rezim('dawlen')" type="button" />
<input value="График ощущаемой высоты" OnClick="Rezim('visota')" type="button" />
</div>

<div style="display:block;" id="ulpog">

<p style="color:red;">Просмотр графика температуры на улице</p>

    <input class="hide" id="hd-1" type="checkbox">
    <label for="hd-1">По количеству измерений</label>
    <div>        
		<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
		<input type="text" name="cmd" id='textcmd' />
		<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','tempul','192.168.1.11',document.getElementById('textcmd').value)" type="button" />
    </div>
	
</br></br>

    <input class="hide" id="hd-2" type="checkbox">
    <label for="hd-2">По количеству дней</label>
    <div>        
		<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
		<input type="text" name="cmd" id='daycmd' />
		<input value="Прсмотреть" OnClick="Graphics('day','tempul','192.168.1.11',document.getElementById('daycmd').value)" type="button" /></br>
    </div>
</br></br>
<input value="За сегодня" OnClick="Graphics('curday','tempul','192.168.1.11','')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.11','tempul',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="batareya">

<p style="color:red;">Просмотр графика температуры батереи системы отопления</p>

    <input class="hide" id="hd-55" type="checkbox">
    <label for="hd-55">По количеству измерений</label>
    <div>        
		<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
		<input type="text" name="cmd" id='textcmd55' />
		<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','temperbatarey','localhost',document.getElementById('textcmd55').value)" type="button" />
    </div>
	
</br></br>

    <input class="hide" id="hd-55" type="checkbox">
    <label for="hd-55">По количеству дней</label>
    <div>        
		<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
		<input type="text" name="cmd" id='daycmd55' />
		<input value="Прсмотреть" OnClick="Graphics('day','temperbatarey','localhost',document.getElementById('daycmd55').value)" type="button" /></br>
    </div>
</br></br>
<input value="За сегодня" OnClick="Graphics('curday','temperbatarey','localhost','')" type="button" /></br>
<p>За <input onchange="selected('localhost','temperbatarey',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="temper">
<p style="color:red;">Просмотр графика температуры в доме</p>
<input class="hide" id="hd-3" type="checkbox">
    <label for="hd-3">По количеству измерений</label>
    <div>        
		<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
		<input type="text" name="cmd" id='textcmd1' />
		<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','temp','192.168.1.10',document.getElementById('textcmd1').value)" type="button" />
    </div>
</br></br>
    <input class="hide" id="hd-4" type="checkbox">
    <label for="hd-4">По количеству дней</label>
    <div>        
		<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
		<input type="text" name="cmd" id='daycmd1' />
		<input value="Прсмотреть" OnClick="Graphics('day','temp','192.168.1.10',document.getElementById('daycmd1').value)" type="button" /></br>
    </div>
</br></br>
<input value="За сегодня" OnClick="Graphics('curday','temp','192.168.1.10','')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','temp',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="vlazn">
<p style="color:red;">Просмотр графика влажности в доме</p>
<input class="hide" id="hd-5" type="checkbox">
    <label for="hd-5">По количеству измерений</label>
    <div>        
		<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
		<input type="text" name="cmd" id='textcmd2' />
		<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','humm','192.168.1.10',document.getElementById('textcmd2').value)" type="button" />
    </div>
</br></br>
    <input class="hide" id="hd-6" type="checkbox">
    <label for="hd-6">По количеству дней</label>
    <div>        
		<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
		<input type="text" name="cmd" id='daycmd2' />
		<input value="Прсмотреть" OnClick="Graphics('day','humm','192.168.1.10',document.getElementById('daycmd2').value)" type="button" /></br>
    </div>
</br></br>
<input value="За сегодня" OnClick="Graphics('curday','humm','192.168.1.10','')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','humm',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="dawlen">
<p style="color:red;">Просмотр графика давления в доме</p>
<input class="hide" id="hd-7" type="checkbox">
    <label for="hd-7">По количеству измерений</label>
    <div>        
		<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
		<input type="text" name="cmd" id='textcmd3' />
		<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','dawlen','192.168.1.10',document.getElementById('textcmd3').value)" type="button" />
    </div>
</br></br>
    <input class="hide" id="hd-8" type="checkbox">
    <label for="hd-8">По количеству дней</label>
    <div>        
		<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
		<input type="text" name="cmd" id='daycmd3' />
		<input value="Прсмотреть" OnClick="Graphics('day','dawlen','192.168.1.10',document.getElementById('daycmd3').value)" type="button" /></br>
    </div>
</br></br>
<input value="За сегодня" OnClick="Graphics('curday','dawlen','192.168.1.10','')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','dawlen',this.value)" type="date" id='vibday' /></p>
</div>

<div style="display:none;" id="visota">
<p style="color:red;">Просмотр графика ощущаемой высоты</p>
<input class="hide" id="hd-9" type="checkbox">
    <label for="hd-9">По количеству измерений</label>
    <div>        
		<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
		<input type="text" name="cmd" id='textcmd4' />
		<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','visota','192.168.1.10',document.getElementById('textcmd4').value)" type="button" />
    </div>
</br></br>
    <input class="hide" id="hd-10" type="checkbox">
    <label for="hd-10">По количеству дней</label>
    <div>        
		<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
		<input type="text" name="cmd" id='daycmd4' />
		<input value="Прсмотреть" OnClick="Graphics('day','visota','192.168.1.10',document.getElementById('daycmd4').value)" type="button" /></br>
    </div>
</br></br>
<input value="За сегодня" OnClick="Graphics('curday','visota','192.168.1.10','')" type="button" /></br>
<p>За <input onchange="selected('192.168.1.10','visota',this.value)" type="date" id='vibday' /></p>
</div>
<p class="temphis" id="temphist">Что когда было<p>
<table>
<tbody>
<tr>
<td><p><img id="img1" usemap="#flowers" src="grafick.php?type=tempul&period=144"></img></p></td>
<td><p><img id="img2" width="540px" height="335px" src="grafick.php?type=tempul&period=144"></img></p></td>
</tr>
<tr>
<td>
<map id="maps" name="flowers">
</map>
</td>
</tr>
</tbody>
</table>

</body>
</html>