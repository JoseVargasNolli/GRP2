<?php

namespace Model\Manager;

/**
 * Description of UserManager
 *
 * @author bruno
 */
class ResponseManager {

    public static function createSucessResponse($xBody) {
        $xResponse = [];
        $xResponse['header'] = 'HTTP/1.1 200 Ok';
        $xResponse['body'] = $xBody;
        return $xResponse;
    }

    public static function createNotFoundResponse() {
        $xResponse = [];
        $xResponse['header'] = 'HTTP/1.1 404 Not Found';
        return $xResponse;
    }

}
