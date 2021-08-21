<?php

define('ROOT_PATH', dirname(__FILE__));
header('Acess-Control-Allow-Origin: *');
//header('Content-Type: application/json; charset=UTF-8');
header('Acess-Control-Allow-Methods: OPTIONS,GET,POST,PUT,DELETE');
header('Acess-Control-Max-Age: 3600');
header('Acess-Control-Allow-Headers: Content-Type, Acess-Control-Allow-Headers, Authorization, X-Requested-With');