CC=clang
CC_OPTS=-Wall -std=c11 -O0 -g
TEST_OPTS=-Isrc -Itest
SRC=
SRC+=src/core/str.c
SRC+=src/expr.c
SRC+=src/func.c
SRC+=src/stmt.c
SRC+=src/token.c
SRC+=src/exec.c
SRC+=src/module.c
SRC+=src/hashtable.c
SRC+=src/symbol.c
SRC+=src/assert.c
SRC+=src/stack.c
SRC+=src/log.c

TEST_SRC=$(wildcard test/*_test.c)

TARGET=satchmo
TEST_TARGET=bin/run_tests

OBJ=$(patsubst src/%.c,bin/%.o,$(SRC))
TEST_OBJ=$(patsubst test/%.c,bin/%.o,$(TEST_SRC))

all: $(TARGET) test

$(TARGET): $(OBJ) bin/main.o bin/lex.yy.o bin/parser.o
	$(CC) $(CC_OPTS) -o $@ $^

bin/%.o: src/%.c
	@mkdir -p `dirname $@`
	$(CC) $(CC_OPTS) -c -o $@ $<


src/lex.yy.c: src/lang.lex src/parser.h
	flex --yylineno -o $@ $<

src/parser.h: src/parser.c
src/parser.c: src/lang.y
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
	rm -f src/lex.yy.c
	rm -f src/parser.c src/parser.h src/parser.output
	rm -f $(TARGET)
	rm -f test/_*

.PHONY: all clean test
