= 新しい関数を使った書き方
PHP7では関数にもいくつか新しい追加がありました。本章では新しく追加された関数のいくつかをピックアップして、従来は一手間必要だった処理が、新しい関数を使って簡潔に書ける例を紹介します。

== intdiv関数
PHP7.0から追加された関数です。@<code>{intdiv}は、除算した結果の整数値を返す関数です。@<code>{/}での除算だと割り切れない場合に小数値の結果になるため、切り捨てが必要でした。

//list[chapter3/intdiv.php][chapter3/intdiv.php]{
// float(1.6666666666667)
var_dump(5 / 3);
// int(1)
var_dump(intdiv(5, 3));
//}

== array_key_firstとarray_key_last関数
PHP7.0から追加された関数です。@<code>{array_key_first}は配列の最初のキー、@<code>{array_key_last}は配列の最後のキーを返す関数です。従来だと簡単そうに見えて意外と面倒な処理でした。空配列の場合は@<code>{NULL}を返します。

//embed[latex]{
\clearpage
//}

//list[chapter3/array_key_first_last.php][chapter3/array_key_first_last.php]{
$fruits1 = [
    'a' => 'strawberry',
    'b' => 'orange',
];
// string(1) "a"
var_dump(array_key_first($fruits1));
// string(1) "b"
var_dump(array_key_last($fruits1));

$fruits2 = [];
// NULL
var_dump(array_key_first($fruits2));
// NULL
var_dump(array_key_last($fruits2));
//}

== Closure::call関数
PHP7.0から追加された関数です。@<code>{Closure::call}は、クロージャにオブジェクト束縛して実行できます。この説明だけだと分かりづらいので、コードを見ていきましょう。

従来はクロージャ内の@<code>{$this}の参照オブジェクトを変更するために@<code>{Closure::bindTo}を挟む必要がありましたが、@<code>{Closure::call}を使うと簡潔に書くことができます。

//list[chapter3/closure_call.php][chapter3/closure_call.php]{
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
//}

== Closure::fromCallable関数
PHP7.1から追加された関数です。@<code>{Closure::fromCallable}は、コールバックからクロージャを作ることができます。筆者はこれまで知らなかったのですが、コールバックについては意外と奥深いので、PHPマニュアルの「コールバック/Callable@<fn>{*1}」もぜひご参照ください。

次のコードは単純な関数をクロージャにして呼び出した例です。

//list[chapter3/closure_from_callable1.php][chapter3/closure_from_callable1.php]{
function test($str)
{
    return $str;
}

$testFunc = Closure::fromCallable('test');
// PHP7時代のコードの書き方
echo $testFunc('PHP7時代のコードの書き方');
//}

オブジェクトのメソッドもクロージャにできるので、privateメソッドをクロージャにして呼び出すなんてこともできます。

//list[chapter3/closure_from_callable2.php][chapter3/closure_from_callable2.php]{
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
//}

== is_countable関数
PHP7.3から追加された関数です。@<code>{is_countable}は、引数の内容が@<code>{count}関数で数えられる値かを調べる関数です。PHP7.2から@<code>{count}関数が、配列もしくは@<code>{Countable}を実装したオブジェクト以外だと受け付けなくなったため@<fn>{*2}、追加されました。

=== 配列に使う
@<code>{count}を使いたい場面は、次のコードのように配列に対して使いたい場合がほとんどではないでしょうか。そのため従来の@<code>{is_array}での検査でも問題はないですが、@<code>{is_countable}の方が「このあと@<code>{count}するんだな」というのが分かりやすいメリットはあります。

//list[chapter3/is_countable1.php][chapter3/is_countable1.php]{
$fruits = [
    'a' => 'strawberry',
    'b' => 'orange',
    'c' => 'apple',
];

if (is_array($fruits)) {
    // 3
    echo count($fruits);
}
if (is_countable($fruits)) {
    // 3
    echo count($fruits);
}

$apple = 'apple';
if (!is_countable($apple)) {
    // Not Countable
    echo 'Not Countable';
}
//}

//embed[latex]{
\clearpage
//}

=== Countableを実装したオブジェクトに使う
@<code>{Countable}を実装したオブジェクトの場合は、次のように使うことができます。筆者は@<code>{Countable}が実際に使われているコードを見たことがないので、@<code>{is_countable}の追加を期にもっと広まってほしいところです。

//list[chapter3/is_countable2.php][chapter3/is_countable2.php]{
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
//}

//footnote[*1][https://www.php.net/manual/ja/language.types.callable.php]
//footnote[*2][PHP7.2のcountにハマった話（https://qiita.com/masaki-ogawa/items/1671d110b2286ececd09）という記事もご参照ください]
