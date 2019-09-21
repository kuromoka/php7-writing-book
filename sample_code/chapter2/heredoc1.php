<?php

function test1()
{
    return <<< EOD
    PHP7時代のコードの書き方
EOD;
}

function test2()
{
    return <<< EOD
PHP7時代のコードの書き方
EOD;
}

// string(38) "    PHP7時代のコードの書き方"
var_dump(test1());
// string(34) "PHP7時代のコードの書き方"
var_dump(test2());
