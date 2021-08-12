<?php

class Connection {

    protected function conecta() {
        $oDadosBanco = \DataBase\DadosBanco::getInstance();
        $aParams = '';
        $aParams .= ($oDadosBanco->getServer()) ? "host='$oDadosBanco->getServer()'" : '';
        $aParams .= ($oDadosBanco->getPorta()) ? "port='$oDadosBanco->getPorta()'" : '';
        $aParams .= ($oDadosBanco->getUser()) ? "user='$oDadosBanco->getUser()'" : '';
        $aParams .= ($oDadosBanco->getPassword()) ? "password='$oDadosBanco->getPassword()'" : '';
        $aParams .= ($oDadosBanco->getBanco()) ? "dbname='$oDadosBanco->getBanco()'" : '';
        $oThrowable = false;
        try {
            $this->connection = pg_connect($params);
        } catch (Throwable $exc) {
            $oThrowable = $exc;
        }
        $this->isConnected = is_resource($this->connection);
        if ($oThrowable) {
            if ($xDebug) {
                throw $oThrowable;
            } else {
                throw new Exception('Erro ao se comunicar com o servidor, contate o suporte');
            }
        }
        return $this->isConnected;
    }

    public function execute($sSql) {
        $xResource = false;
        try {
            $xResource = pg_query($this->connection->get_resource(), $sSql);
        } catch (Throwable $e) {
            
        }

        return $xResource;
    }

    public function getAll($sSql) {
        return new QueryIterator($this - connection, $sSql);
    }

}
