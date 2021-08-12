<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnDba.inc';
/**
 * Description of ColumnInteger
 *
 * @author bruno
 */
class ColumnInteger extends ColumnDba {

    //put your code here
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

}
