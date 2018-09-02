<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/BotSet.php"); ?>
<?php include_once("/var/www/html/michome/VK/func.php"); ?>

<?
if (!isset($_REQUEST)) {
    return;
}
 
//Получаем и декодируем уведомление
$data = json_decode(file_get_contents('php://input'));
 
// проверяем secretKey
if(strcmp($data->secret, $secretKey) !== 0 && strcmp($data->type, 'confirmation') !== 0)
    return;
 
    //Если это уведомление для подтверждения адреса сервера...
    if($data->type == 'confirmation'){
        //...отправляем строку для подтверждения адреса
        die($confirmationToken);
	}
 
    //Если это уведомление о новом сообщении...
    elseif($data->type == 'message_new' || $data->type == 'message_edit'){
        //...получаем id его автора
        $userId = $data->object->user_id;
		$body = $data->object->body;
        
		if(mb_strtolower($body) == "привет"){
			MessSend($userId, "Умный дом приветствует тебя",$token);
		}
		elseif(mb_strtolower($body) == "температура на улице" || mb_strtolower($body) == "какая температура на улице"){
			MessSend($userId, "Сейчас на улице ".Michome_GetParam("textultemp","192.168.1.11")."C",$token);
		}
		elseif(mb_strtolower($body) == "температура в комнате" || mb_strtolower($body) == "какая температура в комнате"){			
			MessSend($userId, "Сейчас в комнате ".Michome_GetParam_JsonParse("temper","192.168.1.10")."C",$token);
		}
		elseif(mb_strtolower($body) == "влажность в комнате" || mb_strtolower($body) == "какая влажность в комнате"){			
			MessSend($userId, "Сейчас в комнате ".Michome_GetParam_JsonParse("humm","192.168.1.10")."%",$token);
		}
		elseif(mb_strtolower($body) == "давление в комнате" || mb_strtolower($body) == "какое давление в комнате"){			
			MessSend($userId, "Сейчас ".Michome_GetParam_JsonParse("dawlen","192.168.1.10")." мм.рт",$token);
		}
		elseif(mb_strtolower($body) == "ощущение высоты"){			
			MessSend($userId, "Сейчас прям как на".Michome_GetParam_JsonParse("visota","192.168.1.10")." метрах",$token);
		}
		elseif(mb_strtolower($body) == "прогноз погоды"){			
			MessSend($userId, Michome_Prognoz(),$token);
		}
		elseif(mb_strtolower($body) == "ссылка"){			
			MessSend($userId, "http://91.202.27.167/michome/",$token);
		}
		elseif(mb_strtolower($body) == "время дня" || mb_strtolower($body) == "долготня дня"){			
			MessSend($userId, Michome_DateVrem(),$token);
		}
		elseif(mb_strtolower($body) == "последнее обновление"){			
			MessSend($userId, "Последнее обновление модуля сбора информации было: ".Michome_GetParam("posledob","192.168.1.10"),$token);
		}
		elseif(mb_strtolower($body) == "справка"){			
			MessSend($userId, "Привет! Я бот для удобной навигации в системе умного дома Michom<br>Я понимаю команды:<br>Температура на улице,<br>Температура в комнате,<br>Влажность в комнате,<br>Давление в комнате,<br>Прогноз погоды,<br>Время дня,<br>Ощущение высоты,<br>Последнее обновление,<br>Ссылка",$token);
		}
		elseif(mb_strtolower($body) == "ддос"){			
			MessSend($userId, "Ах-ты Ивашка ДДОСЕР гнедоделанный))",$token);
		}
 
	}
 
    // Если это уведомление о вступлении в группу
    elseif($data->type == 'group_join'){
        //...получаем id нового участника
        $userId = $data->object->user_id;
 
        //затем с помощью users.get получаем данные об авторе
        $userInfo = json_decode(file_get_contents("https://api.vk.com/method/users.get?user_ids={$userId}&v=5.8"));
 
        //и извлекаем из ответа его имя
        $user_name = $userInfo->response[0]->first_name;
 
        //С помощью messages.send и токена сообщества отправляем ответное сообщение
        $request_params = array(
            'message' => "Michom приветствует тебя",
            'user_id' => $userId,
            'access_token' => $token,
            'v' => '5.0'
        );
 
        $get_params = http_build_query($request_params);
 
        file_get_contents('https://api.vk.com/method/messages.send?' . $get_params);
 
	}

echo('ok');
?>