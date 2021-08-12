<?php

namespace Model\Dba;

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

    public function getModelName() {
        return $this->nameModel;
    }

    protected function showExceptionNotSupported() {
        throw new \Exception('Valor não suportado');
    }

    abstract public function isValorValido($xValorValido, $bThrow = true);
}
