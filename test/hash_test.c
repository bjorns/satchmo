#include <stdlib.h>
#include <stdio.h>

#include "core/hashtable.h"

#include "test.h"

void test_set_value() {
    hashtable_t *subject = new_hashtable(10);

    ht_set(subject, str("foobar"), "baz");

    const char *retreived = (const char*)ht_get(subject, str("foobar"));
    assert_streq("baz", str(retreived));
}

void assert_result(const char *expected, void* data) {
    assert_streq(expected, str((const char*)data));
}

void test_chaining() {
    int TOO_SMALL = 2;
    hashtable_t *subject = new_hashtable(TOO_SMALL);

    ht_set(subject, str("one"), "ONE");
    ht_set(subject, str("two"), "TWO");
    ht_set(subject, str("three"), "THREE");
    ht_set(subject, str("four"), "FOUR");

    assert_result("ONE", ht_get(subject, str("one")));
    assert_result("TWO", ht_get(subject, str("two")));
    assert_result("THREE", ht_get(subject, str("three")));
    assert_result("FOUR", ht_get(subject, str("four")));
}
