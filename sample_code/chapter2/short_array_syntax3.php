<?php

$fruits = [
    [1, 'strawberry'],
    [2, 'orange'],
];

foreach ($fruits as [$id, $name]) {
    // 1, 2
    echo $id;
    // strawberry, orange
    echo $name;
}
