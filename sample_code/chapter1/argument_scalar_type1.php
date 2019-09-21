<?php

/**
 * @param int $num1
 * @param int $num2
 */
function plus($num1, $num2)
{
    if (is_int($num1) && is_int($num2)) {
        return $num1 + $num2;
    } else {
        throw new Exception();
    }
}

// 2
echo plus(1, 1);
// Uncaught Exception
echo plus('test1', 'test2');
