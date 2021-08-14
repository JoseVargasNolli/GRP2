<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/Connection.inc';

abstract class ModelDba {

    private $colunas;

    public function __construct() {
        $this->attribute = [];
        $this->colunas = [];
        foreach ($this->getInstanceColumns() as $oColumnDba) {
            $this->colunas[$oColumnDba->getModelName()] = $oColumnDba;
        }
    }

    abstract protected function getPk();

    abstract protected function getInstanceColumns();

    abstract protected function getTableName();

    abstract protected function getSchemaName();

    protected function getColumns() {
        return $this->colunas;
    }

    protected function getColumn($sName) {
        if (!isset($this->colunas[$sName])) {
            throw new \Exception('Erro não esperado, contate o suporte');
        }
        return $this->colunas[$sName];
    }

    public function searchAll() {
        $aData = new \Model\Dba\QueryIterator($this->getSqlSearch());

        $aModels = [];
        foreach ($aData as $aLinha) {
            $oClone = new self();
            $oClone->loadFromData($aLinha);
            $aModels[] = $oClone;
        }
        $aData->end();
        return $aModels;
    }

    private function getSqlSearch() {
        return 'SELECT * FROM ' . $this->getSchemaName() . '.' . $this->getTableName();
    }

    public function create() {
        $oConnection = new Connection();
        $oConnection->begin();
        $bSucess = $oConnection->execute($this->getSqlInsert());
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
            if ($xValue && !is_null($xValue)) {
                $oColuna->isValorValido($xValue);
                $aColumns[$sColuna] = $sColuna = $oColuna->getDbaName();
                $aValues[$sColuna] = $xValue;
            }
        }
        return [$aColumns, $aValues];
    }

    private function getValuesForInsert() {
        list($aColumns, $aValues) = $this->getValuesTratados();
        foreach ($this->getColumns() as /** @var ColumnDba $oColuna */ $oColuna) {
            $sColuna = $oColuna->getModelName();
            $xValue = isset($aValues[$sColuna]) ? $aValues[$sColuna] : null;
            if ($sTratado = $oColuna->getValorTratadoForInsert($xValue)) {
                $aColumns[$sColuna] = $sColuna;
                $aValues[$sColuna] = $sTratado;
            }
        }
        return [$aColumns, $aValues];
    }

    protected function getSqlInsert() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();

        list($aColumns, $aValues) = $this->getValuesForInsert();
        $sSql = 'INSERT INTO %tabela% (' . join(',', $aColumns) . ') VALUES (' . join(',', $aValues) . ')';
        return str_replace('%tabela%', $sSchema . '.' . $sTable, $sSql);
    }

    protected function getAttribute($sAttributeName) {
        return isset($this->attribute[$sAttributeName]) ? $this->attribute[$sAttributeName] : null;
    }

    protected function setAttribute($sAttributeName, $sValue) {
        $this->attribute[$sAttributeName] = $sValue;
    }

    public function loadFromData($aData) {
        foreach ($aData as $sKey => $xValue) {
            if ($xValue) {
                $oColuna = $this->getColumn($sKey);
                if ($oColuna && $xValue) {
                    $this->setAttribute($sKey, $xValue);
                }
            }
        }
        $this->getValuesTratados();
    }

}
