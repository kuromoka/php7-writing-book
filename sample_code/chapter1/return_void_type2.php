<?php

function test(&$num) : void
{
    if ($num === 0) {
        // A void function must not return a value
        return $num;
    }

    $num *= 10;
}
