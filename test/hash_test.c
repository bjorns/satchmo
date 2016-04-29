#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "hashtable.h"

void test_set_value() {
    hashtable_t *subject = ht_create(10);

    ht_set(subject, "foobar", "baz");

    assert_streq("baz", ht_get(subject, "foobar"));
}

void test_chaining() {
    int TOO_SMALL = 2;
    hashtable_t *subject = ht_create(TOO_SMALL);

    ht_set(subject, "one", "ONE");
    ht_set(subject, "two", "TWO");
    ht_set(subject, "three", "THREE");
    ht_set(subject, "four", "FOUR");

    assert_streq("ONE", ht_get(subject, "one"));
    assert_streq("TWO", ht_get(subject, "two"));
    assert_streq("THREE", ht_get(subject, "three"));
    assert_streq("FOUR", ht_get(subject, "four"));
}

void hash_test() {
    test_set_value();
    test_chaining();
}
