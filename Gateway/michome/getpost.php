<?
include_once("/var/www/html/site/mysql.php");

$temperdht = "";
$hummdht = "";
$temperbmp = "";
$davlen = "";
$data = "";
$date = date("Y-m-d H:i:s");

$getjson = $_POST['6'];
//print_r ( $getjson);

$obj = json_decode($getjson);
//print $obj->{'a'}; // 12345

$ip = $obj->{'ip'};
$type = $obj->{'type'};
if($type == "msinfoo"){	
	$temperdht = $obj->{'data'}->{'temper'};
	$temperbmp = $obj->{'data'}->{'temper'};
	
	$temp = ($temperdht + $temperbmp) / 2;
	$humm = $obj->{'data'}->{'humm'};			
	$davlen = $obj->{'data'}->{'davlen'};
	
	if($humm != "nan"){
	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `date`) VALUES ('$ip', 'msinfoo','null','$temp','$humm','$davlen','$date')"; 
	$result = mysqli_query($link, $guery);
	}
}
else{
	$data = $obj->{'data'};
	$guery = "INSERT INTO `michom`(`ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `date`) VALUES ('$ip', '$type','$data','','','','$date')"; 
	$result = mysqli_query($link, $guery);
}
echo $ip . "<br>";
echo $temp. "<br>";
echo $humm. "<br>";
?>