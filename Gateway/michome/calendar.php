<?php include_once("/var/www/html/site/mysql.php"); ?>

<html>
<head>
<title>Управление Michome</title>
<script>
function Graphics(type,module){
	if(type == "col"){
	  var txt= document.getElementById("textcmd").value;
	  document.getElementById('img1').src = "grafick.php?type="+module+"&period="+txt;
	}
	else if(type == "day"){
		var txt= document.getElementById("daycmd").value;
	    document.getElementById('img1').src = "grafick.php?type="+module+"&period="+(txt*144);
	}
}
function Rezim(d){
	document.getElementById("ulpog").style.display = "none";
	document.getElementById("temper").style.display = "none";
	document.getElementById("vlazn").style.display = "none";
	document.getElementById("dawlen").style.display = "none";
	document.getElementById(d).style.display = "block";
}
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
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','tempul')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','tempul')" type="button" /></br>
</div>

<div style="display:none;" id="temper">
<p style="color:red;">Просмотр графика температуры в доме</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','temp')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','temp')" type="button" /></br>
</div>

<div style="display:none;" id="vlazn">
<p style="color:red;">Просмотр графика влажности в доме</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','humm')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','humm')" type="button" /></br>
</div>

<div style="display:none;" id="dawlen">
<p style="color:red;">Просмотр графика давления в доме</p>
<p>Введите количество измерений. Обратим ваше внимание на то что 144 измерения равняется 1 дню, а 77 - 12 часам, 6 - одному часу</p>
<input type="text" name="cmd" id='textcmd' />
<input name="sendcmd" value="Прсмотреть" OnClick="Graphics('col','dawlen')" type="button" />
<p>Введите количество дней. Обратим ваше внимание на то что за 1 день происходит 144 измерения</p>
<input type="text" name="cmd" id='daycmd' />
<input value="Прсмотреть" OnClick="Graphics('day','dawlen')" type="button" /></br>
</div>

<img id="img1" src="grafick.php?type=tempul&period=144"></img>

</body>
</html>