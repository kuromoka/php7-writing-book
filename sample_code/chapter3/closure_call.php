<?php

class MyClass
{
    private $num;

    public function __construct($num)
    {
        $this->num = $num;
    }
}

$getNum = function () {
    return $this->num;
};
$myclass1 = new MyClass(1);
$myclass2 = new MyClass(2);

// 1
echo $getNum->bindTo($myclass1, 'MyClass')();
// 2
echo $getNum->bindTo($myclass2, 'MyClass')();
// 1
echo $getNum->call($myclass1);
// 2
echo $getNum->call($myclass2);
