<?php
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");

$results = mysqli_query($link, "SELECT * FROM `michom` WHERE type='msinfoo' AND ip='192.168.1.10' ORDER BY id DESC LIMIT 1");

$data = "";
while($row = $results->fetch_assoc()) {
    $data = $row['dawlen'];	
}
$results = mysqli_query($link, "SELECT * FROM `michom` WHERE type='termometr' AND ip='192.168.1.11' ORDER BY id DESC LIMIT 1");

$data1 = "";
while($row = $results->fetch_assoc()) {
    $data1 = $row['temp'];	
}
//echo $data;
//echo $data1[count($data1) - 1];

$mainreq = file_get_contents("http://openweathermap.org/data/2.5/forecast/daily/?appid=b6907d289e10d714a6e88b30761fae22&id=514198&units=metric");

$today = date("H");

if($today > 0 & $today < 9){        
       $req = json_decode($mainreq, true)["list"][0];
       $req1 = json_decode($mainreq, true)["list"][1];
}
else{
       $req = json_decode($mainreq, true)["list"][1];
       $req1 = json_decode($mainreq, true)["list"][0];
}
$req2 = json_decode($mainreq, true)["list"][2];
$req3 = json_decode($mainreq, true)["list"][3];
$req4 = json_decode($mainreq, true)["list"][4];
$req5 = json_decode($mainreq, true)["list"][5];

$ids = Array(200=>0,201=>0,202=>0,210=>0,211=>0,212=>0,221=>0,230=>0,231=>0,232=>0,300=>1,301=>1,302=>1,310=>1,311=>1,312=>1,313=>1,314=>1,321=>1,500=>2,501=>2,502=>2,503=>2,504=>2,511=>2,520=>2,521=>2,522=>2,531=>2,600=>3,601=>3,602=>3,611=>3,612=>3,615=>3,616=>3,620=>3,621=>3,622=>3,800=>4,801=>5,802=>5,803=>5,804=>5);

$local = ["Гроза","Мелкий дождик","Дождик","Снежок","Солнечно","Облачно"];    
    
if(empty($_GET['type'])){

    echo("Днём ".$req['temp']['day']."<br />");
    echo("Ночью ".$req['temp']['night']."<br />");
    echo("Ветер ".$req['speed']." m/s"."<br />");
    echo("Давление ".$req['pressure']."<br />");
    echo("Прогноз ".$local[$ids[$req['weather'][0]['id']]]."<br />");
}
else{

    if($today > 20 || $today < 7){
        $b = 0;
    }
    else{
        $b = 1;
    }
    
    $ret = Array('type'=>'json', 'curdate'=>date("Y-m-d"), 'dawlen'=>$data, 'temp'=>$data1, 'time'=>date("H:i:s"), 'd'=>$b, 
     'data'=>Array(
        Array('type'=>'json', '0'=>round($req['temp']['day'], 1), '1'=>round($req['temp']['night'], 1), '2'=>$req['speed'], '3'=>$req['pressure'], 'times'=>gmdate("Y-m-d", $req['dt']), '4'=>($ids[$req['weather'][0]['id']])), 
        Array('type'=>'json', '0'=>round($req1['temp']['day'], 1), 'times'=>gmdate("Y-m-d", $req1['dt']), '1'=>round($req1['temp']['night'], 1), '2'=>$req1['speed'], '3'=>$req1['pressure'], '4'=>($ids[$req1['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req2['dt']), '0'=>round($req2['temp']['day'], 1), '1'=>round($req2['temp']['night'], 1), '2'=>$req2['speed'], '3'=>$req2['pressure'], '4'=>($ids[$req2['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req3['dt']), '0'=>round($req3['temp']['day'], 1), '1'=>round($req3['temp']['night'], 1), '2'=>$req3['speed'], '3'=>$req3['pressure'], '4'=>($ids[$req3['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req4['dt']), '0'=>round($req4['temp']['day'], 1), '1'=>round($req4['temp']['night'], 1), '2'=>$req4['speed'], '3'=>$req4['pressure'], '4'=>($ids[$req4['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req5['dt']), '0'=>round($req5['temp']['day'], 1), '1'=>round($req5['temp']['night'], 1), '2'=>$req5['speed'], '3'=>$req5['pressure'], '4'=>($ids[$req5['weather'][0]['id']]))
    ));
    echo(json_encode($ret));
}
//var_dump($req);
?>