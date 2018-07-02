<?
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");
$num = 0;
$results = mysqli_query($link, "SELECT DISTINCT ip FROM michom");

    while($row = $results->fetch_assoc()) {
	  if($row['ip'] != ""){
      $ips[] = $row['ip'];
	  $num = $num + 1;
	  }
    }
	
	foreach($ips as $tmp){
		$ipsname[] = file_get_contents('http://'.$tmp.'/getid');
		$ipstype[] = file_get_contents('http://'.$tmp.'/gettype');
	}
	
	$cart = array(
  "name" => "getdivece",
  "col" => $num,
  "ips" => $ips, 
  "devicename" => $ipsname,
  "devicetype" => $ipstype
);
echo json_encode( $cart );
?>