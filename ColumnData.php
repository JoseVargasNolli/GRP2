<?php

namespace Model;

/**
 * Description of ColumnData
 *
 * @author bruno
 */
class ColumnDate extends ColumnDba {

    public function isValorValido($xValorValido) {
        return !!date_create_from_format('d/m/Y', $xValorValido);
    }

}
