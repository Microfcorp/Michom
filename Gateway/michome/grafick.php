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
 
    //определим массив с данными, которые необходимо вывести в виде графика.
		
	$temper = "";
	$vlazn = "";
	$davlenie = "";
	$results = mysqli_query($link, "SELECT * FROM michom");

while($row = $results->fetch_assoc()) {
	if($_GET['type'] == "temp"){
		if($row['temp'] != ""){
    $data[] = $row['temp'];
	}
	}
	elseif($_GET['type'] == "humm"){
		if($row['humm'] != ""){
    $data[] = $row['humm'];
	}
	}
	else{
		if($row['dawlen'] != ""){
    $data[] = $row['dawlen'];
	}
	}
}
	
	
    /*$data[] = '60.00';
    $data[] = '58.72';
    $data[] = '60.74';
    $data[] = '54.30';
    $data[] = '57.95';
    $data[] = '61.47';
    $data[] = '63.78';
    $data[] = '56.07';
    $data[] = '52.67';
    $data[] = '6.07';
    $data[] = '45.26';
    $data[] = '47.24';*/
 
    //параметры изображения  
    $width   = 500; //ширина
    $height  = 300; //высота
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
 
    //определяем область отображения графика
    $gwidth  = $width - 2 * $padding; 
    $gheight = $height - 2 * $padding; 
 
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
 
    //Отдаем полученный график браузеру, меняя заголовок файла
    header ("Content-type: image/png");	
    ImagePng ($im);
?>