<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
<?
	$visot = "";
	$temper = "";
	$temper1 = "";
	$temper2 = "";
    $temper3 = "";
	$vlazn = "";
	$davlenie = "";
	$davlenie2 = "";
	$date = "";
	$alarm = "";
	$results = mysqli_query($link, "SELECT * FROM michom ");
    
    $fgts = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=192.168.1.10&type=selday&date=".date("Y-m-d"));
    $seldays = Array(explode(";", $fgts), explode(";", $fgts), explode(";", $fgts));
	

while($row = $results->fetch_assoc()) {
	if($row['temp'] != "" & $row['humm'] != "" & $row['dawlen'] != "" & $row['type'] == "msinfoo"){
    $temper = $row['temp'];
	$vlazn = $row['humm'];
	$davlenie = $row['dawlen'];
	$visot = $row['visota'];
	$date = $row['date'];
	//echo date("Y-m-d H:i:s", $date);
	}
	if($row['type'] == "get_light_status"){
    $statussvet = $row['data'];
	//echo date("Y-m-d H:i:s", $date);
	}
	if($row['type'] == "termometr"){
    $temper1 = $row['temp'];
	//echo date("Y-m-d H:i:s", $date);
	}
    if($row['type'] == "temperbatarey"){
    $temper3 = $row['temp'];
	//echo date("Y-m-d H:i:s", $date);
	}
	if($row['type'] == "hdc1080"){
    $temper2 = $row['temp'];
	$davlenie2 = $row['humm'];
	//echo date("Y-m-d H:i:s", $date);
	}
	if($row['type'] == "hdc1080andAlarm"){
    $temper2 = $row['temp'];
	$davlenie2 = $row['humm'];
	if($row['data'] == "Alarm"){
	$alarm = "<p style='color:red;'>Внимание! Проникновение</p>";
	}
	elseif($row['data'] == "OK"){
	$alarm = "<p style='color:green;'>Дверь закрыта охрана установлена</p>";
	}
	elseif($row['data'] == "null"){
	$alarm = "<p style='color:green;'>Охрана снята. Дверь открыта</p>";
	}
	elseif($row['data'] == "nullok"){
	$alarm = "<p style='color:green;'>Охрана снята. Дверь закрыта</p>";
	}
	//echo date("Y-m-d H:i:s", $date);
	}
}
/*
$curdate = date("i", $date);

$time = date("i");
 
echo date("i", $time - $curdate) . "\n";*/
	
	//$sleddate = date_parse($date)['minute'] - $curdate;	
    
function scandir_by_mtime($folder) {
  $dircontent = scandir($folder);
  $arr = array();
  foreach($dircontent as $filename) {
    if ($filename != '.' && $filename != '..') {
      if (filemtime($folder.$filename) === false) return false;
      $dat = filemtime($folder.$filename);
      $arr[$dat] = $filename;
    }
  }
  if (!ksort($arr)) return false;
  return $arr;
}

 $dir = "/var/www/html/site/image/graphical/";
 $files = array();
 foreach (scandir($dir) as $file) $files[$file] = filemtime("$dir/$file");
 asort($files);
 $files = array_keys($files);
 //print_r($files);
	
	//$files = scandir("/var/www/html/site/image/graphical/");
    //$files = scandir_by_mtime("/var/www/html/site/image/graphical/");
//rsort($files, SORT_NUMERIC);

//var_dump($files);

$lastfile = $files[count($files)-2];

	?>
<!Doctype html>
<html>
<head>
<title>Управление Michome</title>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome</H1>
	
	<div style="float: right;">
	<p id='datetime'>Текущая дата</p>
	<p>Последнее обновление было: <? echo $date; ?></p>
	<p id='sledob'>Следующие бновление будет через: 0 минут</p>
	<p><a href="room.php">Комнаты</a> <a href="calendar.php">Календарь информации</a> <a href="logger.php?p=0">Логи</a> </p>
	</div>
	
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

