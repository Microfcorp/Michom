<?
include_once("/var/www/html/site/mysql.php");
$num = 0;
if(!empty($_GET['device'])){
$device = "ip='".$_GET['device']."'";
}
else{
	$device = 1;
}
$cmd = $_GET['cmd'];

$data[] = "";
$date[] = "";

if($cmd == "temper"){
		$results = mysqli_query($link, "SELECT * FROM `michom` WHERE ".$device);

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
elseif($cmd == "humm"){
		$results = mysqli_query($link, "SELECT * FROM michom WHERE ".$device);

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
elseif($cmd == "dawlen"){
		$results = mysqli_query($link, "SELECT * FROM michom WHERE ".$device);

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
elseif($cmd == "sobit"){
		$results = mysqli_query($link, "SELECT * FROM michom WHERE ".$device);

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

?>