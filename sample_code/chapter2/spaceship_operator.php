<?php

$array1 = [
    'strawberry',
    'orange',
    'apple',
];
$array2 = $array1;

// 従来の書き方
usort($array1, function ($a, $b) {
    $a_len = strlen($a);
    $b_len = strlen($b);
    if ($a_len == $b_len) {
        return 0;
    }
    return $a_len < $b_len ? -1 : 1;
});
/*
Array
(
    [0] => apple
    [1] => orange
    [2] => strawberry
)
*/
print_r($array1);

// 宇宙船演算子を使った書き方
usort($array2, function ($a, $b) {
    return strlen($a) <=> strlen($b);
});
/*
Array
(
    [0] => apple
    [1] => orange
    [2] => strawberry
)
*/
print_r($array2);
