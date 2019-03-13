<?
include_once("/var/www/html/site/mysql.php");
$id = 0;

$rnd = rand(1, 2);
sleep($rnd);

$results = mysqli_query($link, "SELECT * FROM `michom` WHERE 1");
while($row = $results->fetch_assoc()) {
    $id = $row['id'] + 1;
}
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
if(!empty($obj->{'rsid'})){
$rsid = $obj->{'rsid'};
}
else{
$rsid = $obj->{'rssi'};
}
if($type == "msinfoo"){	
	$temperdht = $obj->{'data'}->{'temper'};
	$temp = $obj->{'data'}->{'temperbmp'};
	
	//$temp = ($temperdht + $temperbmp) / 2;
	$humm = $obj->{'data'}->{'humm'};			
	$davlen = $obj->{'data'}->{'davlen'};
	$visot = $obj->{'data'}->{'visot'};
	
	if($temperdht != "nan"){
	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'msinfoo','$rsid','$temp','$humm','$davlen','$visot','$date')"; 
	$result = mysqli_query($link, $guery);
	}
	else{
	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'Log','MsionfooNan','$temp','$humm','$davlen','$visot','$date')"; 
	$result = mysqli_query($link, $guery);
    
    $id = $id + 1;

    $poslhumm = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/getdata.php?device=192.168.1.10&cmd=texthumm");
    $guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'msinfoo','$rsid','$temp','$poslhumm','$davlen','$visot','$date')"; 
	$result = mysqli_query($link, $guery);
	}
}
elseif($type == "termometr"){	
	$temper = $obj->{'data'}->{'temper'};

	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'termometr','$rsid','$temper','','','','$date')"; 
	$result = mysqli_query($link, $guery);
    
    $temperbater = system("sudo python3 /etc/gettermist.py");

    $id1 = $id + 1;
    
    $guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id1', 'localhost', 'temperbatarey','0','$temperbater','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "Informetr"){	
	$type = $obj->{'data'}->{'data'};
    if($type == "GetData"){
        file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/setcmd.php?device=192.168.1.13&cmd=setdata?param=".file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/getprognoz.php?type=1"));
    }
//GetData
	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'Informetr','$rsid','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
    
}
elseif($type == "hdc1080"){	
	$temper = $obj->{'data'}->{'temper'};
	$humm = $obj->{'data'}->{'humm'};

	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'hdc1080','$rsid','$temper','$humm','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "hdc1080andAlarm"){	
	$temper = $obj->{'data'}->{'temper'};
	$humm = $obj->{'data'}->{'humm'};
	$status = $obj->{'data'}->{'butt'};

	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'hdc1080andAlarm','$status','$temper','$humm','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "get_light_status"){	
	$status = $obj->{'data'}->{'status'};

	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'get_light_status','$status','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "StudioLight"){	
	$status = $obj->{'data'}->{'status'};

	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'StudioLight','$rsid','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
elseif($type == "Log"){	
	$status = $obj->{'data'}->{'log'};

	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', 'Log','$status','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
else{
	$data = $obj->{'data'};
	$guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', '$ip', '$type','$data','','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
echo $ip . "<br>";
//echo $temp. "<br>";
//echo $humm. "<br>";
echo $rsid. "<br>";
?>