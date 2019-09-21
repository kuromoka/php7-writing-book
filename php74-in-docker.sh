#!/bin/bash

if [ $# -ne 1 ]; then
  echo "実行するPHPファイルを1つ指定してください"
  echo "コマンド例："
  echo "$ $0 sample_code/version.php"
  exit 1
fi

docker run -it --rm --name php74 -v "$PWD":/usr/src/myapp -w /usr/src/myapp php:7.4.0RC1-cli php $1
