<?php
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");
require_once("/var/www/html/michome/lib/foreca.php");

$foreca = new Foreca('Russia', 'Ostrogozhsk');
/*$results = mysqli_query($link, "SELECT * FROM `michom` WHERE type='msinfoo' AND ip='192.168.1.10' ORDER BY id DESC LIMIT 1");

$data = "";
while($row = $results->fetch_assoc()) {
    $data = $row['dawlen'];	
}*/
$results = mysqli_query($link, "SELECT * FROM `michom` WHERE type='termometr' AND ip='192.168.1.11' ORDER BY id DESC LIMIT 1");

$data1 = "";
while($row = $results->fetch_assoc()) {
    $data1 = $row['temp'];	
}
//echo $data;
//echo $data1[count($data1) - 1];

$mainreq = file_get_contents("http://openweathermap.org/data/2.5/forecast/daily/?appid=b6907d289e10d714a6e88b30761fae22&id=514198&units=metric");

$today = date("H");
    
$req = json_decode($mainreq, true)["list"][0];
$req1 = json_decode($mainreq, true)["list"][1];
$req2 = json_decode($mainreq, true)["list"][2];
$req3 = json_decode($mainreq, true)["list"][3];
$req4 = json_decode($mainreq, true)["list"][4];
$req5 = json_decode($mainreq, true)["list"][5];

$ids = Array(200=>0,201=>0,202=>0,210=>0,211=>0,212=>0,221=>0,230=>0,231=>0,232=>0,300=>1,301=>1,302=>1,310=>1,311=>1,312=>1,313=>1,314=>1,321=>1,500=>2,501=>2,502=>2,503=>2,504=>2,511=>2,520=>2,521=>2,522=>2,531=>2,600=>3,601=>3,602=>3,611=>3,612=>3,615=>3,616=>3,620=>3,621=>3,622=>3,800=>4,801=>5,802=>5,803=>5,804=>5);

$local = ["Гроза","Мелкий дождик","Дождик","Снежок","Солнечно","Облачно"];    
    
if(empty($_GET['type'])){        
        
    echo("Днём ".$foreca->GetTodayPrognoz()->TDay."<br />");
    echo("Ночью ".$foreca->GetTodayPrognoz()->TNight."<br />");
    echo("Ветер ".$req['speed']." m/s"."<br />");
    echo("Давление ".$req['pressure']."<br />");
    echo("Прогноз ".$local[$ids[$req['weather'][0]['id']]]."<br />");
    
        var_dump($foreca->GetAfterNinePrognoz());
}
else{

    if($today > 20 || $today < 7){
        $b = 0;
    }
    else{
        $b = 1;
    }
    
    $prognoz = $foreca->GetAllPrognoz();
    
    $ret = Array('type'=>'json', 'curdate'=>date("Y-m-d"), 'dawlen'=>$foreca->Pressure(), 'temp'=>$data1, 'time'=>date("H:i:s"), 'd'=>$b, 
     'data'=>Array(
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req['dt']),  '0'=>round($prognoz[0]->TDay, 1),  '1'=>round($prognoz[0]->TNight, 1),  '2'=>$prognoz[0]->Wind->Speed,  '3'=>round($req['pressure']/1.334, 2),  '4'=>($ids[$req['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req1['dt']), '0'=>round($prognoz[1]->TDay, 1), '1'=>round($prognoz[1]->TNight, 1), '2'=>$prognoz[1]->Wind->Speed, '3'=>round($req1['pressure']/1.334, 2), '4'=>($ids[$req1['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req2['dt']), '0'=>round($prognoz[2]->TDay, 1), '1'=>round($prognoz[2]->TNight, 1), '2'=>$prognoz[2]->Wind->Speed, '3'=>round($req2['pressure']/1.334, 2), '4'=>($ids[$req2['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req3['dt']), '0'=>round($prognoz[3]->TDay, 1), '1'=>round($prognoz[3]->TNight, 1), '2'=>$prognoz[3]->Wind->Speed, '3'=>round($req3['pressure']/1.334, 2), '4'=>($ids[$req3['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req4['dt']), '0'=>round($prognoz[4]->TDay, 1), '1'=>round($prognoz[4]->TNight, 1), '2'=>$prognoz[4]->Wind->Speed, '3'=>round($req4['pressure']/1.334, 2), '4'=>($ids[$req4['weather'][0]['id']])), 
        Array('type'=>'json', 'times'=>gmdate("Y-m-d", $req5['dt']), '0'=>round($prognoz[5]->TDay, 1), '1'=>round($prognoz[5]->TNight, 1), '2'=>$prognoz[5]->Wind->Speed, '3'=>round($req5['pressure']/1.334, 2), '4'=>($ids[$req5['weather'][0]['id']]))
    ));
    echo(json_encode($ret));
}
//var_dump($req);
?>