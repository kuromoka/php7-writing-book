<?php

declare(strict_types=1);

function division(int $num1, int $num2)
{
    return $num1 / $num2;
}

function test($num1, $num2)
{
    try {
        return division($num1, $num2);
    } catch (TypeError | DivisionByZeroError $e) {
        return $e->getMessage();
    }
}

// 2
echo test(2, 1);
// Argument 1 passed to division() must be of the type int, string given
echo test('test1', 'test2');
// Warning: Division by zero
echo test(1, 0);
