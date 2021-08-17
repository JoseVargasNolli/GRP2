<?php

namespace Model\Dba;

require_once ROOT_PATH . '/Model/Dba/ColumnText.inc';

/**
 * Description of ColumnVarchar
 *
 * @author bruno
 */
class ColumnVarchar extends ColumnText {

    private $size;

    public function __construct($sNameDba, $sNameModel, $iSize) {
        parent::__construct($sNameDba, $sNameModel);
        $this->size = $iSize;
    }

    public function isValorValido($xValue, $bThrow = true) {
        $xValueTratado = pg_escape_string($xValue);
        if (strlen($xValueTratado) > $this->size) {
            if ($bThrow) {
                $this->showExceptionNotSupported();
            }
            return false;
        }
        return parent::isValorValido($xValueTratado);
    }

}
