<?php

function _GetPosledData($link, $ip){
    $results = mysqli_query($link, "SELECT * FROM michom WHERE `ip` = '$ip' ORDER BY `id` DESC LIMIT 1");
    
    while($row = $results->fetch_assoc()) {
        if($row['id'] != "")
            return new BDData($row['id'], $row['ip'], $row['type'], $row['data'], $row['temp'], $row['humm'], $row['dawlen'], $row['visota'], $row['date'], $link);
    }
    
    $results = mysqli_query($link, "SELECT * FROM logging WHERE `ip` = '$ip' ORDER BY `id` DESC LIMIT 1");
    
    while($row = $results->fetch_assoc()) {
        if($row['id'] != "")
            return new BDLogData($row['id'], $row['ip'], $row['type'], $row['rssi'], $row['log'], $row['date'], $link);
    }
    
    return new BDLogData('0','','','','','', $link);
}

function _GetFromEndData($link, $ip, $count){
    $results = mysqli_query($link, "SELECT * FROM michom WHERE `ip` = '$ip' ORDER BY `id` DESC LIMIT ".$count);
    
    $ret =[];
    
    while($row = $results->fetch_assoc()) {
        if($row['id'] != "")
            $ret[] = new BDData($row['id'], $row['ip'], $row['type'], $row['data'], $row['temp'], $row['humm'], $row['dawlen'], $row['visota'], $row['date'], $link);
    }
    
    $results = mysqli_query($link, "SELECT * FROM logging WHERE `ip` = '$ip' ORDER BY `id` DESC LIMIT ".$count);
    
    while($row = $results->fetch_assoc()) {
        if($row['id'] != "")
            $ret[] = new BDLogData($row['id'], $row['ip'], $row['type'], $row['rssi'], $row['log'], $row['date'], $link);
    }
    
    if(count($ret) == 0)
        $ret[] = new BDLogData('0','','','','','', $link);
    
    return $ret;
}

function _AddLog($link, $ip, $type, $rssi, $log, $date){
    $guery = "INSERT INTO `logging`(`ip`, `type`, `rssi`, `log`, `date`) VALUES ('$ip', '$type','$rssi','$log','$date')";
    $result = mysqli_query($link, $guery);
}

class BDData
{
    public $ID;
    public $IP;
    public $Type;
    public $Data;
    public $Temp;
    public $Humm;
    public $Dawlen;
    public $Visota;
    public $Date;
    
    public $link;
    
    public function __construct($ID, $IP, $Type, $Data, $Temp, $Humm, $Dawlen, $Visota, $Date, $link) {
       $this->ID = $ID;
       $this->IP = $IP;
       $this->Type = $Type;
       $this->Data = $Data;
       $this->Temp = $Temp;
       $this->Humm = $Humm;
       $this->Dawlen = $Dawlen;
       $this->Visota = $Visota;
       $this->Date = $Date;
       $this->link = $link;
    }
    
    public function Update($key, $data){
        $results = mysqli_query($this->$link, "UPDATE `michom` SET `".$key."`='$data' WHERE `id`=".$this->$ID."");
        return $results;
    }
}

class BDLogData
{
    public $ID;
    public $IP;
    public $Type;
    public $RSSI;
    public $Log;
    public $Date;
    
    public $link;
    
    public function __construct($ID, $IP, $Type, $RSSI, $Log, $Date, $link) {
       $this->ID = $ID;
       $this->IP = $IP;
       $this->Type = $Type;
       $this->RSSI = $RSSI;
       $this->Log = $Log;
       $this->Date = $Date;
       $this->link = $link;       
    }
    
    public function Update($key, $data){
        $results = mysqli_query($this->$link, "UPDATE `logging` SET `".$key."`='$data' WHERE `id`=".$this->$ID."");
        return $results;
    }
}
?>