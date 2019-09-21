<?php

$fruits = [
    'strawberry',
    'orange',
    'apple',
];
$filtered_fruit1 = array_filter($fruits, function($fruit) {
    return strlen($fruit) <= 5;
});
$filtered_fruit2 = array_filter($fruits, fn($fruit) => strlen($fruit) <= 5);

/*
Array
(
    [2] => apple
)
*/
print_r($filtered_fruit1);
/*
Array
(
    [2] => apple
)
*/
print_r($filtered_fruit2);
