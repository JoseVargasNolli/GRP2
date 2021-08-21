<?php

require_once '../../main.inc';
require_once ROOT_PATH . '/Model/Manager/UserManager.inc';

$xRequest = $_SERVER["REQUEST_METHOD"];
$oManager = new \Model\Manager\UserManager();
$oManager->processRequest($xRequest);

