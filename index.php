<?php

define('ROOT_PATH', dirname(__FILE__));

function catchException(Exception $ex) {
    var_dump($ex->getTrace());
}

set_error_handler('catchException', 0);


var_dump($_GET);
$sData = $_GET['data'];
//die();
//$operation = $_GET['op'];

$oManager = false;
switch ($sData) {
    case 'user':
        require_once ROOT_PATH . '/Model/Manager/UserManager.inc';
        $oManager = new \Model\Manager\UserManager();
        break;
    case 'info':
        phpinfo();
        break;
}


if ($oManager) {
    switch ($operation) {
        case 'create':
            $oManager->create();
            break;
    }
}