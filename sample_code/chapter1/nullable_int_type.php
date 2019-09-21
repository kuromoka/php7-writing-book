<?php

declare(strict_types=1);

function test(?int $val) : ?int
{
    return $val;
}

// int(1)
var_dump(test(1));
// NULL
var_dump(test(null));
// Argument 1 passed to test() must be of the type int or null, string given
var_dump(test('PHP7時代のコードの書き方'));
