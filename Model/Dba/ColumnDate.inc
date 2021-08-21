<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnDba.inc';

/**
 * Description of ColumnData
 *
 * @author bruno
 */
class ColumnDate extends ColumnDba {

    public function isValorValido($xValorValido, $bThrow = true) {
        try {
            $aData = explode('/', $xValorValido);

            if (!(strlen($aData[0]) == 2) || !(strlen($aData[1]) == 2) || !(strlen($aData[2]) == 4)) {
//                $this->showExceptionNotSupported();
            }
        } catch (Exception $ex) {
            if ($bThrow) {
//                $this->showExceptionNotSupported();
            }
//            return false;
        }
        return true;
    }

    public function getValorTratadoForInsert($xValue) {
        if (is_null($xValue)) {
            return false;
        }
        return "'" . parent::getValorTratadoForInsert($xValue) . "'";
    }
}
