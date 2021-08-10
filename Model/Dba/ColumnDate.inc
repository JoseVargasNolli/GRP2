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
        if (!!date_create_from_format('d/m/Y', $xValorValido)) {
            if ($bThrow) {
                $this->showExceptionNotSupported();
            }
            return false;
        }
        return true;
    }

}
