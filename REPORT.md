# Compiler Project Report

## Overview

This report provides a comprehensive overview of the compiler project, detailing each phase from frontend to backend with a focus on the optimization capabilities. The compiler follows the traditional compiler design pattern, with distinct phases for lexical analysis, syntax analysis, semantic analysis, intermediate code generation, optimization, and code emission.

## Project Structure

The project is organized into the following key components:

1. **Lexical Analysis**: Implemented using Flex in `lexer.l`
2. **Syntax Analysis**: Implemented using Bison in `parser.y`
3. **Abstract Syntax Tree (AST)**: Defined in `compiler.h` and implemented in `ast.c`
4. **IR Generation**: LLVM IR generation in `ir_generator.c`
5. **Optimization**: LLVM-based optimizations in `optimization.c`

## Frontend Analysis

### Lexical Analysis

The lexical analyzer (`lexer.l`) tokenizes the source code, identifying keywords, identifiers, literals, and operators. It supports:

- C-like syntax with keywords such as `int`, `float`, `bool`, `if`, `else`, `while`, `for`, `return`
- Numeric literals (integers and floating-point numbers)
- Boolean literals (`true` and `false`)
- String literals
- Various operators for arithmetic, comparison, and logic operations

### Syntax Analysis

The parser (`parser.y`) builds a parse tree from the token stream provided by the lexer. It defines the grammar for:

- Variable declarations with optional initialization
- Function declarations with parameters
- Control flow statements (if-else, while, for)
- Expressions (arithmetic, relational, logical)
- Function calls

The parser constructs an Abstract Syntax Tree (AST) during the parsing process, which serves as the intermediate representation for further analysis and code generation.

### Abstract Syntax Tree (AST)

The AST is implemented with a recursive node structure in `compiler.h` and `ast.c`. Each node represents a construct in the source language:

- Program nodes contain function declarations
- Function nodes contain parameter lists and blocks
- Blocks contain statements
- Statements include declarations, if-else, loops, returns, etc.
- Expressions include binary operations, unary operations, assignments, function calls, etc.

The AST visualization is generated using GraphViz, allowing for visual inspection of the parse tree.

### Semantic Analysis

Semantic analysis includes type checking and symbol table management. The compiler:

- Validates that expressions have compatible types
- Ensures variables are declared before use
- Verifies function calls have the correct number and type of arguments
- Manages scope for variable and function declarations

## Intermediate Code Generation

The IR generator (`ir_generator.c`) translates the AST into LLVM IR, which is a low-level but platform-independent representation. Features of the IR generation include:

- Translation of AST nodes to corresponding LLVM IR instructions
- Creation of basic blocks for control flow
- Allocation of memory for variables
- Function parameter handling
- Expression evaluation and type conversions

The IR generator also implements some basic optimizations during IR construction, such as strength reduction for multiplications by powers of 2 (converting to bit shifts).

## Optimization Phase

The optimization phase, implemented in `optimization.c`, leverages LLVM's optimization passes to improve the generated code. This part of the project has been upgraded to use LLVM's built-in optimization infrastructure through the Pass Builder API.

### Implemented Optimizations

1. **Constant Folding**: Evaluates constant expressions at compile time.
   - Example: `3 + 5` is folded to `8`
   - This reduces runtime computation and code size

2. **Dead Code Elimination**: Removes unused code.
   - Unused variables
   - Unreachable code blocks
   - Assignments to variables that are never read

3. **Strength Reduction**: Replaces expensive operations with equivalent but cheaper ones.
   - Multiplication by powers of 2 is converted to bit shifts
   - Example: `x * 8` becomes `x << 3`
   - This significantly improves runtime performance

4. **Common Subexpression Elimination (CSE)**: Identifies and eliminates redundant computations.
   - If the same expression is computed multiple times, the result is stored and reused
   - This reduces both code size and execution time

5. **Loop-Invariant Code Motion (LICM)**: Moves code outside loops when it doesn't change inside the loop.
   - Computations that are invariant across loop iterations are hoisted out
   - This reduces the number of instructions executed during loop iterations

### Optimization Implementation

The optimization phase is implemented using LLVM's PassBuilder API, which provides access to LLVM's suite of optimization passes. The implementation:

1. Creates a PassBuilder options object to configure optimization settings
2. Selects appropriate optimization passes based on the optimization level
3. Executes the optimization passes on the LLVM module
4. Generates an optimization report comparing the unoptimized and optimized IR

The optimization level is configurable, allowing for different optimization strategies:
- `OPT_NONE`: No optimizations
- `OPT_BASIC`: Basic optimizations including constant folding and dead code elimination
- `OPT_AGGRESSIVE`: More aggressive optimizations including strength reduction and CSE
- `OPT_FULL`: All optimizations, including LICM and others

