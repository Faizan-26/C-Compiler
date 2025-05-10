# Compiler Project - Middle-End Implementation

This project implements a compiler with a focus on the middle-end phase, which involves converting the Abstract Syntax Tree (AST) into LLVM Intermediate Representation (IR) and applying optimizations.

## Project Structure

- `ast.c`: AST construction and manipulation
- `compiler.h`: Common definitions for the compiler
- `ir_generator.c` and `ir_generator.h`: Conversion of AST to LLVM IR
- `optimization.c` and `optimization.h`: Optimization passes for the LLVM IR
- `lexer.l`: Lexical analyzer
- `parser.y`: Parser and main program
- `Makefile`: Build system

## Features

### Intermediate Representation
- Converts AST to LLVM IR
- Handles variable declarations, assignments, and expressions
- Implements control flow structures (if, while, for)
- Manages function definitions and calls
- Handles basic arithmetic and logical operations

### Optimizations
- Constant folding: Evaluates constant expressions at compile time
- Dead code elimination: Removes unused variables and unreachable code
- Strength reduction: Replaces expensive operations with equivalent cheaper ones
- Common subexpression elimination: Eliminates redundant calculations

## Building and Running

To build the compiler:
```
make
```

To run the compiler on a source file:
```
./compiler source.c
```

To generate and output LLVM IR:
```
./compiler source.c --emit-ir
```

To apply optimizations:
```
./compiler source.c --emit-ir --optimize
```

## Testing

Example test files:
- `simple_test.c`: A basic test with function definition and call
- `test.c`: A more comprehensive test with various language features

## Optimization Report

When running with `--optimize`, the compiler generates an `optimization_report.txt` file that compares the unoptimized and optimized IR, showing size reduction and listing the applied optimizations. 