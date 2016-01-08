CC=clang
CC_OPTS=-Wall -std=c11 -O0 -g

SRC=
SRC+=src/main.c
SRC+=src/expr.c
SRC+=src/stmt.c
SRC+=src/token.c

TARGET=foundation

OBJ=$(patsubst src/%.c,%.o,$(SRC))

all: $(TARGET)

%.o: src/%.c
	$(CC) $(CC_OPTS) -c -o $@ $<

src/lex.yy.c: src/lang.lex src/parser.c
	flex --yylineno -o $@ $<

src/parser.c: src/lang.y
	bison -d -v -o $@ $<

$(TARGET): $(OBJ) lex.yy.o parser.o
	$(CC) $(CC_OPTS) -o foundation $^

clean:
	rm -f *.o
	rm -f src/lex.yy.c
	rm -f src/parser.c src/parser.h src/parser.output
	rm -f $(TARGET)
