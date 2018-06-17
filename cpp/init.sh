#!/bin/bash

set -euo pipefail

if [ $# != 1 ]; then
    >&2 echo 'usage: ./init.sh <problem-name>'
    exit 1
fi

cp -r .skel "$1"
cd "$1"
cmake -H. -Bbuild -G Ninja
