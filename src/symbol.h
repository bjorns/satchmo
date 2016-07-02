#pragma once

#include "core/str.h"

#include "stack.h"
#include "hashtable.h"

typedef enum {
    SYMB_FUNCTION,
    SYMB_OBJECT
} symbol_type_t;

typedef struct {
    str_t name;
    symbol_type_t type;
    void* object;

    uint32_t refs;
} symbol_t;

typedef struct {
    stck_t *stack;
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
 * Enter new context
 */
void push_frame(symbtable_t* table);

/**
 * Exit context
 */
void pop_frame(symbtable_t* table);

/**
 * Put symbol in table
 */
void put_symbol(symbtable_t *table, symbol_t *symbol);

symbol_t *get_symbol(symbtable_t *table, str_t name);
