<?

function MessSend($peer_id, $message,$token){
	$request_params = array(
            'message' => $message,
            'user_id' => $peer_id,
            'access_token' => $token,
            'v' => '5.80',
            'keyboard' => json_encode(array(
                'one_time' => false,
                'buttons' => array(
                    array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Свет на пиано"
                            ),
                            'color' => 'positive'
                        ),
                    ),
                    array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Включить гирлянду"
                            ),
                            'color' => 'positive'
                        ),
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Выключить гирлянду"
                            ),
                            'color' => 'negative'
                        ),
                    ),
                    /*array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Включить ель"
                            ),
                            'color' => 'positive'
                        ),
                        
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Выключить ель"
                            ),
                            'color' => 'negative'
                        ),
                    ),*/
                    array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Включить свет 1"
                            ),
                            'color' => 'positive'
                        ),
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Включить свет 2"
                            ),
                            'color' => 'positive'
                        ),
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Включить свет 3"
                            ),
                            'color' => 'positive'
                        ),
                    ),
                    array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Выключить свет 1"
                            ),
                            'color' => 'negative'
                        ),
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Выключить свет 2"
                            ),
                            'color' => 'negative'
                        ),
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Выключить свет 3"
                            ),
                            'color' => 'negative'
                        ),
                    ),
                    array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Температура на улице"
                            ),
                            'color' => 'primary'
                        ),
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Температура в комнате"
                            ),
                            'color' => 'primary'
                        ),
                    ),
                    array(
                        /*array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Влажность в комнате"
                            ),
                            'color' => 'primary'
                        ),*/
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Давление в комнате"
                            ),
                            'color' => 'primary'
                        ),
                    ),
                    /*array(
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Прогноз погоды"
                            ),
                            'color' => 'primary'
                        ),                        
                    ),*/
                ),
            ))
        );
 
        $get_params = http_build_query($request_params);
 
        //file_get_contents('https://api.vk.com/method/messages.send?' . $get_params);      

       $ch = curl_init();
       curl_setopt($ch, CURLOPT_URL, 'https://api.vk.com/method/messages.send?' . $get_params);
       curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
       //curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT, 3);
       //curl_setopt ($ch, CURLOPT_TIMEOUT, 3);
       $m = @curl_exec($ch);
       curl_close($ch);

        //var_dump($request_params);
}
function MessSend_Attach($peer_id, $message,$token,$att){
	$request_params = array(
            'message' => $message,
            'user_id' => $peer_id,
            'access_token' => $token,
            'v' => '5.80',
			'attachment' => implode(',', $att)
        );
 
        $get_params = http_build_query($request_params);
 
        file_get_contents('https://api.vk.com/method/messages.send?' . $get_params);
}
function Michome_GetParam($cmd,$device){
	return file_get_contents("http://localhost/michome/api/getdata.php?cmd=".$cmd."&device=".$device);
}
function Michome_SetCmd($cmd,$device){
	return file_get_contents("http://localhost/michome/api/setcmd.php?cmd=".$cmd."&device=".$device);
}
function Michome_GetParam_JsonParse($cmd,$device){
	$jsond = json_decode(Michome_GetParam($cmd,$device));
	
	return $jsond->data[$jsond->col];
}
function Michome_Prognoz(){	
	return file_get_contents("http://localhost/michome/prognoz.php");
}
function Michome_DateVrem(){	
	return ("Время восхода солнца: ".date_sunrise(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3)."<br>Время захода солнца: ".date_sunset(time(),SUNFUNCS_RET_STRING,50.860145, 39.082347, 90+50/60, 3));
}
function Michome_SetLight($p,$s){
	return Michome_SetCmd('setlight?p='.$p.'%26s='.$s,"192.168.1.34");
}
function Michome_SetCharModule($p,$s){
	return Michome_SetCmd('setlight?p='.$p.'%26s='.$s,"192.168.1.12");
}
function Michome_SetHDC1080Module($p){
    if($p == 1)
        return Michome_SetCmd('setlight?s=1',"192.168.1.14");
    else
        return Michome_SetCmd('setlight?s=0',"192.168.1.14");
}
function Michome_GetPrognoz($d){ 
	//return str_replace(file_get_contents("http://localhost/michome/api/getprognoz.php"), "<br />", " ");
    return file_get_contents("http://localhost/michome/api/getprognoz.php?type=VK&d=".$d);
}
function AddNot($id){
    global $link;
    $res = mysqli_query($link, "SELECT `ID` FROM `UsersVK` WHERE `ID` = ".$id);
    $count = mysqli_num_rows($res);
    if($count <= 0)
        mysqli_query($link, "INSERT INTO `UsersVK`(`ID`, `Type`, `Enable`) VALUES ('$id','all','1')");
}
function ChangeNot($id, $group){
    global $link;
    AddNot($id);    
    mysqli_query($link, "UPDATE `UsersVK` SET `Type`='$group' WHERE `ID`=".$id);
}
function RemoveNot($id){
    global $link;
    mysqli_query($link, "DELETE FROM `UsersVK` WHERE `ID`=".$id);
}
?>