<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnDba.inc';

/**
 * Description of ColumnData
 *
 * @author bruno
 */
class ColumnBoolean extends ColumnDba {

    public function isValorValido($xValorValido, $bThrow = true) {
        if (is_bool(!!$xValorValido)) {
            return true;
        }
        if ($bThrow) {
            $this->showExceptionNotSupported();
        }
    }

}
