<?
header('Access-Control-Allow-Origin: *');
include_once("/var/www/html/site/mysql.php");

$form = "<select name='select' id='select'>";

    $results = mysqli_query($link, "SELECT DISTINCT ip FROM michom");	
	
    while($row = $results->fetch_assoc()) {
	  if($row['ip'] != ""){
       $form .= "<option selected value='".$row['ip']."'>".$row['ip']."</option>";
	  }
    }

	$form .= "</select>";
	
print_r ($form);
?>