<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/Connection.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnDate.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnVarchar.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnInteger.inc';
require_once ROOT_PATH . '/Model/Dba/ColumnBoolean.inc';

abstract class ModelDba {

    private $attribute;
    private $colunas;
    private $loaded = false;

    public function __construct() {
        $this->attribute = [];
        $this->colunas = [];
        foreach ($this->getInstanceColumns() as $oColumnDba) {
            $this->colunas[strtolower($oColumnDba->getModelName())] = $oColumnDba;
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
        $sName = strtolower($sName);
        if (!isset($this->colunas[$sName])) {
            return false;
//            throw new \Exception('Erro não esperado, contate o suporte (' . $sName . ')');
        }
        return $this->colunas[$sName];
    }

    public function refresh() {
        $aData = new \Model\Dba\QueryIterator($this->getSqlRefresh());
        foreach ($aData as $aLinha) {
            $this->loadFromData($aLinha);
            var_dump($aLinha);
            $this->setLoaded(true);
        }
        $aData->end();

        if ($this->getLoaded()){
            return false;
        }
        return $this->toJson();
    }

    public function searchAll() {
        $aData = new \Model\Dba\QueryIterator($this->getSqlSearch());

        $aModels = [];
        foreach ($aData as $aLinha) {
            $oClone = new $this;
            $oClone->loadFromData($aLinha);
            $oClone->setLoaded(true);
            var_dump($aLinha);
            $aModels[] = $oClone->toJson();
        }
        $aData->end();
        return json_encode($aModels);
    }

    private function getSqlSearch() {
        $aColumns = [];
        foreach ($this->getColumns() as /** @var ColumnDba $oColuna */ $oColuna) {
            $aColumns[$sColuna] = $sColuna = $oColuna->getDbaName();
        }
        return 'SELECT ' . join(',', $aColumns) . '  FROM ' . $this->getSchemaName() . '.' . $this->getTableName();
    }

    public function create() {
        $oConnection = new Connection();
        $oConnection->begin();
        $bSucess = $oConnection->execute($this->getSqlInsert());
        $aData = pg_fetch_array($bSucess);
        $this->loadFromData($aData);
        $oConnection->commit();
        return ($this->toJson());
    }

    public function delete() {
        $oConnection = new Connection();
        $oConnection->begin();
        $bSucess = $oConnection->execute($this->getSqlDelete());
        $oConnection->commit();
        return $bSucess;
    }

    protected function getSqlDelete() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();
        list($aColumns, $aValues) = $this->getValuesTratados($this->getPk());
        $aCondicao = [];
        foreach ($aColumns as $sKey => $sColumn) {
            $aCondicao[] = $sColumn . ' = ' . $aValues[$sKey];
        }
        return sprintf('DELETE FROM %s.%s WHERE %s', $sSchema, $sTable, join(' AND ', $aCondicao));
    }

    protected function getSqlRefresh() {
        $sTable = $this->getTableName();
        $sSchema = $this->getSchemaName();
        list($aColumns, $aValues) = $this->getValuesTratados($this->getPk());
        $aCondicao = [];
        foreach ($aColumns as $sKey => $sColumn) {
            $aCondicao[] = $sColumn . ' = ' . $aValues[$sKey];
        }
        return sprintf('SELECT * FROM %s.%s WHERE %s', $sSchema, $sTable, join(' AND ', $aCondicao));
    }

    private function getValuesTratados($aColumnLoad = false) {
        if (!$aColumnLoad) {
            $aColumnLoad = $this->getColumns();
        }
        $aColumns = [];
        $aValues = [];
        foreach ($aColumnLoad as /** @var ColumnDba $oColuna */ $oColuna) {
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
        $sSql = 'INSERT INTO %tabela% (' . join(',', $aColumns) . ') VALUES (' . join(',', $aValues) . ') RETURNING *';
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
                    $this->setAttribute($oColuna->getModelName(), $xValue);
                }
            }
        }
        $this->getValuesTratados();
    }

    public function toJson() {
        $Json = $this->attribute;
        return $Json;
    }

    function getLoaded() {
        return $this->loaded;
    }

    function setLoaded($loaded): void {
        $this->loaded = $loaded;
    }

}
