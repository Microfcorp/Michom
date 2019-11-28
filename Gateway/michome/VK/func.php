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
                        array(
                            'action' => array(
                                "type" => "text",
                                "payload" => array(
                                    "button" => "1"
                                ),
                                "label" => "Влажность в комнате"
                            ),
                            'color' => 'primary'
                        ),
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
                    array(
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
                    ),
                ),
            ))
        );
 
        $get_params = http_build_query($request_params);
 
        file_get_contents('https://api.vk.com/method/messages.send?' . $get_params);      

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
function Michome_GetPrognoz($d){ 
	//return str_replace(file_get_contents("http://localhost/michome/api/getprognoz.php"), "<br />", " ");
    return file_get_contents("http://localhost/michome/api/getprognoz.php?type=VK&d=".$d);
}
?>