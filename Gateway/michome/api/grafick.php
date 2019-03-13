<?php include_once("/var/www/html/site/mysql.php"); ?>
<?
    $par = "C";
 
    //определим массив с данными, которые необходимо вывести в виде графика.
	
	if($_GET['type'] == "tempul"){
		if(!empty($_GET['period'])){
		  $period = $_GET['period']; //144-oneday				  
		  if(!empty($_GET['start'])){
			  $results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.11' AND `id` >= ".$_GET['start']." AND `id` <= (".$_GET['start']." + ".$period.") ORDER BY id DESC LIMIT " . $period);
		  }
		  else{
			  $results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.11' ORDER BY id DESC LIMIT " . $period);
		  }
		}
		else{
		   $results = mysqli_query($link, "SELECT * FROM michom WHERE ip='192.168.1.11'");
		}
	}
    elseif($_GET['type'] == "temperbatarey"){
		if(!empty($_GET['period'])){
		  $period = $_GET['period']; //144-oneday				  
		  if(!empty($_GET['start'])){
			  $results = mysqli_query($link, "SELECT * FROM michom WHERE ip='localhost' AND `id` >= ".$_GET['start']." AND `id` <= (".$_GET['start']." + ".$period.") ORDER BY id DESC LIMIT " . $period);
		  }
		  else{
			  $results = mysqli_query($link, "SELECT * FROM michom WHERE ip='localhost' ORDER BY id DESC LIMIT " . $period);
		  }
		}
		else{
		   $results = mysqli_query($link, "SELECT * FROM michom WHERE ip='localhost'");
		}
	}
	else{
		if(!empty($_GET['period'])){
			$period = $_GET['period']; //144-oneday
		  if(!empty($_GET['start'])){
			  $results = mysqli_query($link, "SELECT * FROM michom WHERE `type`='msinfoo' AND `ip`='192.168.1.10' AND `id` >= ".$_GET['start']." AND `id` <= (".$_GET['start']." + ".$period.") ORDER BY id DESC LIMIT " . $period);
		  }
		  else{
			$results = mysqli_query($link, "SELECT * FROM michom WHERE `type`='msinfoo' AND `ip`='192.168.1.10' ORDER BY id DESC LIMIT " . $_GET['period']);
		  }
		}
		else{
		$results = mysqli_query($link, "SELECT * FROM michom WHERE `type`='msinfoo' AND `ip`='192.168.1.10'");
		}
	}
	

while($row = $results->fetch_assoc()) {
	if($_GET['type'] == "temp"){
		$par = "C";
		if($row['temp'] != ""){
    $data1[] = $row['temp'];
	$date1[] = $row['date'];
	if(!empty($_GET['period'])){
				$data = array_reverse($data1);
				$date = array_reverse($date1);
			}
			else{
				$data = $data1;
				$date = $date1;
			}
	}
	}
	elseif($_GET['type'] == "humm"){
		$par = "%";
		if($row['humm'] != ""){
    $data1[] = $row['humm'];
	$date1[] = $row['date'];
	if(!empty($_GET['period'])){
				$data = array_reverse($data1);
				$date = array_reverse($date1);
			}
			else{
				$data = $data1;
				$date = $date1;
			}
	}
	}
	elseif($_GET['type'] == "tempul" or $_GET['type'] == "temperbatarey"){
		$par = "C";
		if($row['temp'] != ""){
    $data1[] = $row['temp'];
	$date1[] = $row['date'];
			if(!empty($_GET['period'])){
				$data = array_reverse($data1);
				$date = array_reverse($date1);
			}
			else{
				$data = $data1;
				$date = $date1;
			}
	}
	}
	elseif($_GET['type'] == "visota"){
		$par = "М";
		if($row['visota'] != ""){
    $data1[] = $row['visota'];
	$date1[] = $row['date'];
			if(!empty($_GET['period'])){
				$data = array_reverse($data1);
				$date = array_reverse($date1);
			}
			else{
				$data = $data1;
				$date = $date1;
			}
	}
	}
	else{
		if($row['dawlen'] != ""){
			$par = "мм";
    $data1[] = $row['dawlen'];
	$date1[] = $row['date'];
	if(!empty($_GET['period'])){
				$data = array_reverse($data1);
				$date = array_reverse($date1);
			}
			else{
				$data = $data1;
				$date = $date1;
			}
	}
	}
}
 
    //параметры изображения  
    $width   = 540; //ширина
    $height  = 304 + 21; //высота
    $padding = 15;  //отступ от края 
    $step = 0.5;      //шаг координатной сетки	
 
    //определяем область отображения графика
    $gwidth  = $width - 2 * $padding; 
    $gheight = ($height - 21) - 2 * $padding; 
 
    //вычисляем минимальное и максимальное значение  
    $min = min($data) - 0.5;
    $min = floor($min/$step) * $step;
    $max = max($data) + 0.5;
    $max = ceil($max/$step) * $step;
 
    //отображение графика
    $cnt = count($data);
    $x2 = $padding;
    $i  = 0;
 
    //стоит отметить, что начало координат для картинки находится 
    //в левом верхнем углу, что определяет формулу вычисления координаты y
    $y2 = $gheight - ($data[$i] - $min) * ($gheight) / ($max - $min) + $padding;
 
	$arr = array();
    for($i = 1; $i < $cnt; $i++)
    {
      $x1 = $x2;
      $x2 = $x1 + (($gwidth) / ($cnt - 1));
      $y1 = $y2;
      $y2 = $gheight - ($data[$i] - $min) * ($gheight) / ($max - $min) + $padding;
 
	  $arr[] = ($x1).';'.($y1).";".$data[$i].";".$date[$i];
	  $arr[] = ($x2).';'.($y2).";".$data[$i].";".$date[$i];
	  $arr[] = (($x1+$x2)/2).';'.(($y1+$y2)/2).";".$data[$i].";".$date[$i];
    }
	
	$SrAr = array_sum($data)/count($data);
	 
	echo(json_encode(array($arr)));
?>