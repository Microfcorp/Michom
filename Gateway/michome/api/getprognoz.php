<?php
$today = date("H");

    if($today > 0 & $today < 12){        
       $req = json_decode(file_get_contents("https://openweathermap.org/data/2.5/forecast/daily/?appid=b6907d289e10d714a6e88b30761fae22&id=514198&units=metric"), true)["list"][0];
    }
    else{
       $req = json_decode(file_get_contents("https://openweathermap.org/data/2.5/forecast/daily/?appid=b6907d289e10d714a6e88b30761fae22&id=514198&units=metric"), true)["list"][1];
    }


    $ids = Array(200=>0,201=>0,202=>0,210=>0,211=>0,212=>0,221=>0,230=>0,231=>0,232=>0,300=>1,301=>1,302=>1,310=>1,311=>1,312=>1,313=>1,314=>1,321=>1,500=>2,501=>2,502=>2,503=>2,504=>2,511=>2,520=>2,521=>2,522=>2,531=>2,600=>3,601=>3,602=>3,611=>3,612=>3,615=>3,616=>3,620=>3,621=>3,622=>3,
    800=>4,801=>5,802=>5,803=>5,804=>5);

    $local = ["Гроза","Мелкий дождик","Дождик","Снежок","Солнечно","Облачно"];    
    
if(empty($_GET['type'])){

    echo("Днём ".$req['temp']['day']."<br />");
    echo("Ночью ".$req['temp']['night']."<br />");
    echo("Ветер ".$req['speed']." m/s"."<br />");
    echo("Давление ".$req['pressure']."<br />");
    echo("Прогноз ".$local[$ids[$req['weather'][0]['id']]]."<br />");
}
else{

    if($today > 21 || $today < 7){
        $b = 0;
    }
    else{
        $b = 1;
    }
    
    $ret = Array('type'=>'json', /*'utime'=>strval(time()),*/ 'dawlen'=>file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/getdata.php?device=192.168.1.10&cmd=textdawlen"), 'temp'=>file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/getdata.php?device=192.168.1.11&cmd=textultemp"), 'time'=>date("H:i:s"), 'd'=>$b, '0'=>$req['temp']['day'], '1'=>$req['temp']['night'], '2'=>$req['speed'], '3'=>$req['pressure'], '4'=>($ids[$req['weather'][0]['id']]));
    exit(json_encode($ret));
}
//var_dump($req);
?>