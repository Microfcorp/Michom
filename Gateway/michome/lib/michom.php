<?php
//require_once("/var/www/html/site/mysql.php");
require_once("_timeins.php");
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
}
?>