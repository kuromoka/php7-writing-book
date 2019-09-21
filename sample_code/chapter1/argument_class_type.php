<?php

class MyClass1
{
    public function hello()
    {
        echo 'PHP7時代のコードの書き方';
    }
}

class MyClass2
{
}

function test(MyClass1 $obj)
{
    return $obj->hello();
}

// PHP7時代のコードの書き方
echo test(new MyClass1());
/*
Argument 1 passed to test() must be an instance of MyClass1,
instance of MyClass2 given
*/
echo test(new MyClass2());
