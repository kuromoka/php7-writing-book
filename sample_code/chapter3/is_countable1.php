<?php

$fruits = [
    'a' => 'strawberry',
    'b' => 'orange',
    'c' => 'apple',
];

if (is_array($fruits)) {
    // 3
    echo count($fruits);
}
if (is_countable($fruits)) {
    // 3
    echo count($fruits);
}

$apple = 'apple';
if (!is_countable($apple)) {
    // Not Countable
    echo 'Not Countable';
}
