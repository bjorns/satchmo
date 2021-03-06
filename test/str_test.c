#include "test.h"
#include <string.h>

void test_new_str() {
    str_t x = new_str("foobar", 6);
    assert(6 == x.length);
    assert(0 == strcmp("foobar", x.data));
    assert('\0' == x.data[6]);

    str_t y = str("barfoo");
    assert(6 == y.length);
    assert(0 == strcmp("barfoo", y.data));
    assert('\0' == y.data[6]);
}

void test_eq() {
    str_t x = new_str("foobar", 6);
    str_t y = str("foobar");
    str_t z = new_str("foobar2", 7);
    str_t p = new_str("barfoo", 6);


    assert(str_eq(x, y));

    assert(!str_eq(x, z));
    assert(!str_eq(x, p));
}

void test_substr() {
    str_t x = new_str("foobar", 6);
    assert(str_eq(substr(x, 0, 3), new_str("foo", 3)));
    assert(str_eq(substr(x, 3, 6), new_str("bar", 3)));
}

void test_copy() {
    str_t x = str("foobar");
    str_t copy;
    str_copy(&copy, &x);
    ASSERT(x.data != copy.data);
    ASSERT(x.length == 6);
    assert_streq("foobar", copy);
}
