# C Compiler Project Report

## Overview

This report provides a comprehensive overview of our C compiler project, detailing each phase from frontend to backend with a focus on the optimization capabilities. The compiler follows the traditional compiler design pattern, with distinct phases for lexical analysis, syntax analysis, semantic analysis, intermediate code generation, optimization, and code emission.

## Project Structure

The project is organized into the following key components:

1. **Lexical Analysis**: Implemented using Flex in `lexer.l`
2. **Syntax Analysis**: Implemented using Bison in `parser.y`
3. **Abstract Syntax Tree (AST)**: Defined in `compiler.h` and implemented in `ast.c`
4. **IR Generation**: LLVM IR generation in `ir_generator.c`
5. **Optimization**: LLVM-based optimizations in `optimization.c`
6. **Backend**: Assembly generation in `backend.c`

## Compiler Construction Concepts Used

### Parser Type: Bottom-Up LR(1) Parser

This compiler uses Bison (a GNU implementation of Yacc) which implements a **bottom-up LR(1) parser**. Key characteristics of this parsing approach include:

- **Bottom-up parsing**: The parser starts with individual tokens and works upward to build the parse tree
- **LR(1)**: The parser is "Left-to-right, Rightmost derivation" with 1 token lookahead
- **Shift-reduce technique**: Uses shift and reduce actions based on parsing tables
- **Handles context-free grammars**: Can parse a wide range of programming language syntax
- **Better error detection**: LR parsers can detect syntax errors earlier than top-down parsers

The LR(1) parser is particularly suited for programming languages due to its ability to handle operator precedence and associativity naturally, which is important for parsing expressions in C.

### Symbol Table Implementation

The compiler implements a symbol table for tracking identifiers (variables and functions):

- **Scope management**: Symbols are organized by their lexical scope
- **Name resolution**: Finds the appropriate declaration for each identifier reference
- **Type checking**: Stores and retrieves type information for compile-time type checking
- **Implementation**: Uses a simplified array-based approach in the IR context

### Type System

The compiler supports a basic type system with:

- **Basic types**: int, float, bool, void
- **Type checking**: Ensures operations have compatible types
- **Type conversion**: Implicit conversions are handled during IR generation

### Control Flow Representation

Control flow is represented in both the AST and LLVM IR:

- **AST**: Control flow nodes for if-statements, loops, and function calls
- **LLVM IR**: Uses basic blocks and branch instructions to represent control flow
- **CFG (Control Flow Graph)**: Implicitly built during IR generation

## Frontend Analysis

### Lexical Analysis (Scanner)

The lexical analyzer (`lexer.l`) uses Flex to tokenize the source code, identifying:

- Keywords (`int`, `float`, `bool`, `if`, `else`, `while`, `for`, `return`)
- Identifiers (variable and function names)
- Literals (integers, floats, booleans, strings)
- Operators and punctuation

Regular expressions in the lexer define patterns for each token type, and actions produce token values for the parser.

### Syntax Analysis (Parser)

The parser (`parser.y`) uses Bison to define a context-free grammar for our C-like language. It:

- Defines production rules for all language constructs
- Builds an Abstract Syntax Tree (AST) during parsing
- Handles operator precedence and associativity using Bison's capabilities
- Reports syntax errors with line numbers

### Abstract Syntax Tree (AST)

The AST serves as an intermediate representation between parsing and code generation:

- **Node hierarchy**: Different node types for different language constructs
- **Tree structure**: Represents the nesting of statements and expressions
- **Visitation**: Supports traversal for semantic analysis and code generation
- **Visualization**: AST can be visualized using GraphViz (via `dot`)

## Intermediate Code Generation

The IR generator (`ir_generator.c`) translates the AST into LLVM IR:

- **LLVM API usage**: Uses the LLVM C API to generate IR
- **SSA form**: Generated IR is in Static Single Assignment form
- **Basic blocks**: Control flow is represented using basic blocks
- **Instruction selection**: Maps AST operations to appropriate LLVM instructions
- **Memory allocation**: Allocates stack space for local variables

## Optimization Techniques

The compiler implements several optimization techniques through `optimization.c`:

### 1. Constant Folding

- **Description**: Evaluates constant expressions at compile time
- **Example**: `3 + 5` becomes `8`
- **Implementation**: Uses LLVM's constant folding pass
- **Benefits**: Reduces runtime computation and code size

### 2. Dead Code Elimination (DCE)

