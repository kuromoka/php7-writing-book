<?php

$fruits = [
    [1, 'strawberry'],
    [2, 'orange'],
];

list($id1, $name1) = $fruits[0];
// 1
echo $id1;
// strawberry
echo $name1;

[$id2, $name2] = $fruits[1];
// 2
echo $id2;
// orange
echo $name2;
