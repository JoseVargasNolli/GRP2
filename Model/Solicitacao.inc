<?php

namespace Model;

require_once ROOT_PATH . '/Model/Dba/ColumnDate.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnVarchar.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnInteger.inc';
require_once ROOT_PATH . '/Model/Dba/ModelDba.inc';

class Solicitacao extends Dba\ModelDba {

    protected function getTableName() {
        return 'solicitacao';
    }

    protected function getSchemaName() {
        return 'sistema';
    }

    protected function getPk() {
        return [$this->getColumn('codigo')];
    }

    protected function getInstanceColumns() {
        return [
            (new Dba\ColumnInteger('codigo', 'codigo'))->increment(),
            new Dba\ColumnVarchar('nome', 'nome', 400),
            new Dba\ColumnDate('dataCadastro', 'dataCadastro'),
            new Dba\ColumnText('texto', 'texto'),
            new Dba\ColumnInteger('codigoUsuario', 'codigoUsuario', 100)
        ];
    }

    function getCodigo() {
        return $this->getAttribute('codigo');
    }

    function setCodigo($codigo): void {
        $this->setAttribute('codigo', $codigo);
    }

    function getNome() {
        return $this->getAttribute('nome');
    }

    function setNome($nome): void {
        $this->setAttribute('nome', $nome);
    }

    function getDataCadastro() {
        return $this->getAttribute('dataCadastro');
    }

    function setDataCadastro($dataCadastro): void {
        $this->setAttribute('dataCadastro', $dataCadastro);
    }

    function getTexto() {
        return $this->getAttribute('texto');
    }

    function setTexto($Texto): void {
        $this->setAttribute('texto', $Texto);
    }

    function getCodigoUsuario() {
        return $this->getAttribute('codigoUsuario');
    }

    function setCodigoUsuario($CodigoUsuario): void {
        $this->setAttribute('codigoUsuario', $CodigoUsuario);
    }

}
