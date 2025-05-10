#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include "compiler.h"

// Context for IR generation
typedef struct IRContext {
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    LLVMValueRef current_function;
    
    // Symbol table mapping
    LLVMValueRef* named_values;
    int named_values_count;
    int named_values_capacity;
} IRContext;

// Initialize the IR generation context
IRContext* create_ir_context(const char* module_name);

// Free resources used by the IR context
void destroy_ir_context(IRContext* context);

// Generate LLVM IR from the AST
LLVMModuleRef generate_ir(ASTNode* ast_root, const char* module_name);

// Dump the generated LLVM IR to a file
void dump_ir(LLVMModuleRef module, const char* filename);

// Get the default data layout string for the target platform
const char* get_default_data_layout(void);

// Get a string representation of the target triple for the host machine
const char* get_host_target_triple(void);

// Print the IR to stderr
void print_ir(LLVMModuleRef module);

// Apply optimizations to the module
void optimize_module(LLVMModuleRef module, int opt_level);

#endif // IR_GENERATOR_H 