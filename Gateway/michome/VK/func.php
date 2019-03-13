<?
function MessSend($peer_id, $message,$token){
	$request_params = array(
            'message' => $message,
            'user_id' => $peer_id,
            'access_token' => $token,
            'v' => '5.80'
        );
 
        $get_params = http_build_query($request_params);
 
        file_get_contents('https://api.vk.com/method/messages.send?' . $get_params);
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
	return file_get_contents("http://91.202.27.167/michome/api/getdata.php?cmd=".$cmd."&device=".$device);
}
function Michome_SetCmd($cmd,$device){
	return file_get_contents("http://91.202.27.167/michome/api/setcmd.php?cmd=".$cmd."&device=".$device);
}
function Michome_GetParam_JsonParse($cmd,$device){
	$jsond = json_decode(Michome_GetParam($cmd,$device));
	
	return $jsond->data[$jsond->col];
}
function Michome_Prognoz(){	
	return file_get_contents("http://91.202.27.167/michome/prognoz.php");
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
function Michome_GetPrognoz($cmd,$device){
	return file_get_contents("http://91.202.27.167/michome/api/getprognoz.php");
}
?>