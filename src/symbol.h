#pragma once
#include "str.h"
#include "hashtable.h"

typedef enum {
    SYMB_FUNCTION,
    SYMB_OBJECT
} symbol_type_t;

typedef struct {
    str_t name;
    symbol_type_t type;
    void* object;
} symbol_t;

typedef struct {
    hashtable_t hashtable;
} symbtable_t;

/**
 * Put symbol in table
 */
symbol_t *new_symbol(str_t name, symbol_type_t type, void *object);

/**
 * Create new symbol table
 */
symbtable_t *new_symbtable();

/**
 * Put symbol in table
 */
void put_symbol(symbtable_t *table, symbol_t *symbol);

symbol_t *get_symbol(symbtable_t *table, str_t name);
