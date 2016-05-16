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
    ret->type = type;
    ret->object = object;
    return ret;
}


void put_symbol(symbtable_t *table, symbol_t *symbol) {
    ht_set(&table->hashtable, symbol->name.data, symbol);
}

symbol_t *get_symbol(symbtable_t *table, str_t name) {
    return (symbol_t*)ht_get(&table->hashtable, name.data);
}
