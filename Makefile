CC=gcc


SRC=
SRC+=src/main.c
SRC+=src/expr.c

TARGET=foundation

OBJ=$(patsubst src/%.c,%.o,$(SRC))

all: $(TARGET)

%.o: src/%.c
	$(CC) -Wall -c -o $@ $<

src/lex.yy.c: src/lang.lex src/parser.c
	flex --yylineno -o $@ $<

src/parser.c: src/lang.y
	bison -d -v -o $@ $<

$(TARGET): $(OBJ) lex.yy.o parser.o
	$(CC) -o foundation $^

clean:
	rm -f *.o
	rm -f src/lex.yy.c
	rm -f src/parser.c src/parser.h
	rm -f $(TARGET)
