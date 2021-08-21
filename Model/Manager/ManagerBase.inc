<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

namespace Model\Manager;

require_once ROOT_PATH . '/Model/Manager/ResponseManager.inc';

/**
 * Description of Manager
 *
 * @author bruno
 */
abstract class ManagerBase {

    private $param;

    public function __construct() {
        define('URL', parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH));
        define('URL_PATH', explode('/', URL));
        
        if (URL_PATH[3] != $this->getPath()) {
            $this->notFound();
        }
        if (!isset(URL_PATH[4])) {
            $this->param = (int) URL_PATH[4];
        }
    }

    //put your code here

    abstract public function create();

    abstract public function update();

    abstract public function delete();

    abstract public function search();

    abstract public function searchAll();

    abstract public function getPath();

    function getParam() {
        return $this->param;
    }

    function processRequest($xRequest) {
        $xResponse = false;
        switch ($xRequest) {
            case 'GET':
                if ($this->getParam()) {
                    $xResponse = $this->search();
                } else {
                    $xResponse = $this->searchAll();
                }
                break;
            case 'POST':
                $xResponse = $this->create();
                break;
            case 'PUT':
                $xResponse = $this->update();
                break;
            case 'DELETE':
                $xResponse = $this->delete();
                break;
            default:
                $this->notFound();
                break;
        }
        header($xResponse['header']);
        if ($xResponse['body']) {
            echo $xResponse['body'];
        }
    }

    public function notFound() {
//        header(ResponseManager::createNotFoundResponse()['header']);
        exit();
    }

}
