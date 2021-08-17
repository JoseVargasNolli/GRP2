<?php

namespace Model\Dba;

class QueryIterator implements \Iterator, \Countable {

    function __construct($sSql) {
        $this->connection = new Connection();
        $this->connection->begin();
        $this->sql = $sSql;
    }

    private $rowNumber;
    private $rowContent;

    function end() {
        $this->connection->rollback();
    }

    function init() {
        $this->resource = $this->connection->execute($this->sql);
    }

    function fetch() {
        if ($this->resource) {
            return pg_fetch_assoc($this->resource);
        }
        return false;
    }

    function valid() {
        return !!$this->current();
    }

    function next() {
        $this->rowContent = $this->fetch();
        $this->rowNumber++;
    }

    function key() {
        return $this->rowNumber;
    }

    function rewind() {
        $this->rowNumber = 0;
        $this->rowContent = null;
        $this->init();
        $this->next();
    }

    function current() {
        return $this->rowContent;
    }

    public function count(): int {
        return pg_affected_rows($this->resource);
    }

}
