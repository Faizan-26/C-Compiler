#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>

// Optimization level
typedef enum {
    OPT_NONE = 0,        // No optimizations
    OPT_BASIC = 1,       // Basic optimizations
    OPT_AGGRESSIVE = 2,  // Aggressive optimizations
    OPT_FULL = 3         // Full optimizations
} OptimizationLevel;

// Apply optimizations with the given optimization level
// This will use LLVM's built-in optimization passes
void apply_optimizations(LLVMModuleRef module, OptimizationLevel level);

// Compare unoptimized and optimized IR and generate a report
void generate_optimization_report(const char* unoptimized_ir_file, const char* optimized_ir_file, const char* report_file);

#endif // OPTIMIZATION_H 