<?php

function test() {
    return ['strawberry', 'orange'];
}

[$fruit1, $fruit2] = test();
// strawberry
echo $fruit1;
// orange
echo $fruit2;
