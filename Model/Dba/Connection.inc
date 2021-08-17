<?php

namespace Model\Dba;

require ROOT_PATH . '/Model/Dba/DadosBanco.inc';
require ROOT_PATH . '/Model/Dba/QueryIterator.inc';

class Connection {

    private $sSqlStartup = ['
        CREATE TABLE IF NOT EXISTS sistema.user
(
    codigo integer NOT NULL,
    nome character varying(400) COLLATE pg_catalog."default" NOT NULL,
    dataCadastro date NOT NULL,
    dataNascimento date NOT NULL,
    documento character varying(100) COLLATE pg_catalog."default",
    telefone character varying(20) COLLATE pg_catalog."default",
    email character varying(100) COLLATE pg_catalog."default",
    CONSTRAINT user_pkey PRIMARY KEY (codigo)
)',  '
CREATE TABLE IF NOT EXISTS sistema.solicitacao
(
    codigo integer NOT NULL,
    nome character varying(400) COLLATE pg_catalog."default" NOT NULL,
    dataCadastro date NOT NULL,
    texto text NOT NULL,
    codigoUsuario integer NOT NULL,
    CONSTRAINT solicitacao_pkey PRIMARY KEY (codigo)
)
'
        
];

    protected function conecta() {
        $oDadosBanco = \DataBase\DadosBanco::getInstance();
        $aParams = '';
        $aParams .= ($oDadosBanco->getServer()) ? " host={$oDadosBanco->getServer()} " : '';
        $aParams .= ($oDadosBanco->getPorta()) ? " port={$oDadosBanco->getPorta()} " : '';
        $aParams .= ($oDadosBanco->getUser()) ? " user={$oDadosBanco->getUser()} " : '';
        $aParams .= ($oDadosBanco->getPassword()) ? " password={$oDadosBanco->getPassword()} " : '';
        $aParams .= ($oDadosBanco->getBanco()) ? " dbname={$oDadosBanco->getBanco()} " : '';
        $oThrowable = false;
        try {
            $this->connection = pg_connect($aParams);
        } catch (Throwable $exc) {
            $oThrowable = $exc;
        }
        $this->isConnected = is_resource($this->connection);
        if ($oThrowable) {
            if ($xDebug) {
                throw $oThrowable;
            } else {
                throw new \Exception('Erro ao se comunicar com o servidor, contate o suporte');
            }
        }
        if ($this->isConnected) {
                foreach($this->sSqlStartup as $sSql){
                $this->execute($sSql);
            }
        }
        return $this->isConnected;
    }

    public function begin() {
        $this->conecta();
        pg_query($this->connection, 'begin');
        return $this;
    }

    public function commit() {
        if ($Error = pg_last_error($this->connection)) {

            $this->rollback();
            throw new \Exception($Error);
        } else {
            pg_query($this->connection, 'commit');
        }
        pg_close($this->connection);
        return $this;
    }

    public function rollback() {
        pg_query($this->connection, 'rollback');
    }

    public function execute($sSql) {
        $xResource = false;
        try {
            $xResource = pg_query($this->connection, $sSql);
        } catch (Throwable $e) {
            
        }
        var_dump($xResource);
        return $xResource;
    }

}
