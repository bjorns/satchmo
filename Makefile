CC=clang
CC_OPTS=-Wall -std=c11 -O0 -g -Isrc
TEST_OPTS=-Isrc -Itest
SRC=
SRC+=src/core/log.c
SRC+=src/core/str.c
SRC+=src/core/hashtable.c
SRC+=src/core/stack.c
SRC+=src/parser/token.c
SRC+=src/parser/expr.c
SRC+=src/parser/func.c
SRC+=src/parser/module.c
SRC+=src/parser/stmt.c

SRC+=src/runtime/error.c
SRC+=src/runtime/exec.c

SRC+=src/symbol.c
SRC+=src/assert.c

TEST_SRC=$(wildcard test/*_test.c)

TARGET=satchmo
TEST_TARGET=bin/run_tests

OBJ=$(patsubst src/%.c,bin/%.o,$(SRC))
TEST_OBJ=$(patsubst test/%.c,bin/%.o,$(TEST_SRC))

all: $(TARGET) test

$(TARGET): $(OBJ) bin/main.o bin/parser/lex.yy.o bin/parser/parser.o
	$(CC) $(CC_OPTS) -o $@ $^

bin/%.o: src/%.c
	@mkdir -p `dirname $@`
	$(CC) $(CC_OPTS) -c -o $@ $<


src/parser/lex.yy.c: src/parser/lang.lex src/parser/parser.h
	flex --yylineno -o $@ $<

src/parser/parser.h: src/parser/parser.c
src/parser/parser.c: src/parser/lang.y
	bison -d -v -o $@ $<


# Run all tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): bin/test_main.o $(OBJ) $(TEST_OBJ)
	$(CC) $(CC_OPTS) -o $@ $^

bin/test_main.o: test/test_main.c bin test/_test_head.h test/_test_exec.c
	$(CC) $(CC_OPTS) -c -o $@ $<

bin/%_test.o: test/%_test.c bin
	$(CC) $(CC_OPTS) $(TEST_OPTS) -c -o $@ $<

# Generate test header of all methods
test/_test_head.h: test/*.c
	cat test/*.c | grep "void test_" | sed -e "s/{/;/g" > $@

# Generate method calls to all test methods
test/_test_exec.c: test/*_test.c
	cat test/*.c | grep "void test_" | sed -e "s/{/; ++i;/g" | sed -e "s/void //g" > $@

clean:
	rm -rf bin/
	rm -f src/parser/lex.yy.c
	rm -f src/parser/parser.c src/parser/parser.h src/parser/parser.output
	rm -f $(TARGET)
	rm -f test/_*

.PHONY: all clean test
