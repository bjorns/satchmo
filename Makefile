CC=clang
CC_OPTS=-Wall -std=c11 -O0 -g

SRC=
SRC+=src/main.c
SRC+=src/expr.c
SRC+=src/stmt.c
SRC+=src/token.c

TARGET=foundation

OBJ=$(patsubst src/%.c,bin/%.o,$(SRC))

all: $(TARGET)

bin:
	mkdir -p $@

bin/%.o: src/%.c bin
	$(CC) $(CC_OPTS) -c -o $@ $<

src/lex.yy.c: src/lang.lex src/parser.c
	flex --yylineno -o $@ $<

src/parser.c: src/lang.y
	bison -d -v -o $@ $<

$(TARGET): $(OBJ) bin/lex.yy.o bin/parser.o
	$(CC) $(CC_OPTS) -o foundation $^

clean:
	rm -rf bin/
	rm -f src/lex.yy.c
	rm -f src/parser.c src/parser.h src/parser.output
	rm -f $(TARGET)
