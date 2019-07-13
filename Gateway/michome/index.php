<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
<?php require_once("/var/www/html/michome/lib/michom.php"); ?>
<?

    $API = new MichomeAPI('192.168.1.42', $link);
    
    header("Michome-Page: index");
    
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
	$results = mysqli_query($link, "SELECT * FROM michom WHERE `date` >= \"".date('Y-m-d',strtotime("-1 days"))."\"");
    
    $fgts = $API->TimeIns('192.168.1.10', 'selday', date("Y-m-d"));
    $seldays = explode(";", $fgts);
	
    $fgts1 = $API->TimeIns('192.168.1.11', 'selday', date("Y-m-d"));
    $seldays1 = explode(";", $fgts1);
    
    $fgts2 = $API->TimeIns('localhost', 'selday', date("Y-m-d"));
    $seldays2 = explode(";", $fgts2);

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

$lastfile = $files[count($files)-2];

?>
<!Doctype html>
<html>
<head>
<title>Управление Michome</title>
<script src="/site/MicrofLibrary.js"></script>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome</H1>
	
	<div style="float: right;">
        <p id='datetime'>Текущая дата</p>
        <p>Последнее обновление было: <? echo $date; ?></p>
        <p id='sledob'>Следующие бновление будет через: 0 минут</p>
        
        <p> 
            <a href="room.php">Комнаты</a> 
            <a href="calendar.php">Календарь информации</a> 
            <a href="logger.php?p=0">Логи</a> 
            <a href="module.php">Модули</a> 
        </p> 
        
    </div>
	
	<script type="text/javascript">
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
	    $results = mysqli_query($link, "SELECT ip FROM modules");
		while($row = $results->fetch_assoc()) {
            if($row['ip'] != "" & $row['ip'] != "localhost"){
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
	<a class="tooltip"><p>Текущая температура в комнате: <?echo $temper;?>С</p><span><img src="grafick.php?type=temp&start=<?echo $seldays[0];?>&period=<?echo $seldays[2];?>"/></span></a>
	<a class="tooltip"><p>Текущая влажность в комнате: <?echo $vlazn;?>%</p><span><img src="grafick.php?type=humm&start=<?echo $seldays[0];?>&period=<?echo $seldays[2];?>"/></span></a>
	<a class="tooltip"><p>Текущее давление в комнате: <?echo $davlenie;?> мм.рт</p><span><img src="grafick.php?type=dawlen&start=<?echo $seldays[0];?>&period=<?echo $seldays[2];?>"/></span></a>
	<? echo($alarm);?>
	
	<a class="tooltip"><p>Ощущается как на высоте: <?echo $visot;?> метров над уровнем моря</p><span><img src="grafick.php?type=visota&start=<?echo $seldays[0];?>&period=<?echo $seldays[2];?>"/></span></a>  
	
	<a class="tooltip"><p>Текущая температура на улице: <?echo $temper1;?>С</p><span><img src="grafick.php?type=tempul&start=<?echo $seldays1[0];?>&period=<?echo $seldays1[2];?>"/></span></a>
	
    <a class="tooltip"><p>Текущая температура трубы отопления: <?echo $temper3;?>С</p><span><img src="grafick.php?type=temperbatarey&start=<?echo $seldays2[0];?>&period=<?echo $seldays2[2];?>"/></span></a>
    
	<a class="tooltip"><p>Последнее фото: <? echo $lastfile;?></p><span><img width="540px" height="335px" src="/site/image/graphical/<?php echo $lastfile;?>"/></span></a>

	<p><?//include_once("prognoz.php");?></p>
	
	<span>Время восхода солнца: <? echo(date_sunrise(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)); ?></span><br>
	<span>Время захода солнца: <? echo(date_sunset(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)); ?></span><br>
	<span>Долгота дня: <? echo(date_sunset(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3) - date_sunrise(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)); ?> часов</span><br>
	</div>
</body>

<?php //include_once("/var/www/html/site/footer.php"); ?>

</html>