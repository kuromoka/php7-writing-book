<?php

class MyClass
{
    public int $num;
}

$myclass = new MyClass();
try {
    $myclass->num = 1;
    $myclass->num = 'test';
} catch (TypeError $e) {
    // Typed property MyClass::$num must be int, string used
    echo $e->getMessage();
}
