#include <stdlib.h>
#include "stmt.h"

#include "test.h"

void test_new_stmt() {
    expr_t expr;
    stmt_t *subject = new_stmt(&expr);
    assert(subject->data == &expr);
    assert(subject->type == EXPR);
}

void test_new_stmt_list() {
    stmt_t *stmt = new_stmt(NULL);
    stmt_list_t *subject = new_stmt_list(stmt);

    assert(subject != NULL);
    assert(subject->capacity > 0);
    assert(subject->size = 1);
    assert(subject->stmt_array != NULL);

    stmt_t *stmt2 = new_stmt(NULL);
    stmt_list_t* list2 = append_stmt_list(subject, stmt2);
    assert(list2 == subject);

    assert(subject->size = 2);
    assert(subject->capacity >= subject->size);
}
