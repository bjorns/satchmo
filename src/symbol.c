#include <stdlib.h>

#include "hashtable.h"
#include "symbol.h"

static const int INIT_SIZE = 128;

symbtable_t *new_symbtable() {
    symbtable_t* ret = (symbtable_t*)malloc(sizeof(symbtable_t));

    ret->hashtable = *new_hashtable(INIT_SIZE);
    return ret;
}

symbol_t *new_symbol(str_t name, symbol_type_t type, void *object) {
    symbol_t* ret = (symbol_t*)malloc(sizeof(symbol_t));
    ret->name = name;
    return ret;
}
