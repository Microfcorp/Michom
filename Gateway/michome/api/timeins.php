<?
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");
if(!empty($_GET['device'])){
$device = "ip='".$_GET['device']."'";
}
else{
	$device = 1;
}

$type = $_GET['type'];

if($type == "oneday"){
	$id = 0;
	$id1 = 0;
	
	//SELECT * FROM michom WHERE `date` >= CURDATE() AND `ip` = '192.168.1.11' ORDER BY id LIMIT 1 
	$results = mysqli_query($link, "SELECT * FROM michom WHERE `date` >= CURDATE() AND ".$device." ORDER BY id LIMIT 1");

	while($row = $results->fetch_assoc()) {
    $id = $row['id'];
	}
	
	$results = mysqli_query($link, "SELECT * FROM michom WHERE `id` >= ".$id." AND ".$device."");

	while($row = $results->fetch_assoc()) {
    $id1 = $row['id'];
	}
	
	echo $id1 - $id;
}
elseif($type == "selday"){
	//SELECT * FROM michom WHERE `date` >= "2018-08-06 00:00:00" AND `date` <= "2018-08-07 00:00:00"
	
	$date1 = $_GET['date'];
	
	$date = new DateTime($date1);
    $date->add(new DateInterval('P1D'));
    //echo $date->format('Y-m-d') . "\n";
	
	
	$results = mysqli_query($link, "SELECT * FROM michom WHERE `date` >= '".$date1."' AND `date` <= '".$date->format('Y-m-d')."'");

	while($row = $results->fetch_assoc()) {
    $ids[] = $row['id'];
	}
	echo (min($ids).";".max($ids).";".(max($ids)-min($ids)));
}
?>