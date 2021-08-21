<?php

namespace Model\Manager;

require_once ROOT_PATH . '/Model/Manager/ManagerBase.inc';
require_once ROOT_PATH . '/Model/User.inc';

/**
 * Description of UserManager
 *
 * @author bruno
 */
class UserManager extends \Model\Manager\ManagerBase {

    protected function getData() {
        $aData = [];
        $aData['codigo'] = isset($_POST['codigo']) ? $_POST['codigo'] : null;
        $aData['nome'] = isset($_POST['nome']) ? $_POST['nome'] : null;
        $aData['dataCadastro'] = isset($_POST['dataCadastro']) ? $_POST['dataCadastro'] : null;
        $aData['dataNascimento'] = isset($_POST['dataNascimento']) ? $_POST['dataNascimento'] : null;
        $aData['documento'] = isset($_POST['documento']) ? $_POST['documento'] : null;
        $aData['telefone'] = isset($_POST['telefone']) ? $_POST['telefone'] : null;
        $aData['email'] = isset($_POST['email']) ? $_POST['email'] : null;
        return $aData;
    }

    protected function doLoadModel() {
        $oUser = new \Model\User();
        $oUser->loadFromData($this->getData());
        return $oUser;
    }

    public function create() {
        $oUser = $this->doLoadModel();
        return ResponseManager::createSucessResponse(json_encode($oUser->create()));
    }

    public function delete() {
        
    }

    public function search() {
        
    }

    public function searchAll() {
        $oUser = new \Model\User();
        return ResponseManager::createSucessResponse($oUser->searchAll());
    }

    public function update() {
        
    }

    public function getPath() {
        return 'user';
    }

}
