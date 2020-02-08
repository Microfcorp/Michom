<?php
//require_once("/var/www/html/site/mysql.php");
require_once("_timeins.php");
require_once("_module.php");
require_once("_bddata.php");
require_once("/var/www/html/michome/VK/func.php");
require_once("/var/www/html/site/BotSet.php");
class MichomeAPI
{
    // объявление свойства
    public $Gateway = 'localhost';    
    public $link;
    
    // объявление метода
    public function __construct($Gateway, $link) {
       $this->Gateway = $Gateway;
       $this->link = $link;
    }
    
    public function TimeIns($device = 1, $type, $datee = "") {
       return _TimeIns($this->link, $device, $type, $datee);
    }
    
    public function SendCmd($device, $cmd, $timeout=2000) {
       $ch = curl_init();
       curl_setopt($ch, CURLOPT_URL, 'http://'.$device.'/'.$cmd);
       curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
       curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT_MS, $timeout);
       curl_setopt ($ch, CURLOPT_TIMEOUT_MS, $timeout);
       $m = @curl_exec($ch);
       curl_close($ch);
       
       if($m === FALSE)
           return "Ошибка соеденения с модулем";
       else
           return $m;
    }
    
    public function GetModuleInfo() {
       return _AllModuleInfo();
    }
    public function GetModulesIP() {
       return _GetModulesIP($this->link);
    }
    public function GetModules($ip) {
       return _GetModules($ip, $this);
    }
    public function GetAllModules() {
       return _GetModules($this->GetModulesIP(), $this);
    }
    public function GetSettings($ip) {
       return _GetSettings($this->link, $ip);
    }
    
    public function GetPosledData($ip){
       return _GetPosledData($this->link, $ip);
    }
    
    public function SendNotification($text, $group){
        global $token;
       $results = mysqli_query($this->link, "SELECT `ID` FROM `UsersVK` WHERE `Enable`=1 AND `Type` = '".$group."'");
       while($row = $results->fetch_assoc()) {
            MessSend($row['ID'], $text, $token);
       }  
    }
    
    public function GetFromEndData($ip, $count){
       return _GetFromEndData($this->link, $ip, $count);
    }
    
    public function AddLog($ip, $type, $rssi, $log, $date){
       return _AddLog($this->link, $ip, $type, $rssi, $log, $date);
    }
    
    public function MaxMinTemper($ip, $date = 1){
       return _MaxMinTemper($this->link, $ip, $date);
    }
    
    public function GetSettingsFromType($type){
        return _GetSettingsFromType($this->link, $type);
    }
    
    public function GetTemperatureDiap($device = 1, $type, $datee = ""){
        $devicex = ($device != 1) ? ("`ip`='".$device."'") : 1;
        
        if($datee != ""){
            $dates = $datee;
            $req = $this->TimeIns($device, 'diap', $datee);
            //$req = file_get_contents("http://".$_SERVER['HTTP_HOST']."/michome/api/timeins.php?device=".$_GET['device']."&type=selday&date=".substr($dates, 0, -6));		
            $results = mysqli_query($this->link, "SELECT * FROM `michom` WHERE `id` >= '".explode(';',$req)[0]."' AND `id` <= '".explode(';',$req)[1]."' AND ".$devicex);
        }
        else{
            $results = mysqli_query($this->link, "SELECT * FROM `michom` WHERE ".$devicex);
        }

        $num = 0;
        //$data[] = [];
        //$date[] = [];
        
        while($row = $results->fetch_assoc()) {
            $data[] = intval($row['temp']);
            $date[] = $row['date'];
            $num = $num + 1;
        }
        $cart = array(
          "name" => "getdata",
          "col" => $num,
          "device" => $device,
          "data" => $data,
          "date" => $date
        );
        return $cart;
    }
    
    public function GetDateDevice($device = 1){
        $devicex = ($device != 1) ? ("`ip`='".$device."'") : 1;
        $num = 0;
        $date[] = [];
        $date[] = 'никого';
         
        $results = mysqli_query($this->link, "SELECT * FROM `logging` WHERE ".$devicex);
                         
        while($row = $results->fetch_assoc()) {
            $date[] = $row['date'];
            $num = $num + 1;
        }
        
        $results1 = mysqli_query($this->link, "SELECT * FROM `michom` WHERE ".$devicex);
                       
        while($row1 = $results1->fetch_assoc()) {
            $date[] = $row1['date'];
            $num = $num + 1;
        }     
        $cart = array(
          "name" => "getdata",
          "col" => $num,
          "device" => $device,
          "date" => $date
        );
        return $cart;
    }
    
    public function GetConstant($strl){
        $str = $strl;
        //^rm_192.168.1.11_Temp;
        while(IsStr($str, "^rm")){
            $expl = substr($str, strpos($str, "^rm")+4, (strpos($str, ";") - (strpos($str, "^rm")+4)));     
            $rd = $this->GetPosledData(explode('_', $expl)[0])->GetFromName(explode('_', $expl)[1]);
            $rd = str_replace("_","-", $rd);
            $str = str_replace("^rm_".$expl.";", $rd, $str);      
        }              
        return $str;
    }
    public function GetButton($strl, $m, $p, $c){
        $str = $strl;
        //^bt_192.168.1.34_1_1_1;
        while(IsStr($str, "^bt")){
            $expl = substr($str, strpos($str, "^bt")+4, (strpos($str, ";") - (strpos($str, "^bt")+4)));
            
            if(count(explode('_', $expl)) == 4) $fullif = '1';
            elseif(count(explode('_', $expl)) == 2) $fullif = '0';
            elseif(count(explode('_', $expl)) == 3) $fullif = '3';
            else $fullif = '2';
            
            $md = explode('_', $expl)[0];                                   
                       
            if($fullif == '1'){
                $pi = explode('_', $expl)[1];
                $co = explode('_', $expl)[2];           
                if($m == $md & $pi == $p & $co == $c) $rd = '1';
                else $rd = '0';                   
                $rd = "^if_".$rd."==".explode('_', $expl)[3].";";
            }
            elseif($fullif == '3'){
                $pi = explode('_', $expl)[1];
                $co = explode('_', $expl)[2];           
                if($m == $md & $pi == $p & $co == $c) $rd = '1';
                else $rd = '0';                   
                $rd = "^if_".$rd."==1;";
            }
            elseif($fullif == '0'){
                $pi = explode('_', $expl)[1];
                if($m == $md & $pi == $p) $rd = '1';
                else $rd = '0';                   
                $rd = "^if_".$rd."==1;";
            }
            else{
                if($m == $md) $rd = '1';
                else $rd = '0';                   
                $rd = "^if_".$rd."==1;";
            }          
            
            $str = str_replace("^bt_".$expl.";", $rd, $str);      
        }
        return $str;
    }
    public function GetIFs($strl, $enb){
        $Name = $strl;
        $enable = $enb;
        if($enb == '0') return [$Name, $enable];
        while(IsStr($Name, "^if")){
            $expl = substr($Name, strpos($Name, "^if")+4, (strpos($Name, ";") - (strpos($Name, "^if")+4))); 
            if(IsStr($expl, "<")){  if(doubleval(preg_replace("/[^-0-9\.]/","",explode('<', $expl)[0])) > doubleval(preg_replace("/[^-0-9\.]/","",explode('<', $expl)[1]))){ $enable = "0"; echo "1>2 ";}}
            elseif(IsStr($expl, ">")){ if(doubleval(preg_replace("/[^-0-9\.]/","",explode('>', $expl)[0])) < doubleval(preg_replace("/[^-0-9\.]/","",explode('>', $expl)[1]))){ $enable = "0"; echo "1<2 ";}}
            elseif(IsStr($expl, "<=")){ if(doubleval(preg_replace("/[^-0-9\.]/","",explode('<=', $expl)[0])) >= doubleval(preg_replace("/[^-0-9\.]/","",explode('<=', $expl)[1]))){ $enable = "0"; echo "1>=2 ";}}
            elseif(IsStr($expl, ">=")){ if(doubleval(preg_replace("/[^-0-9\.]/","",explode('>=', $expl)[0])) <= doubleval(preg_replace("/[^-0-9\.]/","",explode('>=', $expl)[1]))){ $enable = "0"; echo "1<=2 ";}}
            elseif(IsStr($expl, "==")){ if(doubleval(preg_replace("/[^-0-9\.]/","",explode('==', $expl)[0])) != doubleval(preg_replace("/[^-0-9\.]/","",explode('==', $expl)[1]))){ $enable = "0"; echo "1!=2 ";}}
            elseif(IsStr($expl, "!=")){ if(doubleval(preg_replace("/[^-0-9\.]/","",explode('!=', $expl)[0])) == doubleval(preg_replace("/[^-0-9\.]/","",explode('!=', $expl)[1]))){ $enable = "0"; echo "1==2 ";}}
            $Name = str_replace("^if_".$expl.";", "", $Name);
        }
        return [$Name, $enable];
    }
    public function GetNotification($strl){
        $str = $strl;
        //^sn_all_Привет, мир;
        while(IsStr($str, "^sn")){
            $expl = substr($str, strpos($str, "^sn")+4, (strpos($str, ";") - (strpos($str, "^sn")+4)));     
            $text = explode('_', $expl)[1];
            $group = explode('_', $expl)[0];
            $this->SendNotification($text, $group);
            $str = str_replace("^sn_".$expl.";", "", $str);
            //echo "SendNotification ";
        }
        return $str;
    }
}
function IsStr($str, $search){
    if(strpos($str, $search) !== FALSE) return true;
    else return false;
}
?>