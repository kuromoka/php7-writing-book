= 型安全を意識した書き方
PHP7の新機能で一番拡張された機能と筆者が考えているのが、この型に関する機能です。PHPは動的型付き言語といわれていますが、静的型付き言語に近い書き方もできるようになっています。

本章ではこの型の機能にフォーカスして、より型安全を意識した書き方について紹介します。

== 型の一覧
まずはPHPの型についておさらいしておきましょう。普段あまり意識する場面は少ないですが、PHPの型はスカラー型・複合型・特別な型に分類されています。

=== スカラー型
スカラー型には次の型があります。

 * boolean
 ** true/falseの論理値
 * integer
 ** 整数値
 * float(double)
 ** 浮動小数点数
 * string
 ** 文字列

=== 複合型
複合型には次の型があります。

 * array
 ** 配列
 * object
 ** オブジェクト
 * callable
 ** コールバックを許容する型
 * iterable
 ** PHP7.1で導入された疑似型。arrayもしくはTraversableインタフェースを実装したオブジェクトを許容する型

=== 特別な型
上記に分類されない特別な型として、次の型があります。

 * resource
 ** DBやファイルなどの外部リソースへ接続する関数が返す型
 * NULL
 ** NULL

== 新しい型の機能の一覧
型安全を意識するうえで知っておきたいPHP7の新機能を紹介します。筆者なりの意見も交えて紹介していきます。

=== declare(strict_types=1)で厳密な型宣言を有効化

PHP7.0から対応した機能です。@<code>{declare}文に@<code>{strict_types}の設定が追加されました。この設定は厳密な型宣言を有効にするための設定で、ファイルの先頭に@<code>{declare(strict_types=1)}と宣言します。

//embed[latex]{
\clearpage
//}

次のコードを見てください（int型での型宣言については後述）。デフォルトだと厳密な型宣言が有効でないため、string型でもint型へ自動で型変換されて処理されるためにエラーが出ません。

//list[chapter1/strict_types1.php][chapter1/strict_types1.php]{
function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

// 2
echo plus('1a', '1b');
//}

@<code>{declare(strict_types=1)}を宣言すると、エラーが出ます。

//list[chapter1/strict_types2.php][chapter1/strict_types2.php]{
declare(strict_types=1);

function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

// Argument 1 passed to plus() must be of the type int, string given
echo plus('1a', '1b');
//}

型宣言を行うケースでは、@<code>{declare(strict_types=1)}のときの動作を期待していることの方が通常は多いと考えられます。またPHPの自動の型変換は複雑なため、バグの原因になったことを筆者も何度か経験してきました。

そのため基本的には一律で@<code>{declare(strict_types=1)}を宣言して、厳密な型宣言を有効にしたほうがいいと筆者は考えています。

ちなみに@<code>{declare(strict_types=1)}はファイル単位での宣言しかできず、意図的に全体適用できないようになっているようです。適用範囲についての詳しい説明は「declare(strict_types=1)の効力範囲について@<fn>{*1}」というQiitaの記事に詳しく説明されているので、そちらをご参照ください。

=== 関数の引数への型宣言
==== 配列での型宣言
配列については、PHP5のときから有効な型宣言です。

//list[chapter1/argument_array_type.php][chapter1/argument_array_type.php]{
function test(array $array)
{
    return count($array);
}

// 3
echo test([1, 2, 3]);
// Argument 1 passed to test() must be of the type array, int given
echo test(1);
//}

==== クラス名での型宣言
クラス名についても、PHP5のときと同様です。

//list[chapter1/argument_class_type.php][chapter1/argument_class_type.php]{
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
//}

==== スカラー型での型宣言
PHP7.0から対応した機能です。スカラー型での型宣言が有効になったことで、活用できる場面が大幅に増えました。

PHP5までは、たとえばスカラー型のint型の引数のみ許容する関数を宣言したい場合に、@<code>{is_int}で判定したり、PHPDocのコメントを書くことでカバーをしていました。@<fn>{*2}

//list[chapter1/argument_scalar_type1.php][chapter1/argument_scalar_type1.php]{
/**
 * @param int $num1
 * @param int $num2
 */
function plus($num1, $num2)
{
    if (is_int($num1) && is_int($num2)) {
        return $num1 + $num2;
    } else {
        throw new Exception();
    }
}

// 2
echo plus(1, 1);
// Uncaught Exception
echo plus('test1', 'test2');
//}

PHP7.0からは、配列やクラス名での型宣言と同じ感じで書くことができます。

//list[chapter1/argument_scalar_type2.php][chapter1/argument_scalar_type2.php]{
declare(strict_types=1);

function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

