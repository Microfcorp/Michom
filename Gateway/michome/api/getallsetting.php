<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php
header('Access-Control-Allow-Origin: *');

$ip = $_GET['device'];

$ip = mysqli_real_escape_string($link, $ip);

$results = mysqli_query($link, "SELECT setting FROM modules WHERE ip = '$ip'");
while($row = $results->fetch_assoc()) {
    $retur = $row['setting'];
}    
exit($retur);
?>