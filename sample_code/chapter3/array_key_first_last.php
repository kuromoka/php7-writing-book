<?php

$fruits1 = [
    'a' => 'strawberry',
    'b' => 'orange',
];
// string(1) "a"
var_dump(array_key_first($fruits1));
// string(1) "b"
var_dump(array_key_last($fruits1));

$fruits2 = [];
// NULL
var_dump(array_key_first($fruits2));
// NULL
var_dump(array_key_last($fruits2));
