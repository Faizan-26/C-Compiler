# Makefile for compiler project

CC = gcc
CFLAGS = -Wall -g
LLVM_FLAGS = `llvm-config --cflags`
LLVM_LIBS = `llvm-config --libs core analysis bitwriter --ldflags --system-libs`

all: compiler

compiler: lex.yy.c parser.tab.c ast.c ir_generator.c optimization.c
	$(CC) $(CFLAGS) $(LLVM_FLAGS) -o compiler lex.yy.c parser.tab.c ast.c ir_generator.c optimization.c $(LLVM_LIBS) -lfl

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean:
	rm -f compiler lex.yy.c parser.tab.c parser.tab.h *.o *.ll *.bc

test: compiler
	./compiler test.c

test_ir: compiler
	./compiler test.c --emit-ir
	@echo "IR saved to test.ll"

test_optim: compiler
	./compiler test.c --emit-ir --optimize
	@echo "Optimized IR saved to test.opt.ll"
	@echo "Optimization report saved to optimization_report.txt"

# Test with a specific case for strength reduction
test_strength_reduction: compiler
	@echo "int main() { int x = 5; int y = x * 8; return y; }" > strength_test.c
	./compiler strength_test.c --emit-ir --optimize
	@echo "Check strength_test.ll and strength_test.opt.ll for strength reduction optimization"
	@cat strength_test.opt.ll

# Test all optimizations
test_all_optimizations: compiler
	./compiler optimization_test.c --emit-ir --optimize
	@echo "Optimized IR saved to optimization_test.opt.ll"
	@echo "Optimization report saved to optimization_report.txt"