<?php

$_GET = [];
$_GET['data'] = 'solicitacao';
$_GET['op'] = 'create';

$_POST = [];
$_POST['codigo'] = null;
$_POST['nome'] = 'Pedro Alvares';
$_POST['dataCadastro'] = '01/10/2010';
$_POST['texto'] = 'um texto longo mas nem tanto somente para preencher espaco vago neste local vazio e frio do universo';
$_POST['codigoUsuario'] = '1';


include './index.php';
$_GET['op'] = 'searchAll';
include './index.php';
