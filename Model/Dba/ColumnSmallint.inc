<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnDba.inc';
/**
 * Description of ColumnSmallint
 *
 * @author bruno
 */
class ColumnSmallint extends ColumnInteger {

    const SIZE_MIN_SMALLINT = -32767;
    const SIZE_MAX_SMALLINT = +32767;

    //put your code here
    public function isValorValido($xValorValido, $bThrow = true) {
        $bIsValido = parent::isValorValido($xValorValido);
        if (!($xValorValido >= self::SIZE_MIN_SMALLINT && $xValorValido <= self::SIZE_MAX_SMALLINT)) {
            if ($bThrow) {
                $this->showExceptionNotSupported();
            }
            return false;
        }
        return $bIsValido;
    }

}
