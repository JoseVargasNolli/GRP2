<?php

define('ROOT_PATH', dirname(__FILE__));
define('DEBUG', true);

//function catchException(Exception $ex) {
//    var_dump($ex->getTrace());
//}
//
//set_error_handler('catchException', 0);


$sData = $_GET['data'];
$operation = $_GET['op'];

$oManager = false;
switch ($sData) {
    case 'user':
        require_once ROOT_PATH . '/Model/Manager/UserManager.inc';
        $oManager = new \Model\Manager\UserManager();
        break;
    case 'solicitacao':
        require_once ROOT_PATH . '/Model/Manager/SolicitacaoManager.inc';
        $oManager = new \Model\Manager\SolicitacaoManager();
        break;
    case 'info':
        phpinfo();
        break;
}


if ($oManager) {
    switch ($operation) {
        case 'create':
            $xResult = $oManager->create();
            break;
        case 'searchAll':
            $aDados = $oManager->searchAll();
            $aData = [];
            foreach ($aDados as $oModel) {
                $aData[] = ($oModel->toJson());
            }
            $xResult = ($aData);
            break;
    }
}

echo json_encode($xResult);
