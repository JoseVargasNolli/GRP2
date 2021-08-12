<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/Connection.inc';

abstract class ModelDba {

    private $colunas;

    public function __construct() {
        $this->attribute = [];
        $this->colunas = $this->getInstanceColumns();
    }

    abstract protected function getPk();

    abstract protected function getInstanceColumns();

    abstract protected function getTableName();

    abstract protected function getSchemaName();

    protected function getColumns() {
        return $this->colunas;
    }

    protected function getColumn($sName) {
        if (!isset($this->coluna[$sName])) {
            throw new Exception('Erro não esperado, contate o suporte');
        }
        return $this->coluna[$sName];
    }

    public function create() {
        $oConnection = new Connection();
        $oConnection->begin();
        $oConnection->setSql($this->getSqlInsert());
        $bSucess = $oConnection->execute();
        $oConnection->commit();
        return $bSucess;
    }

    public function delete() {
        $oConnection = new Connection();
        $oConnection->begin();
        $oConnection->setSql($this->getSqlDelete());
        $bSucess = $oConnection->execute();
        $oConnection->commit();
        return $bSucess;
    }

    protected function getSqlDelete() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();

        list($aColumns, $aValues) = $this->getValuesTratados();
        return sprintf('INSERT INTO %s.%s (%s) VALUES (%s)', $sTable, $sSchema, join($aColumns, ','), join($aValues, ','));
    }

    private function getValuesTratados() {
        $aColumns = [];
        $aValues = [];
        foreach ($this->getColumns() as /** @var ColumnDba $oColuna */ $oColuna) {
            $xValue = $this->getAttribute($oColuna->getModelName());
            $oColuna->isValorValido($xValue);
            if ($xValue && !is_null($xValue)) {
                $aColumns[] = $sColuna = $oColuna->getDbaName();
                $aValues[] = $xValue;
            }
        }
        return [$aColumns, $aValues];
    }

    protected function getSqlInsert() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();

        list($aColumns, $aValues) = $this->getValuesTratados();
        return sprintf('INSERT INTO %s.%s (%s) VALUES (%s)', $sTable, $sSchema, join($aColumns, ','), join($aValues, ','));
    }

    protected function getAttribute($sAttributeName) {
        return $this->attribute[$sAttributeName];
    }

    protected function setAttribute($sAttributeName, $sValue) {
        $this->attribute[$sAttributeName] = $sValue;
    }

    public function loadFromData($aData) {
        foreach ($aData as $sKey => $xValue) {
            if ($xValue) {
                $oColuna = $this->getColumn($sKey);
                if ($oColuna) {
                    $this->setAttribute($sKey, $xValue);
                }
            }
        }
        $this->getValuesTratados();
    }

}