- **Description**: Removes unused code that doesn't affect program behavior
- **Targets**: Unused variables, unreachable code, unused computations
- **Implementation**: Uses LLVM's DCE pass
- **Benefits**: Reduces code size and can improve cache utilization

### 3. Strength Reduction

- **Description**: Replaces expensive operations with equivalent but cheaper ones
- **Primary example**: `x * 8` becomes `x << 3` (multiplication to shift)
- **Implementation**: 
  - Custom implementation during IR generation
  - Also leverages LLVM's strength reduction pass
- **Benefits**: Improves runtime performance by using less expensive CPU instructions

### 4. Common Subexpression Elimination (CSE)

- **Description**: Identifies and eliminates redundant computations
- **Approach**: Stores and reuses results of repeated expressions
- **Implementation**: Uses LLVM's GVN (Global Value Numbering) pass
- **Benefits**: Reduces both code size and execution time

### 5. Loop-Invariant Code Motion (LICM)

- **Description**: Moves code that doesn't change inside loops to outside the loop
- **Implementation**: Uses LLVM's LICM pass
- **Benefits**: Reduces loop execution time by computing invariant expressions only once

### Optimization Implementation Details

- **PassBuilder API**: Uses LLVM's modern PassBuilder API for optimizations
- **Optimization levels**: Supports multiple optimization levels (None, Basic, Aggressive, Full)
- **Optimization report**: Generates detailed reports comparing unoptimized and optimized IR

## Backend Code Generation

The backend (`backend.c`) converts LLVM IR to target-specific assembly code:

- **Target architecture**: Currently generates x86-64 assembly
- **Instruction selection**: Maps LLVM IR instructions to x86-64 instructions
- **Register allocation**: Maps IR virtual registers to physical registers
- **Stack frame management**: Allocates stack space for local variables

## Project Requirements and Setup

### Prerequisites

To build and run the compiler, you need:

1. **C/C++ Development tools**:
   - GCC or Clang compiler
   - GNU Make

2. **LLVM Development Libraries**:
   - LLVM core libraries (version 10.0 or higher recommended)
   - LLVM development headers

3. **Flex and Bison**:
   - Flex (fast lexical analyzer generator)
   - Bison (parser generator)

4. **Visualization Tools** (optional):
   - GraphViz (for AST visualization)

### Installation on Ubuntu/Debian

```bash
# Install required packages
sudo apt update
sudo apt install build-essential llvm-dev clang flex bison graphviz
```

### Building the Compiler

```bash
# Clone the repository
git clone <repository-url>
cd C-Compiler

# Build the compiler
make
```

### Running the Compiler

The Makefile provides several targets for testing different compiler phases:

```bash
# Test frontend (lexical and syntax analysis)
make frontend

# Test middle-end (IR generation and optimization)
make middleend

# Test backend (assembly generation)
make backend_test

# Test complete pipeline (frontend -> middle-end -> backend)
make full_pipeline
```

For testing with specific files:

```bash
# Compile a custom file
./compiler your_file.c --emit-ir --optimize
./backend your_file.opt.ll -o your_file.s
gcc -o your_file_executable your_file.s
```

### Troubleshooting Common Issues

1. **Segmentation faults in middle-end**:
   - Use `make middleend_simple` which uses a simpler test case
   - Avoid complex function calls in test programs

2. **LLVM version compatibility**:
   - Ensure your LLVM installation matches the expected version
   - Check include paths in Makefile if compilation fails

## Current Limitations and Future Work

### Current Limitations

1. **Function Call Handling**: The compiler has some limitations with complex function calls.
2. **Limited Type System**: No support for arrays, pointers, or user-defined types.
3. **Limited Standard Library**: No comprehensive standard library implementation.

### Future Work

1. **Enhanced Type System**: Add support for arrays, structs, and pointers.
2. **Improved Error Reporting**: More detailed error messages with suggestions.
3. **Additional Optimizations**: Implement function inlining and vectorization.
4. **Multi-target Support**: Generate code for multiple target architectures.

## Conclusion

This C compiler project successfully implements the key components of a modern compiler, from lexical analysis through optimization to code generation. It demonstrates important compiler construction concepts including bottom-up parsing, symbol table management, type checking, and various optimization techniques.

The modular design allows for easy extension and enhancement, making it a solid foundation for future compiler development. The integration with LLVM provides a robust optimization framework that significantly improves the quality of the generated code.

While there are some limitations in the current implementation, particularly around complex function calls and advanced language features, the compiler successfully compiles and optimizes simple C programs, demonstrating the effectiveness of the applied compiler construction principles. 