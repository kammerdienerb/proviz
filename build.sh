#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd $DIR

rm -f *.j.h

for f in $(find . -name "*.j"); do
    dir=$(basename $(dirname "${f}"))
    if [[ ${dir} == "." ]]; then
        dir=""
    fi
    base=$(basename ${f} ".j")
    xxd -n "${dir}_${base}_j" -i ${f} > ${f}.h || exit $?
done

# ASAN="-fsanitize=address"
# CFLAGS="-Wall -Werror -pedantic -Wno-gnu-zero-variadic-macro-arguments -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O0 ${ASAN}"
CFLAGS="-g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O3 -march=native -mtune=native -DJULIE_ASSERTIONS=0"

LDFLAGS="-lm -ldl"

gcc -o proviz proviz.c ${CFLAGS} ${LDFLAGS}
