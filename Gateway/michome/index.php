<?php include_once("/var/www/html/site/mysql.php"); ?>
	<?
	$temper = "";
	$vlazn = "";
	$davlenie = "";
	$date = "";
	$results = mysqli_query($link, "SELECT * FROM michom");

while($row = $results->fetch_assoc()) {
	if($row['temp'] != "" & $row['humm'] != "" & $row['dawlen'] != ""){
    $temper = $row['temp'];
	$vlazn = $row['humm'];
	$davlenie = $row['dawlen'];
	$date = $row['date'];
	}
}	
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
	<p id='sledob'>Следующие бновление будет через: минут</p>
	</div>
	<?
	
	?>
	<script>
	var x = new Date().getMinutes();

			function backTimer() {
				var j = document.getElementById('sledob');				
				var i = new Date('<?echo $date;?>').getMinutes();
				if(i < x) {
					j.innerHTML = "Следующие обновление будет через: " + String(((x - i)) - 10).substr(1) + " минут";
					setTimeout(backTimer, 500);
				} else {
					j.innerHTML = "обновление";
				}
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
			
	window.setTimeout("time()",1000);
	window.setTimeout("backTimer()",1000);
</script>
	<div>
    <H4>Отправить команду:</H4>
	  <form action="index.php" method="post">
      <p>Команда: <input type="text" name="cmd" /></p>	  
	  <p>На:  <select name="send">
	  <?
	    $results = mysqli_query($link, "SELECT DISTINCT ip FROM michom");

while($row = $results->fetch_assoc()) {
	if($row['ip'] != ""){
    echo "<option selected value=".$row['ip'].">".$row['ip']."</option>";
	}
}
	  ?>
   </select></p>
   
      <p><input name="sendcmd" type="submit" /></p>
      </form>
	  <?php
      if(!empty($_POST['sendcmd'])){
	   $cmd = $_POST['cmd'];
	   $to = $_POST['send'];	
	   $homepage = file_get_contents('http://'.$to.'/'.$cmd);
       echo $homepage;
      }
      ?>
	</div>
	<div>
	<p>Текущая тепература: <?echo $temper;?></p>
	<p>Текущая влажность: <?echo $vlazn;?>%</p>
	<p>Текущие давление: <?echo $davlenie;?> мм.рт</p>
	</div>
	<div>
	<table>
	<tbody>
	<tr>
	<td>
	<img style="-webkit-user-select: none;background-position: 0px 0px, 10px 10px;background-size: 20px 20px;background-image:linear-gradient(45deg, #eee 25%, transparent 25%, transparent 75%, #eee 75%, #eee 100%),linear-gradient(45deg, #eee 25%, white 25%, white 75%, #eee 75%, #eee 100%);" src="grafick.php?type=temp">
	</td>
    <td>	
	<img style="-webkit-user-select: none;background-position: 0px 0px, 10px 10px;background-size: 20px 20px;background-image:linear-gradient(45deg, #eee 25%, transparent 25%, transparent 75%, #eee 75%, #eee 100%),linear-gradient(45deg, #eee 25%, white 25%, white 75%, #eee 75%, #eee 100%);" src="grafick.php?type=humm">
	</td>
	<td>	
	<img style="-webkit-user-select: none;background-position: 0px 0px, 10px 10px;background-size: 20px 20px;background-image:linear-gradient(45deg, #eee 25%, transparent 25%, transparent 75%, #eee 75%, #eee 100%),linear-gradient(45deg, #eee 25%, white 25%, white 75%, #eee 75%, #eee 100%);" src="grafick.php?type=dawlen">
	</td>
	</tr>
	</tbody>
	</table>
	</div>
</body>
<footer>
<?php include_once("/var/www/html/site/footer.php"); ?>
</footer>
</html>
