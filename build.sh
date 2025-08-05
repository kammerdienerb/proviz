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

PCRE2_CFLAGS=""
PCRE2_LDFLAGS=""
if which pcre2-config > /dev/null && ! [[ $(pcre2-config --version) < "10.36" ]]; then
    PCRE2_CFLAGS="$(pcre2-config --cflags-posix) -DJULIE_USE_PCRE2"
    PCRE2_LDFLAGS="$(pcre2-config --libs-posix)"
fi

# ASAN="-fsanitize=address"
# CFLAGS="-Wall -Werror -pedantic -Wno-gnu-zero-variadic-macro-arguments -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O0 ${ASAN} ${PCRE2_CFLAGS}"
CFLAGS="-g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O3 -march=native -mtune=native -DJULIE_ASSERTIONS=0 ${PCRE2_CFLAGS}"

LDFLAGS="-lm -ldl ${PCRE2_LDFLAGS}"

gcc -o proviz proviz.c ${CFLAGS} ${LDFLAGS}
