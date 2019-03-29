<?
include_once("/var/www/html/site/mysql.php");
//$id = 0;

//$rnd = rand(0, 2);
//sleep($rnd);

/*$results = mysqli_query($link, "SELECT * FROM `michom` WHERE 1");
while($row = $results->fetch_assoc()) {
    $id = $row['id'] + 1;
}*/

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
        $guery = "INSERT INTO `logging`(`ip`, `type`, `rssi`, `log`, `date`) VALUES ('$ip', 'msinfoo','$rsid','MsinfooNAN','$date')";
        $result = mysqli_query($link, $guery);  

        $results1 = mysqli_query($link, "SELECT * FROM `michom` WHERE type='msinfoo' AND ip='192.168.1.10' ORDER BY id DESC LIMIT 1");

        $data1 = "";
        while($row = $results1->fetch_assoc()) {
            $data1 = $row['humm'];	
        }

        $guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'msinfoo','$rsid','$temp','$data1','$davlen','$visot','$date')"; 
        $result = mysqli_query($link, $guery);
	}
}
elseif($type == "termometr"){	//Термометр
	$temper = $obj->{'data'}->{'temper'}; //Температура

	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'termometr','$rsid','$temper','','','','$date')"; 
	$result = mysqli_query($link, $guery);
    
}
elseif($type == "Informetr"){	//Информетр
	$type = $obj->{'data'}->{'data'};
    $message = "Informetr: ".$type;
    $guery = "INSERT INTO `logging`(`ip`, `type`, `rssi`, `log`, `date`) VALUES ('$ip', 'Informetr','$rsid','$message','$date')";
	$result = mysqli_query($link, $guery);
    if($type == "GetData"){
        file_get_contents("http://192.168.1.13/setdata?param=".file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/getprognoz.php?type=1"));
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
elseif($type == "StudioLight"){	//Модуль освещения
	$status = $obj->{'data'}->{'status'};

    $guery = "INSERT INTO `logging`(`ip`, `type`, `rssi`, `log`, `date`) VALUES ('$ip', 'StudioLight','$rsid','OK','$date')";
	//$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'StudioLight','$rsid','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "Log"){	//Лог
	$status = $obj->{'data'}->{'log'};

    $guery = "INSERT INTO `logging`(`ip`, `type`, `rssi`, `log`, `date`) VALUES ('$ip', 'Log','$rsid','$status','$date')";
	//$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', 'Log','$status','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
else{//Произвольное событие
	$data = $obj->{'data'};
	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$ip', '$type','$data','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
echo $ip . "<br>";
//echo $temp. "<br>";
//echo $humm. "<br>";
echo $rsid. "<br>";
?>