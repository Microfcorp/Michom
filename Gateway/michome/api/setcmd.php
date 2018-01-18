<?
$device = $_GET['device'];
$cmd = $_GET['cmd'];

$data = file_get_contents('http://'.$device.'/'.$cmd);
echo $data;
?>