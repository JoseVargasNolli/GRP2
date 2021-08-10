<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

namespace Model\Manager;

/**
 * Description of Manager
 *
 * @author bruno
 */
abstract class ManagerBase {

    //put your code here

    abstract public function create();

    abstract public function update();

    abstract public function delete();

    abstract public function search();

    abstract public function searchAll();
}
