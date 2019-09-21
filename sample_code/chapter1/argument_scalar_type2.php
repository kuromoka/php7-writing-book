<?php

declare(strict_types=1);

function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

// 2
echo plus(1, 1);
// Argument 1 passed to plus() must be of the type int, string given
echo plus('test1', 'test2');