### Optimization Report Generation

The optimizer generates a report comparing the unoptimized and optimized IR code. The report includes:

- Size comparison before and after optimization
- Percentage reduction in code size
- List of applied optimizations with detailed statistics:
  - Number of constant expressions folded
  - Number of dead store operations eliminated
  - Number of strength reductions applied
  - Number of common subexpressions eliminated
  - Loop optimizations applied

## Testing

The project includes various test files to verify the functionality of different phases:

1. `test.c`: A general test file that exercises all language features
2. `strength_test.c`: Specifically tests strength reduction optimization
3. `optimization_test.c`: Tests various optimization techniques

The Makefile provides multiple testing targets:
- `make test`: Basic compilation test
- `make test_ir`: Tests IR generation
- `make test_optim`: Tests IR generation with optimization
- `make test_strength_reduction`: Specific test for strength reduction
- `make test_all_optimizations`: Tests all optimization techniques

## Current Issues and Future Work

### Issues

1. **Function Call Handling**: The IR generator has significant issues with handling function calls. In our testing:
   - Function declarations are correctly parsed and added to the AST
   - However, when trying to call these functions, the IR generator fails to recognize them
   - This results in "Unknown function" errors during IR generation
   - For example, in `optimization_test.c`, the functions `constant_fold_test` and `strength_reduction_test` are defined but cannot be called in `main()`
   - This is a critical issue affecting the usability of the compiler

2. **Symbol Resolution**: There are issues with the symbol resolution mechanism:
   - While variables are correctly resolved within functions
   - Functions are not properly added to the symbol table for resolution
   - This appears to be an issue in the semantic analysis phase or in the symbol table implementation
   - The error manifests as "Undefined function" errors despite the functions being defined

3. **Memory Management**: While we've fixed the segmentation faults in the optimization report generation:
   - There may still be memory management issues in other parts of the code
   - Memory leaks might occur during complex compilation tasks
   - More thorough testing with memory analyzers like Valgrind would be beneficial

### Future Work

1. **Fix Current Issues**:
   - Fix the function call handling in the IR generator by properly implementing function lookup
   - Enhance the symbol table to properly register and resolve function symbols
   - Conduct comprehensive memory leak analysis and fix any leaking resources

2. **Additional Optimizations**:
   - Implement more advanced loop optimizations
   - Add inlining capabilities for small functions
   - Implement constant propagation across function boundaries

3. **Backend Enhancements**:
   - Add target-specific code generation
   - Implement register allocation
   - Add machine-dependent optimizations

4. **Language Features**:
   - Expand the type system to include arrays and structures
   - Add support for pointers and dynamic memory allocation
   - Implement a more comprehensive standard library

## Conclusion

The compiler project successfully implements all major phases of a compiler, from lexical analysis to optimization. The frontend components (lexer, parser, AST) are robust and handle a substantial subset of C-like syntax. The IR generation leverages LLVM for portability and optimization capabilities.

The optimization phase has been successfully upgraded to use LLVM's built-in optimization infrastructure, providing powerful optimizations like constant folding, dead code elimination, strength reduction, and common subexpression elimination.

However, there are significant issues with function call handling that need to be addressed to make the compiler fully functional. Despite these limitations, the compiler provides a solid foundation for future enhancements and extensions, particularly in the optimization phase where LLVM's powerful optimization framework is effectively utilized.

## Key Findings and Accomplishments

1. **Successful Integration of LLVM Optimizations**: 
   - Successfully replaced custom optimization code with LLVM's more robust PassBuilder API
   - Implemented a configurable optimization system with multiple optimization levels
   - Verified that key optimizations (constant folding, DCE, strength reduction) work correctly

2. **Proven Strength Reduction Capability**:
   - Successfully demonstrated strength reduction optimization converting multiplications by powers of 2 to bit shifts
   - For example, `x * 8` is correctly transformed to `x << 3`
   - This optimization works both at the IR generation level and through LLVM passes

3. **Robust Optimization Reporting**:
   - Fixed critical segmentation faults in the optimization report generation
   - Implemented a comprehensive optimization report that details:
     - Code size reduction
     - Number of optimizations applied by category
     - Specific details of optimization effects

4. **Effective Constant Folding**:
   - Demonstrated that constant expressions like `3 + 5` are correctly folded to `8` at compile time
   - In the optimized IR, complex expressions with constant operands are completely evaluated

5. **Verification of AST Construction**:
   - Confirmed that the lexer and parser correctly build an AST for all language constructs
   - The AST properly represents control flow, function declarations, and expressions

6. **Identified Critical Areas for Improvement**:
   - Pinpointed function call resolution as the major weakness of the current implementation
   - Identified issues in the symbol table implementation for function resolution
   - These findings provide clear direction for future development 