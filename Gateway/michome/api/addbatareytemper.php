<?
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");

$results = mysqli_query($link, "SELECT * FROM `michom` WHERE 1");
while($row = $results->fetch_assoc()) {
    $id = $row['id'] + 1;
}

$temperbater = system("sudo python3 /etc/gettermist.py");
$date = date("Y-m-d H:i:s");
    
    $guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', 'localhost', 'temperbatarey','0','$temperbater','','','','$date')"; 
	$result = mysqli_query($link, $guery);
    echo($result);
?>