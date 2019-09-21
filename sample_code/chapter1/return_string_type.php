<?php

declare(strict_types=1);

function test($val) : string
{
    return $val;
}

// string(34) "PHP7時代のコードの書き方"
var_dump(test('PHP7時代のコードの書き方'));
// Return value of test() must be of the type string, int returned
var_dump(test(1));
