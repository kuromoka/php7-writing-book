<?php

function test(&$num) : void
{
    if ($num === 0) {
        return;
    }

    $num *= 10;
}

$num = 0;
// NULL
var_dump(test($num));
// 0
echo $num;

$num = 10;
// NULL
var_dump(test($num));
// 100
echo $num;
