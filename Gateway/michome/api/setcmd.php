<?
header('Access-Control-Allow-Origin: *');
$device = $_GET['device'];
$cmd = $_GET['cmd'];

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, 'http://'.$device.'/'.$cmd);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT_MS, 2000);
curl_setopt ($ch, CURLOPT_TIMEOUT_MS, 2000);
$m = @curl_exec($ch);
curl_close($ch);

if($m === FALSE)
    exit("Ошибка соеденения с модулем");
else
    exit($m);
?>