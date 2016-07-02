#include <stdlib.h>
#include <assert.h>

#include "core/hashtable.h"
#include "symbol.h"

static const int INIT_SIZE = 128;
static const int STACK_CAPACITY = 128;

symbol_t *new_symbol(str_t name, symbol_type_t type, void *object) {
    symbol_t* ret = (symbol_t*)malloc(sizeof(symbol_t));
    ret->name = name;
    ret->type = type;
    ret->object = object;
    ret->refs = 0;
    return ret;
}

symbtable_t *new_symbtable() {
    symbtable_t* ret = (symbtable_t*)malloc(sizeof(symbtable_t));
    assert(ret != NULL);
    ret->stack = new_stack(STACK_CAPACITY);
    assert(ret->stack != NULL);
    hashtable_t *global_frame = new_hashtable(INIT_SIZE);
    assert(global_frame != NULL);
    stack_push(ret->stack, (void*)global_frame);
    return ret;
}

void push_frame(symbtable_t *table) {
    hashtable_t *new_frame = new_hashtable(INIT_SIZE);
    stack_push(table->stack, (void*)new_frame);
}

void pop_frame(symbtable_t *table) {
    stack_pop(table->stack);
}

void put_symbol(symbtable_t *table, symbol_t *symbol) {
    hashtable_t *frame = (hashtable_t*)stack_peek(table->stack);
    ht_set(frame, symbol->name, symbol);
}

symbol_t *get_symbol(symbtable_t *table, str_t name) {

    stck_t *stack = table->stack;
    int index = stack->size - 1;
    while(index >= 0) {
        hashtable_t *frame = (hashtable_t*)stack->entries[index];
        symbol_t *symb = (symbol_t*)ht_get(frame, name);
        if (symb != NULL) {
            return symb;
        }
        --index;
    }
    return NULL;
}
