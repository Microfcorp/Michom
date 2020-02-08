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
    
    function cmp($a, $b)
    {
        return strcmp($b->IsOnline, $a->IsOnline);
    }
    
    function formatFileSize($size) {
    $a = array("B", "KB", "MB", "GB", "TB", "PB");
    $pos = 0;
    while ($size >= 1024) {
        $size /= 1024;
        $pos++;
    }
    return round($size,2)." ".$a[$pos];
}
?>
<!Doctype html>
<html>
	<head>
		<title>Настройки</title>
		<link rel="stylesheet" type="text/css" href="styles/style.css"/>
        <script type="text/javascript" src="/site/MicrofLibrary.js"></script>
		<style>
			dialog::backdrop {
			  background-color: rgba(0, 0, 0, 0.8);
			}
		</style>
        <script type="text/javascript">        
        function SendModule(url, data){
            postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/setcmd.php?device='+ url +'&cmd='+ data.replace( /&/g, "%26" ), "POST", "", function(d){alert(d)});
        }

        var ips = "";

        function show(ip){
            postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/getallsetting.php?device='+ ip, "POST", "", function(d)
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
            
            postAjax('http://<?echo $_SERVER['HTTP_HOST'];?>/michome/api/saveallsettings.php?device='+ ips + '&d='+result, "POST", "", function(d)
                {
                   if(d!="OK"){
                       alert("Ошибка");
                   }
                }
            );
            
            if('<?echo $_SERVER['HTTP_HOST'];?>' == "192.168.1.42")
                postAjax('http://'+ips+'/setsettings?s='+ result, "POST", "", function(da){});   
            else
                SendModule(ips, '/setsettings?s='+ result);
            
            dialog.close();
        }

        function closed(){
            dialog.close();
        }
    </script>
	</head>
	<body>
		<div class = "body_alfa"></div>
		<div class = "body">
			<div class = "title_menu">Управление Michome. Модули</div>
			<div class = "com">
                <?php
                    usort($Modules, "cmp");
                    foreach($Modules as $tmp){
                        if($tmp->IsOnline){
                            echo "<div class = \"components\">";
                                echo "<div class = \"components_alfa\">";
                                    echo "<div class = \"components_title\">".$tmp->IP." - ".$tmp->ModuleInfo->Descreption."</div>";
                                    echo "<div class = \"components_text\"><p style=\"color: green;\">Модуль в сети</p><p>Уровень связи: ".$tmp->RSSI."</p><p>Размер память: ".formatFileSize($tmp->FlashSize)."</p> <p>Поледнее соеденение было установленно <span style=\"left: 3px;\">".$tmp->PosledDate."</span></p>";
                                    foreach($tmp->ModuleInfo->URL as $mdu){
                                        echo "<p><a href='#' onclick='SendModule(\"".$tmp->IP."\",\"".$mdu[0]."\")'>".$mdu[1]."</a></p>";
                                    }
                                    echo "</div>";
                                    echo "<div onclick='show(\"".$tmp->IP."\")' class = \"components_button\"><a href = \"#\"></a></div>";
                                echo "</div>";
                            echo "</div>";
                        }
                        else{                          
                            echo "<div class = \"components\">";
                                echo "<div class = \"components_alfa\">";
                                    echo "<div class = \"components_title\">".$tmp->IP."</div>";
                                    echo "<div class = \"components_text\"><p style=\"color: red;\">Модуль не в сети </p><p>Последний раз был в сети: ".$tmp->PosledDate."</p></div>";                               
                                    echo "<div class = \"components_button\"><a href = \"#\"></a></div>";
                                echo "</div>";
                            echo "</div>";
                        }
                    }				
                ?>
                <!--<div class = "components">
					<div class = "components_alfa">
						<div class = "components_title">192.168.45.201 - Что-то тут интересное...</div>
						<div class = "components_text">А тут брет нести можно, несу и буду нести, а что еще прикажете делать, не знаю я, всю жизнь ерундой занимаемся</div>
						<div class = "components_button"><a href = "#"></a></div>
	
					</div>
				</div>-->
			</div>
		</div>
        
		<?php require_once("/var/www/html/site/verhn.php");?> 
        
        <div>
            <dialog style="padding: 16px; margin: auto;" id="dialog">
              <div id="tables"></div>
              <button onclick="save()">Сохранить</button>
              <button onclick="closed()">Закрыть</button>
            </dialog>
        </div>
	</body>
</html>	