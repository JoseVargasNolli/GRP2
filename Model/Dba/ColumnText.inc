<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnDba.inc';

/**
 * Description of ColumnVarchar
 *
 * @author bruno
 */
class ColumnText extends ColumnDba {

    public function isValorValido($xValue, $bThrow = true) {
        return is_string($xValue);
    }

    public function getValorTratadoForInsert($xValue) {
        if (is_null($xValue)) {
            return false;
        }
        return "'" . parent::getValorTratadoForInsert($xValue) . "'";
    }

}
