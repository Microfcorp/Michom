<?php include_once("/var/www/html/site/mysql.php"); ?>
<?php include_once("/var/www/html/site/secur.php"); ?>
<?php require_once("/var/www/html/michome/lib/michom.php"); ?>
<?
    header("Michome-Page: Module-Configuration");
    
    $API = new MichomeAPI('192.168.1.42', $link); 
    
	//$ModulesInfo = $API->GetModuleInfo();
    $Modules = $API->GetAllModules();
    //$Modules = $API->GetModules(['192.168.1.13']);
    //echo ($API->GetDateDevice('192.168.1.11')['date'][count($API->GetDateDevice('192.168.1.11')['date'])-1]);
    function random_html_color()
    {
        return sprintf( '#%02X%02X%02X', rand(100, 255), rand(100, 255), rand(100, 255) );
    }
?>
<!Doctype html>
<html>
<head>
<title>Управление Michome</title>
<style>
dialog::backdrop {
  background-color: rgba(0, 0, 0, 0.8);
}
</style>
</head>

<body>
	<?php include_once("/var/www/html/site/verh.php"); ?>
	<H1 style="text-align: center; color:red;">Управление Michome. Модули</H1>	
	<script type="text/javascript">
    
	//var caz = document.getElementById("cazestvo").value;
	function createXMLHttp() {
        if (typeof XMLHttpRequest != "undefined") { // для браузеров аля Mozilla
            return new XMLHttpRequest();
        } else if (window.ActiveXObject) { // для Internet Explorer (all versions)
            var aVersions = [
                "MSXML2.XMLHttp.5.0",
                "MSXML2.XMLHttp.4.0",
                "MSXML2.XMLHttp.3.0",
                "MSXML2.XMLHttp",
                "Microsoft.XMLHttp"
            ];
            for (var i = 0; i < aVersions.length; i++) {
                try {
                    var oXmlHttp = new ActiveXObject(aVersions[i]);
                    return oXmlHttp;
                } catch (oError) {}
            }
            throw new Error("Невозможно создать объект XMLHttp.");
        }
    }

// фукнция Автоматической упаковки формы любой сложности
function getRequestBody(oForm) {
    var aParams = new Array();
    for (var i = 0; i < oForm.elements.length; i++) {
        var sParam = encodeURIComponent(oForm.elements[i].name);
        sParam += "=";
        sParam += encodeURIComponent(oForm.elements[i].value);
        aParams.push(sParam);
    }
    return aParams.join("&");
}
// функция Ajax POST
function postAjax(url, oForm, callback) {
    // создаем Объект
    var oXmlHttp = createXMLHttp();
    // получение данных с формы
    var sBody = oForm;
    // подготовка, объявление заголовков
    oXmlHttp.open("POST", url, true);
    oXmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	//oXmlHttp.addHeader("Access-Control-Allow-Origin", "*");
    // описание функции, которая будет вызвана, когда придет ответ от сервера
    oXmlHttp.onreadystatechange = function() {
        if (oXmlHttp.readyState == 4) {
            if (oXmlHttp.status == 200) {
                callback(oXmlHttp.responseText);
            } else {
                callback('error' + oXmlHttp.statusText);
            }
        }
    };
    // отправка запроса, sBody - строка данных с формы
    oXmlHttp.send(sBody);
}

function SendModule(url, data){
    postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ url +'&cmd='+ data.replace( /&/g, "%26" ), "", function(d){alert(d)});
}

var ips = "";

function show(ip){
    postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/getallsetting.php?device='+ ip, "", function(d)
        {
            var table = document.createElement('table');
            var html = '<tbody>';
            for (var i = 0; i < d.split(';').length; i++) {
                html += '<tr><td class="n n|'+i+'">'+d.split(';')[i].split('=')[0]+'</td><td><input class="v v|'+i+'" type="text" value="'+d.split(';')[i].split('=')[1]+'"></input></td></tr>';
            }
            table.innerHTML = html + '</tbody>';
            tables.innerHTML = table.outerHTML;
        }
    );
    ips = ip;
    dialog.showModal();
}

function save(){
    var names = document.getElementsByClassName('n');
    var values = document.getElementsByClassName('v');
    
    var result = "";
    
    for (var i = 0; i < names.length; i++) {

        var v1 = names[i].innerHTML;
        var v2 = values[i].value;
        result += (v1 + "=" + v2 + ";");
    }
    result = result.substring(0, result.length - 1)
    
    postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/saveallsettings.php?device='+ ips + '&d='+result, "", function(d)
        {
           if(d!="OK"){
               alert("Ошибка");
           }
        }
    );
    
    postAjax('http://'+ips+'/setsettings?s='+ result, "", function(da){});   
    
    dialog.close();
}

function closed(){
    dialog.close();
}
</script>
	
<div id="main">
    <table style="border-color: aqua; border-style: none;" border="1" width="100%" cellpadding="8">
        <tbody>
            <?php
                foreach($Modules as $tmp){
                    if($tmp->IsOnline){
                        echo "<tr height=\"130px\" style=\"margin-left: 5px; width: 100vw; background-color: ".random_html_color().";\">";
                            echo "<td>";
                                echo "<p>___".$tmp->IP."___</p><p>".$tmp->ModuleInfo->Descreption."</p>";
                            echo "</td>";
                            echo "<td>";
                                echo "<p>Модуль в сети </p><p>Уровень связи: ".$tmp->RSSI."</p> <p>Поледнее соеденение было установленно ".$tmp->PosledDate."</p>";
                            echo "</td>";
                            echo "<td>";
                                echo "Действия: <br />";
                                foreach($tmp->ModuleInfo->URL as $mdu){
                                    echo "<p><a href='#' onclick='SendModule(\"".$tmp->IP."\",\"".$mdu[0]."\")'>".$mdu[1]."</a></p>";
                                }
                                echo "<button onclick='show(\"".$tmp->IP."\")'>Открыть настройки</button>";
                            echo "</td>";
                        echo "</tr>";
                    }
                    else{
                        echo "<tr height=\"130px\" style=\"margin-left: 5px; width: 100vw; background-color: ".random_html_color().";\">";
                            echo "<td>";
                                echo "<p>___".$tmp->IP."___</p>";
                            echo "</td>";
                            echo "<td>";
                                echo "<p>Модуль не в сети </p><p>Последний раз был в сети: ".$tmp->PosledDate."</p>";
                            echo "</td>";
                            echo "<td>";
                                echo "Действия не доступны";
                            echo "</td>";
                        echo "</tr>";
                    }
                }
            ?>
        </tbody>
    </table>
    
    <dialog id="dialog">
      <div id="tables"></div>
      <button onclick="save()">Сохранить</button>
      <button onclick="closed()">Закрыть</button>
    </dialog>
</div>
    
</body>
</html> 