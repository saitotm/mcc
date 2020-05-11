#!/bin/bash
assert() {
    expected="$1"
    input="$2"

    ./mcc "$input" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expeted, but got $actual"
        exit 1
    fi
}

#assert 15 "ab=2; a=3; (ab + a) * 3;"
#assert 15 "a = 3; b = 2; (a + b) * 3;"
assert 0 "0;"
assert 42 "42;"
assert 21 "5+20-4;"
assert 41 " 12 + 34 - 5 ;"
assert 47 "5 + 6 * 7;"
assert 15 "5*(9-6);"
assert 4 "(3+5) / 2;"
assert 10 "-10 + 20;"
assert 2 "-5 * 3 + 17;"
assert 0 "1 == 0;"
assert 1 "1 != 5;"
assert 1 "1 < 2;"
assert 1 "-1 <= 2;"
assert 1 "5 > 3;"
assert 0 "-3 >= 5;"
assert 3 "a = 3;"
assert 5 "a = 3; b = 2; a + b;"
assert 14 "a = 3; b = 5 * 6 - 8; a + b / 2;"
assert 15 "fizz = 3; buzz = 5; fizzbuzz = fizz * buzz;"
assert 15 "ab=2; a=3; (ab + a) * 3;"
assert 0 "return 0;"
assert 5 "return 5; return 8;"
assert 14 "a = 3; b = 5 * 6 - 8; return a + b / 2;"


echo OK