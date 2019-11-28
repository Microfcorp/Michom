<?php 
function _AllModuleInfo(){
    return [new ModuleInfo('termometr','termometr_okno','Модуль уличного термометра',[]),
            new ModuleInfo('Informetr','Informetr_Pogoda','Модуль информетра',[['onlight','Включить подсветку'],['offlight','Выключить подсветку'],['test','Тест системы']]),
            new ModuleInfo('msinfoo','sborinfo_tv','Модуль сбора информации',[]),
            new ModuleInfo('hdc1080','hdc1080_garadze','Модуль гаражной метеостанции',[]),
            new ModuleInfo('StudioLight','StudioLight_Main','Модуль объемного освещения',[])
           ];
}

function _GetModule($id){
    foreach(_AllModuleInfo() as $tmp){
        if($tmp->ID == $id)
            return $tmp;
    }
    return null;
}

function _GetSettings($link, $ip){
    $results = mysqli_query($link, "SELECT setting FROM modules WHERE ip = '$ip'");
    while($row = $results->fetch_assoc()) {
        return $row['setting'];
    }   
}

function _GetModulesIP($link){
    $retur = [];
    $results = mysqli_query($link, "SELECT ip FROM modules");
    while($row = $results->fetch_assoc()) {
        if($row['ip'] != "" & $row['ip'] != "localhost"){
            $retur[] = $row['ip'];
        }
    }        
    return $retur;
}

function _GetModules($rete, $API){
    $ret = [];    
    foreach($rete as $tmp){
        $ret[] = new Module($tmp, $API);
    }
    return $ret;
}

class ModuleInfo
{
    public $Type;
    public $ID;
    public $Descreption;
    public $URL;
    
    public function __construct($Type, $ID, $Descreption, $URL) {
       $baseURL = [['refresh','Обновить данные'],['restart','Перезагрузить']];
       $this->Type = $Type;
       $this->ID = $ID;
       $this->Descreption = $Descreption;
       $this->URL = array_merge($URL, $baseURL);
    }
}

class Module{
    
    public $IP;
    public $RSSI;
    public $ModuleInfo;
    public $IsOnline;
    public $PosledDate;
    
    public function __construct($ip, $API) {
       $this->IP = $ip;
       
       $ch = curl_init();
       curl_setopt($ch, CURLOPT_URL, 'http://'.$ip . "/getmoduleinfo");
       curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
       curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT_MS, 800);
       curl_setopt ($ch, CURLOPT_TIMEOUT_MS, 800);
       
       $m = @curl_exec($ch);

       if($m === FALSE){
           $this->IsOnline = FALSE;
           $this->PosledDate = $API->GetPosledData($ip)->Date;
           //echo $ip;
           //var_dump($API->GetDateDevice($ip)['date']);
       }
       else{
           if($m != 'Not found'){
               $mod = explode('/n', $m);   
                //var_dump($mod);
               $this->RSSI = $mod[2];
               $this->ModuleInfo = _GetModule($mod[0]);
               $this->IsOnline = TRUE;
               $this->PosledDate = $API->GetPosledData($ip)->Date;
           }          
       }
    }
}
?>