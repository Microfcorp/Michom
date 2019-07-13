<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php
header('Access-Control-Allow-Origin: *');

$ip = $_GET['device'];

$results = mysqli_query($link, "SELECT setting FROM modules WHERE ip = '$ip'");
while($row = $results->fetch_assoc()) {
    $retur = $row['setting'];
}    
exit($retur);
?>