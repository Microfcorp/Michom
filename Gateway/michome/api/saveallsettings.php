<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php
header('Access-Control-Allow-Origin: *');

$ip = $_GET['device'];
$data = $_GET['d'];

$results = mysqli_query($link, "UPDATE `modules` SET `setting`='$data' WHERE ip = '$ip'");

if($results){
    exit("OK");
}
?>