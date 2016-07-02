#include <stdlib.h>
#include <stdint.h>

#include "core/log.h"
#include "stack.h"

static int STACK_STATUS_OK = 0;
static int STACK_STATUS_OVER_CAPACITY = 1;

stck_t *new_stack(const uint32_t capacity) {
    if (capacity == 0) {
        error("Capacity needs to be above 0");
        return NULL;
    }
    stck_t *ret = (stck_t*)malloc(sizeof(stck_t));

    if (ret == NULL) {
        return NULL;
    }
    ret->entries = (void*)calloc(capacity, sizeof(void*));
    if (ret->entries == NULL) {
        return NULL;
    }

    ret->capacity = capacity;
    ret->size = 0;
    return ret;
}

int stack_push(stck_t *stack, void* entry) {
    if (stack->size >= stack->capacity) {
        return STACK_STATUS_OVER_CAPACITY;
    }
    stack->entries[stack->size] = entry;
    ++stack->size;
    return STACK_STATUS_OK;
}

void *stack_pop(stck_t *stack) {
    if (stack->size <= 0) {
        return NULL;
    } else {
        --stack->size;
        return stack->entries[stack->size];
    }
}

void *stack_peek(stck_t *stack) {
    if (stack->size < 0 || stack->size >= stack->capacity) {
        return NULL;
    } else {
        return stack->entries[stack->size - 1];
    }
}
