<?php

// MyNamespace名前空間のクラスを読み込む
require_once 'mynamespace.php';

use MyNamespace\{MyClass1, MyClass2};
// use MyNamespace\{MyClass1, MyClass2,};

// MyNamespace\MyClass1
echo MyClass1::getClassName();
//MyNamespace\MyClass2
echo MyClass2::getClassName();
