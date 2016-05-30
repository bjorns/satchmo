#include "stack.h"
#include "test.h"

void test_stack() {
    stck_t *stack = new_stack(10);

    int x = 4711;

    int result = stack_push(stack, (void*) &x);
    ASSERT(result == 0);

    int *y = (int*)stack_pop(stack);

    ASSERT(*y == 4711);
}

void test_stack_overflow() {
    stck_t *stack = new_stack(3);

    int result;

    int x0 = 4711;
    result = stack_push(stack, (void*) &x0);
    ASSERT(result == 0);

    int x1 = 4712;
    result = stack_push(stack, (void*) &x1);
    ASSERT(result == 0);

    int x2 = 4713;
    result = stack_push(stack, (void*) &x2);
    ASSERT(result == 0);

    int x3 = 4714;
    result = stack_push(stack, (void*) &x3);
    ASSERT(result != 0);

    int *y = (int*)stack_pop(stack);

    // Last push failed
    ASSERT(*y == 4713);
}
