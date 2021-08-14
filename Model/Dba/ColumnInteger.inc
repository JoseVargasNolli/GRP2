<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnDba.inc';

/**
 * Description of ColumnInteger
 *
 * @author bruno
 */
class ColumnInteger extends ColumnDba {

    private $increment = false;

    public function isValorValido($xValorValido, $bThrow = true) {
        $bIsValido = is_integer($xValorValido);
        if (!$bIsValido) {
            if ($bThrow) {
                $this->showExceptionNotSupported();
            }
            return false;
        }
        return true;
    }

    public function increment() {
        $this->increment = true;
        return $this;
    }

    public function getValorTratadoForInsert($xValue) {
        var_dump(' coluna de inteiro tratada é ' . $xValue);
        if ($this->increment && (is_null($xValue) || $xValue == '' || strtolower($xValue) == strtolower('null'))) {
            return "(SELECT COALESCE(MAX({$this->getDbaName()}),0) + 1  FROM %tabela%)";
        }
        if (is_null($xValue)) {
            return false;
        }
        return parent::getValorTratadoForInsert($xValue);
    }

}
