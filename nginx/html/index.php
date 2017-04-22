<?php
$json = file_get_contents('php://input');
if(!empty($json)) {
    var_dump(json_decode($json, true));
    file_put_contents('UE4POST.json', $json, LOCK_EX);
}
else {
    $json = file_get_contents('UE4POST.json');
    if(!empty($json)) {
        var_dump(json_decode($json, true));
    }
}
phpinfo();