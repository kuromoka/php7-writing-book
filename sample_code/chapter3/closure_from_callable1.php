<?php

function test($str)
{
    return $str;
}

$testFunc = Closure::fromCallable('test');
// PHP7時代のコードの書き方
echo $testFunc('PHP7時代のコードの書き方');
