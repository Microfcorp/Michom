<?
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");

$num = 0;

if(!empty($_GET['device'])){ //Определение IP устройства
    $device = "`ip` = '".mysqli_real_escape_string($link, $_GET['device'])."'";
}
else{
	$device = 1;
}

if(!empty($_GET['type'])){ //Определение типа устройства
    $type = "`type` = '".mysqli_real_escape_string($link, $_GET['type'])."'";
}
else{
	$type = "`type` != 'Log'";
}

$cmd = $_GET['cmd']; //Комманда на получение типа данных

$data[] = "";
$date[] = "";

if($cmd == "temper"){//Температура
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$type." AND ".$device);
	}
	else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device);
	}

while($row = $results->fetch_assoc()) {
    $data[] = $row['temp'];
	$date[] = $row['date'];
	$num = $num + 1;
	}
		$cart = array(
  "name" => "getdata",
  "type" => $cmd,
  "col" => $num,
  "device" => $device,
  "data" => $data,
  "date" => $date
);
echo json_encode( $cart );

}
elseif($cmd == "textultemp"){//Текст уличной температуры
	$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device." ORDER BY `id` DESC LIMIT 1");
    
    while($row = $results->fetch_assoc()) {
        $data = $row['temp'];	
    }
    echo $data;
}
elseif($cmd == "texthumm"){//Текст влажности
	$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device." ORDER BY `id` DESC LIMIT 1");

    while($row = $results->fetch_assoc()) {
        $data = $row['humm'];	
    }
    echo $data;
}
elseif($cmd == "textdawlen"){//Текст давления
	$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device." ORDER BY `id` DESC LIMIT 1");

    while($row = $results->fetch_assoc()) {
        $data[] = $row['dawlen'];	
    }
    echo $data;
}
elseif($cmd == "humm"){//Влажность
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$type." AND ".$device);
	}
	else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device);
	}

while($row = $results->fetch_assoc()) {
    $data[] = $row['humm'];
	$date[] = $row['date'];
	$num = $num + 1;
}
    $cart = array(
      "name" => "getdata",
      "type" => $cmd,
      "col" => $num,
      "device" => $device,
      "data" => $data,
      "date" => $date
    );
echo json_encode( $cart );
}
//delet...
elseif($cmd == "tempertemp"){
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$type." AND ".$device);
	}
		else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device);
	}

while($row = $results->fetch_assoc()) {
    $data[] = $row['temp'];
	$date[] = $row['date'];
	$num = $num + 1;
	}
		$cart = array(
  "name" => "getdata",
  "type" => $cmd,
  "col" => $num,
  "device" => $device,
  "data" => $data,
  "date" => $date
);
echo json_encode( $cart );
}
///delet...///
elseif($cmd == "dawlen"){//Давление
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$type." AND ".$device);
	}
	else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device);
	}

while($row = $results->fetch_assoc()) {
    $data[] = $row['dawlen'];
	$date[] = $row['date'];
	$num = $num + 1;
}
    $cart = array(
      "name" => "getdata",
      "type" => $cmd,
      "col" => $num,
      "device" => $device,
      "data" => $data,
      "date" => $date
    );
echo json_encode( $cart );
}
elseif($cmd == "posledob"){	//Последнее обновление
	$results = mysqli_query($link, "SELECT * FROM michom WHERE ".$type." AND ".$device);

    while($row = $results->fetch_assoc()) {
        $date = $row['date'];
    }
	
echo $date;
}
elseif($cmd == "cursvet"){//Текущее состояние света
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND type = \"get_light_status\" AND ".$device);
	}
	else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE type = \"get_light_status\" AND ".$device);
	}

    while($row = $results->fetch_assoc()) {
        $data[] = $row['data'];
        $date[] = $row['date'];
        $num = $num + 1;
	}
	
    $cart = array(
      "name" => "getdata",
      "type" => $cmd,
      "col" => $num,
      "device" => $device,
      "data" => $data,
      "date" => $date
    );
echo json_encode( $cart );
}
elseif($cmd == "sobit"){//События
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$type." AND ".$device);
	}
		else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device);
	}

while($row = $results->fetch_assoc()) {
        $typedata[] = $row['type'];
        $data[] = $row['data'];
        $date[] = $row['date'];
        $num = $num + 1;
}
    $cart = array(
      "name" => "getdata",
      "type" => $cmd,
      "col" => $num,
      "device" => $device,
      "typedata" => $typedata,
      "data" => $data,
      "date" => $date
    );
echo json_encode( $cart );
}
elseif($cmd == "visota"){//Высота
	if(isset($_GET['date'])){
		$dates = $_GET['date'];
		$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$type." AND ".$device);
	}
		else{
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$type." AND ".$device);
	}

while($row = $results->fetch_assoc()) {
        $data[] = $row['visota'];
        $date[] = $row['date'];
        $num = $num + 1;
}
    $cart = array(
      "name" => "getdata",
      "type" => $cmd,
      "col" => $num,
      "device" => $device,
      "data" => $data,
      "date" => $date
    );
echo json_encode( $cart );
}

?>