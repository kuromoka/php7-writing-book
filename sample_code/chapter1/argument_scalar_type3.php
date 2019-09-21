<?php

declare(strict_types=1);

function plus(integer $num1, integer $num2)
{
    return $num1 + $num2;
}

// int(1)
var_dump((int)'1a');
// int(1)
var_dump((integer)'1a');
// Argument 1 passed to plus() must be an instance of integer, int given
echo plus(1, 1);
