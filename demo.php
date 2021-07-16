<?php
$code = morseEncode("derek-sunder/yes!/this_is_me");
var_dump($code);
$str = morseDecode($code);
var_dump($str);
