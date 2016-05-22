#include <stdlib.h>
#include <stdio.h>

#include "symbol.h"
#include "expr.h"
#include "str.h"

#include "assert.h"

void test_create_symbol() {
    lval_t value;
    symbol_t *s = new_symbol(str("symbol_name"), SYMB_OBJECT, &value);
    ASSERT(s != NULL);
    ASSERT(str_eq(str("symbol_name"), s->name));
    ASSERT(SYMB_OBJECT == s->type);
    ASSERT(&value == s->object);
}

void test_symbol_table_access() {
    str_t name = str("symbol_name");
    symbtable_t *symbtable = new_symbtable();
    lval_t value;
    symbol_t *s1 = new_symbol(name, SYMB_OBJECT, &value);

    put_symbol(symbtable, s1);
    symbol_t *s2 = get_symbol(symbtable, name);
    ASSERT(s2 != NULL);

    assert_streq("symbol_name", s2->name);
}
