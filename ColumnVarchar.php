<?php

namespace Model;

/**
 * Description of ColumnVarchar
 *
 * @author bruno
 */
class ColumnVarchar extends ColumnDba {

    private $size;

    public function __construct($sNameDba, $sNameModel, $iSize) {
        parent::__construct($sNameDba, $sNameModel);
        $this->size = $iSize;
    }

    public function isValorValido($xValue, $bThrow = true) {
        $xValueTratado = pg_escape_string($xValue);
        if (strlen($xValueTratado) > $this->size) {
            if ($bThrow) {
                throw new Exception('Valor não suportado');
            }
            return false;
        }
        return true;
    }

}
