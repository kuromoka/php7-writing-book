<?php

$fruits = [
    ['id' => 1, 'name' => 'strawberry'],
    ['id' => 2, 'name' => 'orange'],
];

list('id' => $id1, 'name' => $name1) = $fruits[0];
// 1
echo $id1;
// strawberry
echo $name1;

['id' => $id2, 'name' => $name2] = $fruits[1];
// 2
echo $id2;
// orange
echo $name2;
