<?php

namespace Model;

abstract class ModelDba {

    abstract public function getTableName();

    abstract public function getSchemaName();

    abstract public function getColumns();

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

    public function getSqlDelete() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();

        list($aColumns, $aValues) = $this->getValuesTratados();
        return sprintf('INSERT INTO %s.%s (%s) VALUES (%s)', $sTable, $sSchema, join($aColumns, ','), join($aValues, ','));
    }

    private function getValuesTratados() {
        $aColumns = [];
        $aValues = [];
        foreach ($this->getColumns() as /** @var ColumnDba $oColuna */ $oColuna) {
            $aColumns[] = $sColuna = $oColuna->getDbaName();
            $aValues[] = $xValue = $this->getAttribute($oColuna->getModelName());
            $oColuna->isValorValido($xValue);
        }
        return [$aColumns, $aValues];
    }

    public function getSqlInsert() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();

        list($aColumns, $aValues) = $this->getValuesTratados();
        return sprintf('INSERT INTO %s.%s (%s) VALUES (%s)', $sTable, $sSchema, join($aColumns, ','), join($aValues, ','));
    }

    private function getAttribute($sAttributeName) {
        $oReflection = new ReflectionProperty($this, $sAttributeName);
        return $oReflection->getValue();
    }

}
