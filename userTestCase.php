<?php

$_GET = [];
$_GET['data'] = 'user';
$_GET['op'] = 'create';

$_POST = [];
$_POST['codigo']= null;
$_POST['nome'] = 'Pedro Alvares';
$_POST['dataCadastro']= '01/10/2010';
$_POST['dataNascimento'] = '01/01/2000';
$_POST['documento'] = '55555555';
$_POST['telefone'] = '47 992924596';
$_POST['email'] = 'teste@mail.com';


include './index.php';
$_GET['op'] = 'searchAll';
include './index.php';
