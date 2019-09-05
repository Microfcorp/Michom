<?
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");

$results = mysqli_query($link, "SELECT * FROM `michom` WHERE 1");
while($row = $results->fetch_assoc()) {
    $id = $row['id'] + 1;
}

$temperbater = exec("sudo python3 /etc/gettermist.py");
$date = date("Y-m-d H:i:s");
    
	/*if(intval($temperbatarey) < 25){
		curl_setopt_array($ch = curl_init(), array(
		  CURLOPT_URL => "https://api.pushover.net/1/messages.json",
		  CURLOPT_POSTFIELDS => array(
			"token" => "a3oe1bpbbcj4duooajrm98zx3kw5zi",
			"user" => "u5oywewtr3ant69yq1u758czivz877",
			"message" => "Внимание! Возможно потух котелы",
			"sound" => "tugboat",
		  ),
		  CURLOPT_SAFE_UPLOAD => true,
		  CURLOPT_RETURNTRANSFER => true,
		));
		curl_exec($ch);
		curl_close($ch);
	}
	*/
    $guery = "INSERT INTO `michom`(`id`, `ip`, `type`, `data`, `temp`, `humm`, `dawlen`, `visota`, `date`) VALUES ('$id', 'localhost', 'temperbatarey','0','$temperbater','','','','$date')"; 
	$result = mysqli_query($link, $guery);
    echo($result);
?>