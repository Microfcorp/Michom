<?php include_once("/var/www/html/site/mysql.php"); ?>
<?
//вспомогательная функция для определения цвета
    function ImageColor($im, $color_array)
    {
      return ImageColorAllocate(
      $im,
      isset($color_array['r']) ? $color_array['r'] : 0, 
      isset($color_array['g']) ? $color_array['g'] : 0, 
      isset($color_array['b']) ? $color_array['b'] : 0 
      );
    }
 
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
	else{
		if(!empty($_GET['period'])){
			$period = $_GET['period']; //144-oneday
		  if(!empty($_GET['start'])){
			  $results = mysqli_query($link, "SELECT * FROM michom WHERE `ip`='192.168.1.10' AND `id` >= ".$_GET['start']." AND `id` <= (".$_GET['start']." + ".$period.") ORDER BY id DESC LIMIT " . $period);
		  }
		  else{
			$results = mysqli_query($link, "SELECT * FROM michom WHERE `ip`='192.168.1.10' ORDER BY id DESC LIMIT " . $_GET['period']);
		  }
		}
		else{
		$results = mysqli_query($link, "SELECT * FROM michom WHERE `ip`='192.168.1.10'");
		}
	}
	

while($row = $results->fetch_assoc()) {
	if($_GET['type'] == "temp"){
		$par = "C";
		if($row['temp'] != ""){
    $data1[] = $row['temp'];
	if(!empty($_GET['period'])){
				$data = array_reverse($data1);
			}
			else{
				$data = $data1;
			}
	}
	}
	elseif($_GET['type'] == "humm"){
		$par = "%";
		if($row['humm'] != ""){
    $data1[] = $row['humm'];
	if(!empty($_GET['period'])){
				$data = array_reverse($data1);
			}
			else{
				$data = $data1;
			}
	}
	}
	elseif($_GET['type'] == "tempul"){
		$par = "C";
		if($row['temp'] != ""){
    $data1[] = $row['temp'];
			if(!empty($_GET['period'])){
				$data = array_reverse($data1);
			}
			else{
				$data = $data1;
			}
	}
	}
	elseif($_GET['type'] == "visota"){
		$par = "М";
		if($row['visota'] != ""){
    $data1[] = $row['visota'];
			if(!empty($_GET['period'])){
				$data = array_reverse($data1);
			}
			else{
				$data = $data1;
			}
	}
	}
	else{
		if($row['dawlen'] != ""){
			$par = "мм";
    $data1[] = $row['dawlen'];
	if(!empty($_GET['period'])){
				$data = array_reverse($data1);
			}
			else{
				$data = $data1;
			}
	}
	}
}
 
    //параметры изображения  
    $width   = 540; //ширина
    $height  = 304 + 21; //высота
    $padding = 15;  //отступ от края 
    $step = 0.5;      //шаг координатной сетки
 
    //создаем изображение
    $im = @ImageCreate ($width, $height) 
      or die ("Cannot Initialize new GD image stream");
 
    //задаем цвета, которые будут использоваться при отображении картинки
    $bgcolor = ImageColor($im, array('r'=>255, 'g'=>255, 'b'=>255)); 
    $color = ImageColor($im, array('b'=>175)); 
    $green = ImageColor($im, array('g'=>175)); 
    $gray = ImageColor($im, array('r'=>175, 'g'=>175, 'b'=>175));
    $maxmin = ImageColor($im, array('r'=>3, 'g'=>104, 'b'=>58));	
 
    //определяем область отображения графика
    $gwidth  = $width - 2 * $padding; 
    $gheight = ($height - 21) - 2 * $padding; 
 
    //вычисляем минимальное и максимальное значение  
    $min = min($data) - 0.5;
    $min = floor($min/$step) * $step;
    $max = max($data) + 0.5;
    $max = ceil($max/$step) * $step;
 
    //рисуем сетку значений
    for($i = $min; $i < $max + $step; $i += $step)
    {
      $y = $gheight - ($i - $min) * ($gheight) / ($max - $min) + $padding;
      ImageLine($im, $padding, $y, $gwidth + $padding, $y, $gray);
      ImageTTFText($im, 8, 0, $padding + 1, $y - 1, $gray, "/var/www/html/site/Verdana.ttf", $i);
    }
 
    //отображение графика
    $cnt = count($data);
    $x2 = $padding;
    $i  = 0;
 
    //стоит отметить, что начало координат для картинки находится 
    //в левом верхнем углу, что определяет формулу вычисления координаты y
    $y2 = $gheight - ($data[$i] - $min) * ($gheight) / ($max - $min) + $padding;
 
    for($i = 1; $i < $cnt; $i++)
    {
      $x1 = $x2;
      $x2 = $x1 + (($gwidth) / ($cnt - 1));
      $y1 = $y2;
      $y2 = $gheight - ($data[$i] - $min) * ($gheight) / ($max - $min) + $padding;
 
      //Рисуются две линии, чтобы сделать график более заметным      
      ImageLine($im, $x1, $y1, $x2, $y2, $color);
      ImageLine($im, $x1 + 1, $y1, $x2 + 1, $y2, $color);
    }
	
	$SrAr = array_sum($data)/count($data);
	
	ImageTTFText($im, 10, 0, 10, $height - 21, $maxmin, "/var/www/html/site/Verdana.ttf", "Максимальное значение на графике " . max($data) . $par.". Минимальное " . min($data) . $par.".\nАмплитуда равна " . substr((max($data) - min($data)),0,4) . $par.". Среднее значение равно ".substr($SrAr,0,5). $par.".");
 
    //Отдаем полученный график браузеру, меняя заголовок файла
    header ("Content-type: image/png");	
    ImagePng ($im);
	imagedestroy($im);
?>