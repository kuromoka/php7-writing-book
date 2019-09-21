= 新しい文法を使った書き方
PHP7では文法面でも新しい追加が多くありました。本章では新しく追加された文法のいくつかをピックアップして、従来のコードに比べて簡潔さや書き心地が上がる例を紹介します。

== null合体演算子
PHP7.0から対応した機能です。null合体演算子@<code>{??}を使うと、PHP5までの@<code>{isset}による存在チェックを次のように書くことができます。

//list[chapter2/null_coalescing_operator.php][chapter2/null_coalescing_operator.php]{
$user = [
    'id' => 1,
];

// 従来のissetを使った書き方
$status1 = isset($user['status']) ? $user['status'] : 100;
// 100
echo $status1;

// null合体演算子を使った書き方
$status2 = $user['status'] ?? 100;
// 100
echo $status2;
//}

== 宇宙船演算子
PHP7.0から対応した機能です。聞き慣れない名前ですが、宇宙船演算子とは@<code>{<=>}のことです。2つの式を比較してその結果を返す演算子になります。それぞれの式を@<code>{$a}、@<code>{$b}としたとき、次のような結果が返ってきます。

 * @<code>{$a = $b}なら、0が返ってくる
 * @<code>{$a < $b}なら、-1が返ってくる
 * @<code>{$a > $b}なら、1が返ってくる

「はたしてこれを何に使うのか？」といった疑問ですが、たとえば@<code>{usort}で宇宙船演算子を使ってあげると、中身がスッキリとします。

//list[chapter2/spaceship_operator.php][chapter2/spaceship_operator.php]{
$array1 = [
    'strawberry',
    'orange',
    'apple',
];
$array2 = $array1;

// 従来の書き方
usort($array1, function ($a, $b) {
    $a_len = strlen($a);
    $b_len = strlen($b);
    if ($a_len == $b_len) {
        return 0;
    }
    return $a_len < $b_len ? -1 : 1;
});
/*
Array
(
    [0] => apple
    [1] => orange
    [2] => strawberry
)
*/
print_r($array1);

// 宇宙船演算子を使った書き方
usort($array2, function ($a, $b) {
    return strlen($a) <=> strlen($b);
});
/*
Array
(
    [0] => apple
    [1] => orange
    [2] => strawberry
)
*/
print_r($array2);
//}

== use宣言のグループ化

PHP7.0から対応した機能です。use宣言を複数書くときにまとめて書くことができます。例として、次のような@<code>{MyNamespace}の名前空間に属するクラスを2つ定義します。

//list[chapter2/mynamespace.php][chapter2/mynamespace.php]{
namespace MyNamespace {
    class MyClass1
    {
        public function getClassName()
        {
            echo __CLASS__;
        }
    }

    class MyClass2
    {
        public function getClassName()
        {
            echo __CLASS__;
        }
    }
}
//}

PHP5までは次のように、複数useしたいときにはuse宣言も分けて書く必要がありました。

//list[chapter2/use_group1.php][chapter2/use_group1.php]{
// MyNamespace名前空間のクラスを読み込む
require_once 'mynamespace.php';

use MyNamespace\MyClass1;
use MyNamespace\MyClass2;

// MyNamespace\MyClass1
echo MyClass1::getClassName();
//MyNamespace\MyClass2
echo MyClass2::getClassName();
//}

PHP7.0からはグループ化することで、同じ名前空間なら1行にまとめて書くことができます。ちなみにPHP7.2からは最後にカンマを付けることもできます。

//embed[latex]{
\clearpage
//}

//list[chapter2/use_group2.php][chapter2/use_group2.php]{
// MyNamespace名前空間のクラスを読み込む
require_once 'mynamespace.php';

use MyNamespace\{MyClass1, MyClass2};
// use MyNamespace\{MyClass1, MyClass2,};

// MyNamespace\MyClass1
echo MyClass1::getClassName();
//MyNamespace\MyClass2
echo MyClass2::getClassName();
//}

== 複数の例外をまとめてcatchする
PHP7.1から対応した機能です。catchで複数の例外をまとめてcatchできるようになりました。複数の例外でcatch後の処理を共通化したい場合に簡潔に書くことができます。

次のコードはPHP7から追加された、引数の型が異なる場合の@<code>{TypeError}例外@<fn>{*1}とゼロで除算した場合の@<code>{DivisionByZeroError}例外@<fn>{*2}を、まとめてcatchした例です。

//list[chapter2/multiple_catch.php][chapter2/multiple_catch.php]{
declare(strict_types=1);

function division(int $num1, int $num2)
{
    return $num1 / $num2;
}

