# Makefile for compiler project

CC = gcc
CFLAGS = -Wall -g

all: compiler

compiler: lex.yy.c parser.tab.c ast.c
	$(CC) $(CFLAGS) -o compiler lex.yy.c parser.tab.c ast.c -lfl

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean:
	rm -f compiler lex.yy.c parser.tab.c parser.tab.h *.o

test: compiler
	./compiler test.c