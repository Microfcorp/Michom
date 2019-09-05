<?
require_once("/var/www/html/site/mysql.php");
require_once("/var/www/html/michome/lib/michom.php");
//$id = 0;

//$rnd = rand(0, 2);
//sleep($rnd);

/*$results = mysqli_query($link, "SELECT * FROM `michom` WHERE 1");
while($row = $results->fetch_assoc()) {
    $id = $row['id'] + 1;
}*/

$API = new MichomeAPI('192.168.1.42', $link);

$one = 1;

$temperdht = "";
$hummdht = "";
$temperbmp = "";
$davlen = "";
$data = "";
$rsid = "";
$date = date("Y-m-d H:i:s");

$getjson = $_POST['6'];
var_dump ( $getjson);

$obj = json_decode($getjson);
//sleep(2);
//var_dump($obj);
//print $obj->{'a'}; // 12345

$ip = $obj->{'ip'};
$type = $obj->{'type'};

//Получение rsid
if(!empty($obj->{'rsid'})){
    $rsid = $obj->{'rsid'};
}
elseif(!empty($obj->{'rssi'})){
    $rsid = $obj->{'rssi'};
}
else{
    $rsid = '';    
}

if($type == "msinfoo"){	//Модуль сбора информации
	$temperdht = $obj->{'data'}->{'temper'}; //Температура DHT11
	$temp = $obj->{'data'}->{'temperbmp'}; //Температура BMP180
	
	//$temp = ($temperdht + $temperbmp) / 2;
	$humm = $obj->{'data'}->{'humm'};//Влажность			
	$davlen = $obj->{'data'}->{'davlen'};//Давление
	$visot = $obj->{'data'}->{'visot'};//Высота
	
	if($temperdht != "nan"){
        $guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'msinfoo','$rsid','$temp','$humm','$davlen','$visot','$date')"; 
        $result = mysqli_query($link, $guery);
	}
	else{      
        $API->AddLog($ip, 'msinfoo', $rsid, 'MsinfooNAN', $date);

        $data1 = $API->GetPosledData('192.168.1.10')->Humm;

        $guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'msinfoo','$rsid','$temp','$data1','$davlen','$visot','$date')"; 
        $result = mysqli_query($link, $guery);
	}
}
elseif($type == "termometr"){	//Термометр
	$temper = $obj->{'data'}->{'temper'}; //Температура
	
	if(intval($temper) < 10 & $ip == "192.168.1.11"){
		curl_setopt_array($ch = curl_init(), array(
		  CURLOPT_URL => "https://api.pushover.net/1/messages.json",
		  CURLOPT_POSTFIELDS => array(
			"token" => "a3oe1bpbbcj4duooajrm98zx3kw5zi",
			"user" => "u5oywewtr3ant69yq1u758czivz877",
			"message" => "Внимание! На улице слишком низкая температура (".$temper.")",
		  ),
		  CURLOPT_SAFE_UPLOAD => true,
		  CURLOPT_RETURNTRANSFER => true,
		));
		curl_exec($ch);
		curl_close($ch);
	}
	
	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'termometr','$rsid','$temper','','','','$date')"; 
	$result = mysqli_query($link, $guery);
    
}
elseif($type == "Informetr"){	//Информетр
	$type = $obj->{'data'}->{'data'};
    $message = "Informetr: ".$type;
    
    $API->AddLog($ip, 'Informetr', $rsid, $message, $date);
    
    if($type == "GetData"){
       $ch = curl_init();
       curl_setopt($ch, CURLOPT_URL, "http://".$_SERVER['HTTP_HOST']."/michome/api/getprognoz.php?type=1");
       curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
       curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT_MS, 300);
       curl_setopt ($ch, CURLOPT_TIMEOUT_MS, 300);
       $pr = curl_exec($ch);
	   curl_close($ch);
       
       file_get_contents("http://192.168.1.13/setdata?param=".$pr);
    }
}
elseif($type == "hdc1080"){ //HDC1080	
	$temper = $obj->{'data'}->{'temper'};
	$humm = $obj->{'data'}->{'humm'};

	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'hdc1080','$rsid','$temper','$humm','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "hdc1080andAlarm"){	//HDC1080 и сигнализация
	$temper = $obj->{'data'}->{'temper'};
	$humm = $obj->{'data'}->{'humm'};
	$status = $obj->{'data'}->{'butt'};

	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'hdc1080andAlarm','$status','$temper','$humm','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "get_light_status"){//Модуль света	
	$status = $obj->{'data'}->{'status'};

	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'get_light_status','$status','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "get_button_press"){//Событие нажатия кнопки
	$status = $obj->{'data'}->{'status'};

	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'get_button_press','$status','','','','','$date')"; 
	//$result = mysqli_query($link, $guery);
}
elseif($type == "StudioLight"){	//Модуль освещения
	$status = $obj->{'data'}->{'status'};
    
    $API->AddLog($ip, 'StudioLight', $rsid, 'OK', $date);
}
elseif($type == "Log"){	//Лог
	$status = $obj->{'data'}->{'log'};
    
    $API->AddLog($ip, 'Log', $rsid, $status, $date);
}
elseif($type == "init"){ //Инициализация модуля
	$moduletype = $obj->{'data'}->{'type'};
    $moduleid = $obj->{'data'}->{'id'};

    $res = mysqli_query($link, "SELECT ip FROM modules WHERE ip = \"".$ip."\" limit 1");
    $count = mysqli_num_rows($res);
    if( $count > 0 ) {} //Пропускаем...
    else { //Добавляем в базу модулей
        $guery = "INSERT INTO `modules`(`ip`, `type`, `mID`, `urls`) VALUES ('$ip','$moduletype','$moduleid','refresh=Обновить данные;restart=Перезагрузить')";       
        $result = mysqli_query($link, $guery);
    }    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, 'http://'.$ip.'/setsettings?s='.$API->GetSettings($ip));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT, 10);
    curl_setopt ($ch, CURLOPT_TIMEOUT, 10);
    $pr = curl_exec($ch);
	curl_close($ch);
}
else{//Произвольное событие
	$data = $obj->{'data'};
	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', '$type','$data','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
echo $ip . "<br>";
echo $rsid. "<br>";
?>