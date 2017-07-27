cmake_minimum_required(VERSION 3.7)
project(satchmo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/core/hashtable.c
        src/core/hashtable.h
        src/core/log.c
        src/core/log.h
        src/core/stack.c
        src/core/stack.h
        src/core/str.c
        src/core/str.h
        src/parser/expr.c
        src/parser/expr.h
        src/parser/func.c
        src/parser/func.h
        src/parser/lex.yy.c
        src/parser/module.c
        src/parser/module.h
        src/parser/parser.c
        src/parser/parser.h
        src/parser/stmt.c
        src/parser/stmt.h
        src/parser/token.c
        src/parser/token.h
        src/runtime/builtin.c
        src/runtime/builtin.h
        src/runtime/error.c
        src/runtime/error.h
        src/runtime/exec.c
        src/runtime/exec.h
        src/runtime/gc.h
        src/runtime/value.c
        src/runtime/value.h
        src/assert.c
        src/lex.yy.c
        src/main.c
        src/symbol.c
        src/symbol.h
        test/_test_exec.c
        test/_test_head.h
        test/hash_test.c
        test/stack_test.c
        test/stmt_test.c
        test/str_test.c
        test/symb_test.c
        test/test.h
        test/test_main.c)

add_executable(satchmo ${SOURCE_FILES})