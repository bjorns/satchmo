CC=gcc


SRC=
SRC+=src/main.c

TARGET=foundation

OBJ=$(patsubst src/%.c,%.o,$(SRC))

all: $(TARGET)

%.o: src/%.c
	$(CC) -Wall -c -o $@ $<

src/lex.yy.c: src/lang.lex
	flex --yylineno -o $@ src/lang.lex

$(TARGET): main.o lex.yy.o
	$(CC) -o foundation $^

clean:
	rm -f *.o
	rm -f src/lex.yy.c
	rm -f $(TARGET)
