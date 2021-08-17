<?php

namespace Model\Manager;

require_once ROOT_PATH . '/Model/Manager/ManagerBase.inc';
require_once ROOT_PATH . '/Model/Solicitacao.inc';

/**
 * Description of SolicitacaoManager
 *
 * @author bruno
 */
class SolicitacaoManager extends \Model\Manager\ManagerBase {

    protected function getData() {
        $aData = [];
        $aData['codigo'] = isset($_POST['codigo']) ? $_POST['codigo'] : null;
        $aData['nome'] = isset($_POST['nome']) ? $_POST['nome'] : null;
        $aData['dataCadastro'] = isset($_POST['dataCadastro']) ? $_POST['dataCadastro'] : null;
        $aData['texto'] = isset($_POST['texto']) ? $_POST['texto'] : null;
        $aData['codigoUsuario'] = isset($_POST['codigoUsuario']) ? $_POST['codigoUsuario'] : null;
        return $aData;
    }

    protected function doLoadModel() {
        $oSolicitacao = new \Model\Solicitacao();
        $oSolicitacao->loadFromData($this->getData());
        return $oSolicitacao;
    }

    public function create() {
        $oSolicitacao = $this->doLoadModel();
        return $oSolicitacao->create();
    }

    public function delete() {
        
    }

    public function search() {
        
    }

    public function searchAll() {
        $oSolicitacao = new \Model\Solicitacao();
        return $oSolicitacao->searchAll();
    }

    public function update() {
        
    }

}
