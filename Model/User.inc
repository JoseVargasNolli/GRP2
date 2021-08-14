<?php

namespace Model;

require_once ROOT_PATH . '/Model/Dba/ColumnDate.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnVarchar.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnInteger.inc';
require_once ROOT_PATH . '/Model/Dba/ModelDba.inc';

class User extends Dba\ModelDba {

    protected function getTableName() {
        return 'user';
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
            new Dba\ColumnDate('dataNascimento', 'dataNascimento'),
            new Dba\ColumnVarchar('documento', 'documento', 100),
            new Dba\ColumnVarchar('telefone', 'telefone', 20),
            new Dba\ColumnVarchar('email', 'email', 100),
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

    function getDataNascimento() {
        return $this->getAttribute('dataNascimento');
    }

    function setDataNascimento($dataNascimento): void {
        $this->setAttribute('dataNascimento', $dataNascimento);
    }

    function getDocumento() {
        return $this->getAttribute('documento');
    }

    function setDocumento($documento): void {
        $this->setAttribute('documento', $documento);
    }

    function getTelefone() {
        return $this->getAttribute('telefone');
    }

    function setTelefone($telefone): void {
        $this->setAttribute('telefone', $telefone);
    }

    function getEmail() {
        return $this->getAttribute('email');
    }

    function setEmail($email): void {
        $this->setAttribute('email', $email);
    }

}
