<?php

namespace Model;

/**
 * Description of ColumnDba
 *
 * @author bruno
 */
abstract class ColumnDba {

    private $nameDba;
    private $nameModel;

    public function __construct($sNameDba, $sNameModel) {
        $this->nameDba = $sNameDba;
        $this->nameModel = $sNameModel;
    }

    public function getDbaName() {
        return $this->nameDba;
    }

    public function getNameModel() {
        return $this->nameModel;
    }

    abstract public function isValorValido($xValorValido);
}
