<?php

function test(array $array)
{
    return count($array);
}

// 3
echo test([1, 2, 3]);
// Argument 1 passed to test() must be of the type array, int given
echo test(1);
