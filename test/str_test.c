#include "str.h"
#include "test.h"

void test_eq() {
    str_t x = new_str("foobar", 6);
    str_t y = str("foobar");
    str_t z = new_str("foobar2", 7);
    str_t p = new_str("barfoo", 6);
    assert("Strings are not equal", str_eq(x, y));
    assert("Strings are equal", !str_eq(x, z));
    assert("Strings are equal", !str_eq(x, p));
}

void test_substr() {
    str_t x = new_str("foobar", 6);
    assert("Incorrect substr", str_eq(substr(x, 0, 3), new_str("foo", 3)));
    assert("Incorrect substr", str_eq(substr(x, 3, 6), new_str("bar", 3)));
}

void str_test() {
    test_eq();
    test_substr();
}
