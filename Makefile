CC=clang
CC_OPTS=-Wall -std=c11 -O0 -g
TEST_OPTS=-Isrc
SRC=
SRC+=src/expr.c
SRC+=src/stmt.c
SRC+=src/token.c
SRC+=src/exec.c
SRC+=src/module.c
SRC+=src/str.c

TEST_SRC=
TEST_SRC+=test/str_test.c

TARGET=satchmo
TEST_TARGET=bin/run_tests

OBJ=$(patsubst src/%.c,bin/%.o,$(SRC))
TEST_OBJ=$(patsubst test/%.c,bin/%.o,$(TEST_SRC))

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

bin:
	mkdir -p $@

bin/%_test.o: test/%_test.c bin
	$(CC) $(CC_OPTS) $(TEST_OPTS) -c -o $@ $<

bin/%.o: src/%.c bin
	$(CC) $(CC_OPTS) -c -o $@ $<


src/lex.yy.c: src/lang.lex src/parser.c
	flex --yylineno -o $@ $<

src/parser.c: src/lang.y
	bison -d -v -o $@ $<

$(TARGET): $(OBJ) bin/main.o bin/lex.yy.o bin/parser.o
	$(CC) $(CC_OPTS) -o $@ $^

$(TEST_TARGET): bin/test_main.o $(OBJ) $(TEST_OBJ)
	$(CC) $(CC_OPTS) -o $@ $^

clean:
	rm -rf bin/
	rm -f src/lex.yy.c
	rm -f src/parser.c src/parser.h src/parser.output
	rm -f $(TARGET)
