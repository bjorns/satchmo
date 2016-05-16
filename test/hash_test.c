#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "hashtable.h"

void test_set_value() {
    hashtable_t *subject = new_hashtable(10);

    ht_set(subject, "foobar", "baz");

    assert_streq("baz", str((const char*)ht_get(subject, "foobar")));
}

void assert_result(const char *expected, void* data) {
    assert_streq(expected, str((const char*)data));
}

void test_chaining() {
    int TOO_SMALL = 2;
    hashtable_t *subject = new_hashtable(TOO_SMALL);

    ht_set(subject, "one", "ONE");
    ht_set(subject, "two", "TWO");
    ht_set(subject, "three", "THREE");
    ht_set(subject, "four", "FOUR");

    assert_result("ONE", ht_get(subject, "one"));
    assert_result("TWO", ht_get(subject, "two"));
    assert_result("THREE", ht_get(subject, "three"));
    assert_result("FOUR", ht_get(subject, "four"));
}

void hash_test() {
    test_set_value();
    test_chaining();
}
