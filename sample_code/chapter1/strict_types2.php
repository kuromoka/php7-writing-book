<?php

declare(strict_types=1);

function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

// Argument 1 passed to plus() must be of the type int, string given
echo plus('1a', '1b');
