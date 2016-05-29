#pragma once
#include <stdint.h>

typedef struct {
    uint32_t capacity;

    int32_t size;

    void **entries;
} stck_t;

stck_t *new_stack(const uint32_t capacity);

int stack_push(stck_t *stack, void* entry);

void *stack_pop(stck_t *stack);

void *stack_peek(stck_t *stack);
