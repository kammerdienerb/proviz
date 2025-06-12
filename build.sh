#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd $DIR

rm -f *.j.h

for f in *.j; do
    xxd -n $(basename ${f} ".j")_j -i ${f} > ${f}.h || exit $?
done

CFLAGS="-g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O0"
# CFLAGS="-g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O3 -march=native -mtune=native"

LDFLAGS="-lm -ldl"

gcc -o proviz proviz.c ${CFLAGS} ${LDFLAGS}
