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

static symbol_t *make_symbol(const char* name) {
    lval_t value;
    symbol_t *s1 = new_symbol(str(name), SYMB_OBJECT, &value);
    return s1;
}

void test_symb_frames() {

    symbtable_t *symbtable = new_symbtable();

    symbol_t *global = make_symbol("global_symbol");
    put_symbol(symbtable, global);
    push_frame(symbtable);

    symbol_t *local = make_symbol("local_symbol");
    put_symbol(symbtable, local);

    symbol_t *local_lookup = get_symbol(symbtable, str("local_symbol"));
    ASSERT(local_lookup != local);


    symbol_t *global_lookup = get_symbol(symbtable, str("global_symbol"));
    ASSERT(global_lookup != NULL);
    assert_streq("global_symbol", global_lookup->name);

}
