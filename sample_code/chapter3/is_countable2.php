<?php

class MyClass1 implements Countable
{
    private $num = 10;

    public function count()
    {
        return $this->num;
    }
}

class MyClass2
{
}

$myclass1 = new MyClass1();
if (is_countable($myclass1)) {
    // 10
    echo count($myclass1);
}

$myclass2 = new MyClass2();
if (!is_countable($myclass2)) {
    // Not Countable
    echo 'Not Countable';
}
