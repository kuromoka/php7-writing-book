<?php

class MyClass
{
    public function getClosure()
    {
        return Closure::fromCallable([$this, 'test']);
    }

    private function test($str)
    {
        return $str; 
    }
}

$myclass = new MyClass();
$testFunc = $myclass->getClosure();
// PHP7時代のコードの書き方
echo $testFunc('PHP7時代のコードの書き方');