function GetData()
{
     // получаем индекс выбранного элемента
  	 var selind = document.getElementById("select").options.selectedIndex;
   var txt= document.getElementById("textcmd").value;
   var val= document.getElementById("select").options[selind].value;
  
   document.getElementById("cmdresult").innerHTML = "Отправка данных: " + txt + " На: " + val + ". Пожалуйста подождите..."; //log
  
   postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ val +'&cmd='+ txt.replace( /&/g, "%26" ), "", function(d){document.getElementById("cmdresult").innerHTML = d;
  
   window.setTimeout(function(){document.getElementById("cmdresult").innerHTML = "";},6000);
   
   });
}
   
   
	var x = new Date().getMinutes();

			function backTimer() {
				var j = document.getElementById('sledob');				
				var i = new Date('<?echo $date;?>').getMinutes();
				if(i < x) {
					j.innerHTML = "Следующие обновление будет через: " + String(((x - i)) - 10).substr(1) + " минут";					
				} else {
					j.innerHTML = "обновление";
					//window.setTimeout(function(){location.reload();},600);					
				}
				setTimeout(backTimer, 500);
			}
			
	function time(){		
window.setTimeout("time()",1000);
Data = new Date();
Year = Data.getFullYear();
Month = Data.getMonth();
Day = Data.getDate();
Hour = Data.getHours();
Minutes = Data.getMinutes();
Seconds = Data.getSeconds();
document.getElementById('datetime').innerHTML=Day + '.' + '01' + '.' + Year + ' ' + Hour + ":" + Minutes + ':' + Seconds;

	}		
			
	window.setTimeout("time()",1);
	window.setTimeout("backTimer()",1);	
	
    </script>
	
	<div>
    <H4>Отправить команду:</H4>
	  <form>
      <p>Команда: <input type="text" name="cmd" id='textcmd' /></p>	  
	  <p>На:  
      <select name="send" id='select'>
      <option  name='select' value="localhost">localhost</option>
	  <?php
        $res1 = [];
	    $results = mysqli_query($link, "SELECT DISTINCT ip FROM michom");
		while($row = $results->fetch_assoc()) {
            if($row['ip'] != "" & $row['ip'] != "localhost"){
                $res1[] = $row['ip'];
				echo "<option  name='select' value=".$row['ip'].">".$row['ip']."</option>";
			}
		}
        
        $results = mysqli_query($link, "SELECT DISTINCT ip FROM logging");
		while($row = $results->fetch_assoc()) {
            if($row['ip'] != "" & $row['ip'] != "localhost" & !in_array($row['ip'], $res1)){
				echo "<option  name='select' value=".$row['ip'].">".$row['ip']."</option>";
			}
		}
	  ?>
	  </select></p>
   
      <p><input name="sendcmd" value="Отправить" OnClick="GetData()" type="button" /></p>
      </form>	  
	</div>
	
	<div style="background-color:#03899C;">
	<p>Status Log: </p>
	<span id="cmdresult"></span>
	</div>
	
	<div>
	<a class="tooltip"><p>Текущая температура в комнате: <?echo $temper;?>С</p><span><img src="grafick.php?type=temp&start=<?echo $seldays[0][0];?>&period=<?echo $seldays[0][2];?>"/></span></a>
	<a class="tooltip"><p>Текущая влажность в комнате: <?echo $vlazn;?>%</p><span><img src="grafick.php?type=humm&start=<?echo $seldays[0][0];?>&period=<?echo $seldays[0][2];?>"/></span></a>
	<a class="tooltip"><p>Текущее давление в комнате: <?echo $davlenie;?> мм.рт</p><span><img src="grafick.php?type=dawlen&start=<?echo $seldays[0][0];?>&period=<?echo $seldays[0][2];?>"/></span></a>
	<? echo($alarm);?>
	
	<a class="tooltip"><p>Ощущается как на высоте: <?echo $visot;?> метров над уровнем моря</p><span><img src="grafick.php?type=visota&start=<?echo $seldays[0][0];?>&period=<?echo $seldays[0][2];?>"/></span></a>  
	
	<a class="tooltip"><p>Текущая температура на улице: <?echo $temper1;?>С</p><span><img src="grafick.php?type=tempul&start=<?echo $seldays[1][0];?>&period=<?echo $seldays[1][2];?>"/></span></a>
	
    <a class="tooltip"><p>Текущая температура трубы отопления: <?echo $temper3;?>С</p><span><img src="grafick.php?type=temperbatarey&start=<?echo $seldays[2][0];?>&period=<?echo $seldays[2][2];?>"/></span></a>
    
	<a class="tooltip"><p>Последнее фото: <? echo $lastfile;?></p><span><img width="540px" height="335px" src="/site/image/graphical/<?php echo $lastfile;?>"/></span></a>

	<p><?//include_once("prognoz.php");?></p>
	
	<span>Время восхода солнца: <? echo(date_sunrise(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)); ?></span><br>
	<span>Время захода солнца: <? echo(date_sunset(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)); ?></span><br>
	<span>Долгота дня: <? echo(date_sunset(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3) - date_sunrise(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)); ?> часов</span><br>
	</div>
</body>

<?php //include_once("/var/www/html/site/footer.php"); ?>

</html>