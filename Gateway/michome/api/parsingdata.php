<?
function parsing($data, $param){
	
	$json = json_encode($data);
	
	return $json->{$param};
}

?> 