// 2
echo plus(1, 1);
// Argument 1 passed to plus() must be of the type int, string given
echo plus('test1', 'test2');
//}

注意点として、エイリアスがあるスカラー型の場合に一方のエイリアスで型宣言すると、クラス名として認識されてしまうのでご注意ください。

たとえばint型へのキャストは@<code>{(int)}と@<code>{(integer)}両方で行うことができますが、型宣言に@<code>{integer}と書くとint型の型宣言にはなりません。

//list[chapter1/argument_scalar_type3.php][chapter1/argument_scalar_type3.php]{
declare(strict_types=1);

function plus(integer $num1, integer $num2)
{
    return $num1 + $num2;
}

// int(1)
var_dump((int)'1a');
// int(1)
var_dump((integer)'1a');
// Argument 1 passed to plus() must be an instance of integer, int given
echo plus(1, 1);
//}

=== 関数の戻り値への型宣言
PHP7.0から対応した機能です。関数の戻り値に対しても、型宣言ができるようになりました。宣言時のコードが従来のPHPにはない見た目なので慣れが必要？ですが型安全を意識する上では、非常に重要な機能です。

//list[chapter1/return_string_type.php][chapter1/return_string_type.php]{
declare(strict_types=1);

function test($val) : string
{
    return $val;
}

// string(34) "PHP7時代のコードの書き方"
var_dump(test('PHP7時代のコードの書き方'));
// Return value of test() must be of the type string, int returned
var_dump(test(1));
//}

//embed[latex]{
\clearpage
//}

=== nullableな型宣言
PHP7.1から対応した機能です。型の前に@<code>{?}を付けることで、その型に加えて@<code>{NULL}を許容した型宣言ができるようになりました。「関数の引数や戻り値で複数の型を許容したくないけど、@<code>{NULL}は使いたい」といった場面で使えます。

//list[chapter1/nullable_int_type.php][chapter1/nullable_int_type.php]{
declare(strict_types=1);

function test(?int $val) : ?int
{
    return $val;
}

// int(1)
var_dump(test(1));
// NULL
var_dump(test(null));
// Argument 1 passed to test() must be of the type int or null, string given
var_dump(test('PHP7時代のコードの書き方'));
//}

//embed[latex]{
\clearpage
//}

=== void宣言
PHP7.1から対応した機能です。何も返さない関数の戻り値に対して、@<code>{void}を宣言できるようになりました。

@<code>{void}を宣言した関数では、空の@<code>{return}を使うか、@<code>{return}の省略が必要です。戻り値は@<code>{NULL}になります。

//list[chapter1/return_void_type1.php][chapter1/return_void_type1.php]{
function test(&$num) : void
{
    if ($num === 0) {
        return;
    }

    $num *= 10;
}

$num = 0;
// NULL
var_dump(test($num1));
// 0
echo $num;

$num = 10;
// NULL
var_dump(test($num));
// 100
echo $num;
//} 

次のように@<code>{return}で値を返すようなコードにした場合、実行時点でエラーになります。@<code>{void}の宣言で力を発揮できる場面は、この瞬間ではないでしょうか。

//list[chapter1/return_void_type2.php][chapter1/return_void_type2.php]{
function test(&$num) : void
{
    if ($num === 0) {
        // A void function must not return a value
        return $num;
    }

    $num *= 10;
}
//}

=== 型宣言の型と一致しない場合のTypeError例外
PHP7.0から対応した機能です。型宣言をした場合には、宣言した型と一致しない引数や戻り値だった場合のケアについても考えておく必要もあるでしょう。

宣言した型と一致しない場合は、@<code>{TypeError}例外がスローされるので、catchして例外時の処理を続けることができます。

//list[chapter1/catch_typeerror.php][chapter1/catch_typeerror.php]{
declare(strict_types=1);

function plus(int $num1, int $num2)
{
    return $num1 + $num2;
}

try {
    plus('test1', 'test2');
} catch (TypeError $e) {
    // Argument 1 passed to plus() must be of the type int, string given......
    echo $e->getMessage();
}
//}

この@<code>{TypeError}例外はPHP7.0から追加された@<code>{Error}クラスを継承しているため、従来の@<code>{Exception}だとcatchできないので注意が必要です。これらの変更については、PHPマニュアルの「PHP7でのエラー@<fn>{*3}」をご参照ください。

//footnote[*1][https://qiita.com/Hiraku/items/734f0666ab3d34c52efa]
//footnote[*2][PHPDocはあくまでコメントなので動作に影響は及ぼさないですが、IDEや静的解析ツールを使う場合に参照してくれることがあります。]
//footnote[*3][https://www.php.net/manual/ja/language.errors.php7.php]
