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
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, 'http://'.$tmp.'/getnameandid');
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT_MS, 300);
        curl_setopt ($ch, CURLOPT_TIMEOUT_MS, 300);
        $m = @curl_exec($ch);
        
		$call = explode("/n", $m);
		//var_dump($call);
		$ipsname[] = $call[0];
		$ipstype[] = $call[1];
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