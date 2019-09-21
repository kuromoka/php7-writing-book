<?php

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
