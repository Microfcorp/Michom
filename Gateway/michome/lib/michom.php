<?php
//require_once("/var/www/html/site/mysql.php");
require_once("_timeins.php");
require_once("_module.php");
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
}
?>