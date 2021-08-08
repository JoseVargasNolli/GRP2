<?php

namespace Model;

class User extends \ModelDba {

    private $codigo;
    private $nome;
    private $dataCadastro;
    private $dataNascimento;
    private $documento;
    private $telefone;
    private $email;

    protected function getTableName() {
        return 'user';
    }

    protected function getSchemaName() {
        return 'system';
    }

    protected function getPk() {
        return [$this->getColuna('codigo')];
    }

    protected function getColumns() {
        return [
            new ColumnInteger('codigo', 'codigo'),
            new ColumnVarchar('nome', 'nome', 400),
            new ColumnDate('dataCadastro', 'dataCadastro'),
            new ColumnDate('dataNascimento', 'dataNascimento'),
            new ColumnVarchar('documento', 'documento', 100),
            new ColumnVarchar('telefone', 'telefone', 20),
            new ColumnVarchar('email', 'email', 100),
        ];
    }

    function getCodigo() {
        return $this->codigo;
    }

    function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }

    function getNome() {
        return $this->nome;
    }

    function setNome($nome): void {
        $this->nome = $nome;
    }

    function getDataCadastro() {
        return $this->dataCadastro;
    }

    function setDataCadastro($dataCadastro): void {
        $this->dataCadastro = $dataCadastro;
    }

    function getDataNascimento() {
        return $this->dataNascimento;
    }

    function setDataNascimento($dataNascimento): void {
        $this->dataNascimento = $dataNascimento;
    }

    function getDocumento() {
        return $this->documento;
    }

    function setDocumento($documento): void {
        $this->documento = $documento;
    }

    function getTelefone() {
        return $this->telefone;
    }

    function setTelefone($telefone): void {
        $this->telefone = $telefone;
    }

    function getEmail() {
        return $this->email;
    }

    function setEmail($email): void {
        $this->email = $email;
    }

}
