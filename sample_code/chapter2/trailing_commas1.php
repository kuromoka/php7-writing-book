<?php

function sum(...$numbers)
{
    $sum = 0;
    foreach ($numbers as $number) {
        $sum += $number;
    }
    return $sum;
}

// 19
echo sum(1, 2, 3, 5, 8,);