function test($num1, $num2)
{
    try {
        return division($num1, $num2);
    } catch (TypeError | DivisionByZeroError $e) {
        return $e->getMessage();
    }
}

// 2
echo test(2, 1);
// Argument 1 passed to division() must be of the type int, string given
echo test('test1', 'test2');
// Warning: Division by zero
echo test(1, 0);
//}

== 配列短縮記法[]でlistの置き換え
PHP7.1から対応した機能です。@<code>{[]}の機能が強化されたことで、次のような@<code>{list}で書いていた処理を簡潔に書くことができます。

=== 配列の分解
@<code>{[]}で配列を分解して、複数の変数への代入ができます。

//list[chapter2/short_array_syntax1.php][chapter2/short_array_syntax1.php]{
$fruits = [
    [1, 'strawberry'],
    [2, 'orange'],
];

list($id1, $name1) = $fruits[0];
// 1
echo $id1;
// strawberry
echo $name1;

[$id2, $name2] = $fruits[1];
// 2
echo $id2;
// orange
echo $name2;
//}

=== 戻り値の配列の分解
関数から複数の値を戻したいときに配列を返すことがありますが、@<code>{[]}で戻り値の配列を分解して、複数の変数への代入ができます。

//list[chapter2/short_array_syntax2.php][chapter2/short_array_syntax2.php]{
function test() {
    return ['strawberry', 'orange'];
}

[$fruit1, $fruit2] = test();
// strawberry
echo $fruit1;
// orange
echo $fruit2;
//}

=== foreachの変数を分解
@<code>{foreach}でも次のように書くことで、分解した状態の値が取得できます。

//list[chapter2/short_array_syntax3.php][chapter2/short_array_syntax3.php]{
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
//}

== listや[]での配列キーのサポート
PHP7.1から対応した機能です。listや@<code>{[]}で、キーが含まれた配列も分解できるようになりました。

//list[chapter2/list_key.php][chapter2/list_key.php]{
$fruits = [
    ['id' => 1, 'name' => 'strawberry'],
    ['id' => 2, 'name' => 'orange'],
];

list('id' => $id1, 'name' => $name1) = $fruits[0];
// 1
echo $id1;
// strawberry
echo $name1;

['id' => $id2, 'name' => $name2] = $fruits[1];
// 2
echo $id2;
// orange
echo $name2;
//}

== ヒアドキュメントとNowdocの強化
PHP7.3から対応した機能です。ヒアドキュメントはダブルクオート@<code>{""}で、Nowdocはシングルクオート@<code>{''}で囲まれた文字列と同様に動作する書き方です。ただし使うには結構癖があるので、毎回書き方を調べている方も多いのではないでしょうか。

たとえば次のコードは従来のヒアドキュメントを使った例です。@<code>{test1}関数は戻り値にインデントのスペースが含まれているため、消すためには@<code>{test2}関数のようにインデントを削除する必要があり、コードの視認性が下がっていました。

//list[chapter2/heredoc1.php][chapter2/heredoc1.php]{
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
//}

PHP7.3からは終端文字のインデントが可能になりかつ終端文字の位置からの文字列になるため、より直感的に視認性の高い書き方が可能になっています。

//list[chapter2/heredoc2.php][chapter2/heredoc2.php]{
function test()
{
    return <<< EOD
    PHP7時代のコードの書き方
    EOD;
}

// string(34) "PHP7時代のコードの書き方"
var_dump(test());
//}

== 関数呼び出し時の末尾カンマの許可
PHP7.3から対応した機能です。関数呼び出し時に、末尾にカンマが許可されるようになりました。たとえば次のような可変長引数の関数を呼び出す場合に、引数を追加するたびに末尾のカンマを消さなくてすむので便利です。

//list[chapter2/trailing_commas1.php][chapter2/trailing_commas1.php]{
function sum(...$numbers)
{
    $sum = 0;
    foreach ($numbers as $number) {
        $sum += $number;
    }
    return $sum;
}

// 19
echo sum(1, 2, 3, 5, 8,);
//}

もちろん自分で定義した関数ではなくPHPの組込み関数でも同様の記述が可能で、たとえば@<code>{var_dump}などは頻繁に引数を追加削除するので便利です。

//list[chapter2/trailing_commas2.php][chapter2/trailing_commas2.php]{
$fruit1 = 'strawberry';
$fruit2 = 'orange';
$fruit3 = 'apple';

/*
string(10) "strawberry"
string(6) "orange"
string(5) "apple"
*/
var_dump($fruit1, $fruit2, $fruit3,);
//}

//footnote[*1][https://www.php.net/manual/ja/class.typeerror.php]
//footnote[*2][https://www.php.net/manual/ja/class.divisionbyzeroerror.php]
