<?php

declare(strict_types=1);

function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

try {
    plus('test1', 'test2');
} catch (TypeError $e) {
    // Argument 1 passed to plus() must be of the type int, string given......
    echo $e->getMessage();
}
