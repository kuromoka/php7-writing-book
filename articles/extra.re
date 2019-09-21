= 付録：PHP7.4について
PHP7.4の正式版が出るのは2019年の11月予定@<fn>{*1}となっているため、本書ではすでに正式版としてリリースされているPHP7.3.xを対象とした本にしました。

ただPHP7.4の新機能を見ていく中でこれは便利そうという機能については、何かしら本書でも触れておきたいと考えて、短い付録ですが収録しました。

前述したようにPHP7.4はまだ正式版ではないため、ここで紹介している機能に変更があったりする可能性はあるため、その点ご理解いただき読んでいただけると幸いです。

冒頭にも記載していますがこの付録に記載のコードについては、「7.4.0RC1」のバージョンで動作を確認しています。

== プロパティ変数への型宣言
従来できなかったのが不思議な感覚すらありますが、クラスのプロパティ変数に型を付けることができます。型と一致しないときに@<code>{TypeError}例外がスローされるのは、関数の引数や戻り値の型宣言と同じ動作になっています。

//list[extra/typed_properties.php][extra/typed_properties.php]{
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
//}

== アロー関数
JavaScriptとかではお馴染みのやつです。コールバック関数をスッキリと書くことができます。

//list[extra/arrow_functions.php][extra/arrow_functions.php]{
$fruits = [
    'strawberry',
    'orange',
    'apple',
];
$filtered_fruit1 = array_filter($fruits, function($fruit) {
    return strlen($fruit) <= 5;
});
$filtered_fruit2 = array_filter($fruits, fn($fruit) => strlen($fruit) <= 5);

/*
Array
(
    [2] => apple
)
*/
print_r($filtered_fruit1);
/*
Array
(
    [2] => apple
)
*/
print_r($filtered_fruit2);
//}

== 「??=」演算子
これの日本語訳は「null合体代入演算子」とか呼ばれているようです。@<fn>{*3}次のように、null合体演算子の@<code>{??}と代入を同時に行うことができます。

//list[extra/null_coalescing_assignment_operator.php][extra/null_coalescing_assignment_operator.php]{
$id = null;
// $id  = $id ?? 100 と同様
$id ??= 100;
// 100
echo $id;
//}

//footnote[*1][https://wiki.php.net/todo/php74]
//footnote[*2][https://wiki.php.net/rfc/covariant-returns-and-contravariant-parameters]
//footnote[*3][https://qiita.com/rana_kualu/items/e15a9b7c12f175380244]
