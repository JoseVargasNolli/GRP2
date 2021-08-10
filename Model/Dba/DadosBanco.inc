<?php

namespace \DataBase;

class DadosBanco {

    private static $instance;
    private $server;
    private $port;
    private $user;
    private $password;
    private $banco;

    public static function getInstance() {
        if (!isset(self::$instance)) {
            self::$instance = new self();
        }
        return self::$instance;
    }

    private function __construct() {
        $this->server = '192.168.2.2';
        $this->port = 2255;
        $this->user = 'postgres';
        $this->password = 'admin';
        $this->banco = 'database';
    }

    function getServer() {
        return $this->server;
    }

    function getPorta() {
        return $this->port;
    }

    function getUser() {
        return $this->user;
    }

    function getPassword() {
        return $this->password;
    }

    function getBanco() {
        return $this->banco;
    }

}
