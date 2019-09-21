#!/bin/bash

if [ $# -ne 1 ]; then
  echo "実行するPHPファイルを1つ指定してください"
  echo "コマンド例："
  echo "$ $0 sample_code/version.php"
  exit 1
fi

docker run -it --rm --name php56 -v "$PWD":/usr/src/myapp -w /usr/src/myapp php:5.6-cli php $1
