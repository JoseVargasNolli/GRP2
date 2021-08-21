<?php
require_once '../../main.inc';
require_once  '../../Model/Manager/UserManager.inc';

$xRequest = $_SERVER["REQUEST_METHOD"];
$oManager = new \Model\Manager\UserManager();
var_dump($oManager->searchTest(1));

