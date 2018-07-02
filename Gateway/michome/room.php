<?php include_once("/var/www/html/site/mysql.php"); ?>
<?
$temp1 = "";
$temp2 = "";
$temp3 = "";

$humm1 = "";
$humm2 = "";

$abc1 = "";
$abc2 = "";

$results = mysqli_query($link, "SELECT * FROM michom WHERE type='msinfoo' AND ip='192.168.1.35'");
while($row = $results->fetch_assoc()) {
	$temp1 = $row['temp'];
	$humm1 = $row['humm'];
	$abc1 = $row['dawlen'];
}
$results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.45'");
while($row = $results->fetch_assoc()) {
	$temp2 = $row['temp'];
}
$results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.11'");
while($row = $results->fetch_assoc()) {
	$humm2 = $row['humm'];
	$temp3 = $row['temp'];
}
?>
<html>
<head>
<title>Управление Michome</title>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome. План комнат</H1>
	<div style='float: left; background-color: #D4EB66; width: 400px; height: 250px'>
	<p style="text-align: center">Зал</p>
	<!-- <p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;" id="light1">Центральная люстра: <? //echo(mysqli_query($link, "SELECT * FROM michom  WHERE ip = '192.168.1.45'")->fetch_assoc()['data']);?> <a href="#" style="font-size: 11pt; font-family: Verdana, Arial, Helvetica, sans-serif;" OnClick="setlight(light1)">Изменить состояние</a></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;" id="light1">Прожектор: <? //echo(mysqli_query($link, "SELECT * FROM michom  WHERE ip = '192.168.1.46'")->fetch_assoc()['data']);?> <a href="#" style="font-size: 11pt; font-family: Verdana, Arial, Helvetica, sans-serif;" OnClick="setlight(light2)">Изменить состояние</a></p> -->
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp1);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Давление: <? echo($abc1);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Влажность: <? echo($humm1);?></p>
	</div>
	<div style='float: left; margin-left:10px; background-color: green; width: 400px; height: 250px'>
	<p style="text-align: center">Улица</p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp2);?></p>
	</div>
	<div style='clear: left; margin-top:10px; float: left; background-color: cyan; width: 400px; height: 250px'>
	<p style="text-align: center">Летний домик</p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp3);?></p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Влажность: <? echo($humm2);?></p>
	</div>
	<div style='float: left; margin-top:10px; margin-left:10px; background-color: green; width: 400px; height: 250px'>
	<p style="text-align: center">Улица</p>
	<p style="font-size: 12pt; font-family: Verdana, Arial, Helvetica, sans-serif;">Температура: <? echo($temp2);?></p>
	</div>
</body>
</html>