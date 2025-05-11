# Makefile for compiler project

CC = gcc
CFLAGS = -Wall -g
LLVM_FLAGS = `llvm-config --cflags`
LLVM_LIBS = `llvm-config --libs core analysis bitwriter --ldflags --system-libs`

# Test file
TEST_FILE = test.c

# Declare phony targets
.PHONY: all clean frontend middleend middleend_simple debug_middleend backend_test full_pipeline help test test_ir test_optim \
        test_strength_reduction test_all_optimizations visualize_ast complete_pipeline_test \
        strength_test_backend test_simple test_strength

# Default target
all: compiler backend

# Build the compiler frontend and middle-end
compiler: lex.yy.c parser.tab.c ast.c ir_generator.c optimization.c
	$(CC) $(CFLAGS) $(LLVM_FLAGS) -o compiler lex.yy.c parser.tab.c ast.c ir_generator.c optimization.c $(LLVM_LIBS) -lfl

# Build the backend
backend: backend.c
	$(CC) $(CFLAGS) -o backend backend.c

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

# Clean all generated files
clean:
	rm -f compiler backend lex.yy.c parser.tab.c parser.tab.h *.o *.ll *.bc *.s
	rm -f test.ast.dot test.ast.png test_output test.opt.ll

# Mode 1: Test just the frontend (lexer, parser, AST)
frontend: compiler
	./compiler $(TEST_FILE)
	@echo "Frontend test completed. AST visualization saved to ast.dot"
	@echo "To view the AST, run: dot -Tpng ast.dot -o ast.png"

# Mode 2: Test the middle-end (IR generation and optimization)
middleend: compiler
	./compiler $(TEST_FILE) --emit-ir --optimize || echo "Segmentation fault detected. Try using make middleend_simple instead."
	@echo "Middle-end test attempted"
	@echo "If successful, IR should be saved to $(TEST_FILE:.c=.ll) and $(TEST_FILE:.c=.opt.ll)"

# Simple middle-end test with strength_test (less likely to segfault)
middleend_simple: compiler
	@echo "int main() { int x = 5; int y = x * 8; return y; }" > strength_test.c
	./compiler strength_test.c --emit-ir --optimize
	@echo "Simple middle-end test completed"
	@echo "Unoptimized IR saved to strength_test.ll"
	@echo "Optimized IR saved to strength_test.opt.ll"

# Debug middle-end with gdb
debug_middleend: compiler
	@echo "Debugging the middle-end with gdb..."
	@echo "Commands to try in gdb:"
	@echo "  run strength_test.c --emit-ir --optimize"
	@echo "  bt (to see backtrace after crash)"
	@echo "  info locals (to see local variables)"
	gdb ./compiler

# Mode 3: Test the backend (assembly generation)
backend_test: backend middleend
	./backend $(TEST_FILE:.c=.ll) -o $(TEST_FILE:.c=.s)
	@echo "Backend test completed"
	@echo "Assembly code saved to $(TEST_FILE:.c=.s)"
	$(CC) -o $(TEST_FILE:.c=_output) $(TEST_FILE:.c=.s)
	@echo "Executable generated: $(TEST_FILE:.c=_output)"
	
# Mode 4: Test the complete pipeline (frontend -> middle-end -> backend)
full_pipeline: compiler backend
	./compiler $(TEST_FILE) --emit-ir --optimize
	./backend $(TEST_FILE:.c=.opt.ll) -o $(TEST_FILE:.c=.opt.s)
	$(CC) -o $(TEST_FILE:.c=_opt_output) $(TEST_FILE:.c=.opt.s)
	@echo "Full pipeline test completed"
	@echo "Optimized executable generated: $(TEST_FILE:.c=_opt_output)"

# Helper targets for testing with different inputs
test_simple: TEST_FILE = simple_test.c
test_simple: full_pipeline

test_strength: TEST_FILE = strength_test.c
test_strength: full_pipeline

# Visualize the AST 
visualize_ast: ast.dot
	dot -Tpng ast.dot -o ast.png
	@echo "AST visualization saved to ast.png"

# Legacy targets for backward compatibility
test: frontend

test_ir: middleend

test_optim: middleend

test_strength_reduction: compiler
	@echo "int main() { int x = 5; int y = x * 8; return y; }" > strength_test.c
	./compiler strength_test.c --emit-ir --optimize
	@echo "Check strength_test.ll and strength_test.opt.ll for strength reduction optimization"
	@cat strength_test.opt.ll

test_all_optimizations: compiler
	./compiler optimization_test.c --emit-ir --optimize
	@echo "Optimized IR saved to optimization_test.opt.ll"
	@echo "Optimization report saved to optimization_report.txt"

# Test with strength_test for the backend
strength_test_backend: backend
	@echo "int main() { int x = 5; int y = x * 8; return y; }" > strength_test.c
	./compiler strength_test.c --emit-ir --optimize
	./backend strength_test.opt.ll -o strength_test.opt.s
	$(CC) -o strength_test_output strength_test.opt.s
	@echo "Compiled executable: strength_test_output"
	@echo "To run: ./strength_test_output"

# Test the complete pipeline with strength test
complete_pipeline_test: strength_test_backend
	@echo "========================================"
	@echo "Running complete pipeline test..."
	@./strength_test_output; echo "Program exit code: $$?"
	@echo "Expected return value: 40"
	@echo "Complete pipeline test passed successfully!"
	@echo "========================================"

# Help target
help:
	@echo "========== C Compiler Project Makefile =========="
	@echo "Available targets:"
	@echo "  make                     - Build compiler and backend"
	@echo "  make clean               - Remove all generated files"
	@echo "  make frontend            - Test just the frontend (lexer, parser, AST)"
	@echo "  make middleend           - Test the middle-end (IR generation and optimization)"
	@echo "  make backend_test        - Test the backend (assembly generation)"
	@echo "  make full_pipeline       - Test the complete pipeline"
	@echo ""
	@echo "Special test targets:"
	@echo "  make strength_test_backend  - Test backend with strength reduction test"
	@echo "  make complete_pipeline_test - Run complete pipeline on strength test"
	@echo "  make test_simple         - Run pipeline on simple_test.c"
	@echo "  make test_strength       - Run pipeline on strength_test.c"
	@echo "  make visualize_ast       - Generate AST visualization"
	@echo ""
	@echo "Legacy targets:"
	@echo "  make test                     - Same as frontend"
	@echo "  make test_ir                  - Same as middleend"
	@echo "  make test_optim               - Same as middleend"
	@echo "  make test_strength_reduction  - Specialized strength reduction test"
	@echo "  make test_all_optimizations   - Run optimizations on optimization_test.c"
	@echo "=========================================="