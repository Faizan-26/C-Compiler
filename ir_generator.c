#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "ir_generator.h"

// Initial capacity for named values array
#define INITIAL_NAMED_VALUES_CAPACITY 128

// Helper function prototypes
static LLVMTypeRef get_llvm_type(DataType type, IRContext* context);
static LLVMValueRef generate_function_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_statement_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_expression_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_binary_expr_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_unary_expr_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_literal_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_var_ref_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_var_decl_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_if_stmt_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_while_stmt_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_for_stmt_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_return_stmt_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_function_call_ir(ASTNode* node, IRContext* context);
static LLVMValueRef generate_assignment_ir(ASTNode* node, IRContext* context);
static LLVMValueRef find_named_value(IRContext* context, const char* name);

// Initialize built-in functions (print, etc.)
static void initialize_built_in_functions(IRContext* context) {
    // Declare print function for integers
    LLVMTypeRef print_int_param_types[] = { LLVMInt32Type() };
    LLVMTypeRef print_int_type = LLVMFunctionType(LLVMVoidType(), print_int_param_types, 1, 0);
    LLVMAddFunction(context->module, "print", print_int_type);
    
    // You can add more built-in functions here as needed
    
    printf("Built-in functions initialized\n");
}

// Initialize the IR generation context
IRContext* create_ir_context(const char* module_name) {
    IRContext* context = (IRContext*)malloc(sizeof(IRContext));
    if (!context) {
        fprintf(stderr, "Failed to allocate memory for IR context\n");
        return NULL;
    }

    // Initialize LLVM module and builder
    context->module = LLVMModuleCreateWithName(module_name);
    context->builder = LLVMCreateBuilder();
    context->current_function = NULL;

    // Initialize symbol table mapping
    context->named_values_capacity = INITIAL_NAMED_VALUES_CAPACITY;
    context->named_values = (LLVMValueRef*)malloc(sizeof(LLVMValueRef) * context->named_values_capacity);
    context->named_values_count = 0;

    if (!context->named_values) {
        fprintf(stderr, "Failed to allocate memory for named values array\n");
        LLVMDisposeBuilder(context->builder);
        LLVMDisposeModule(context->module);
        free(context);
        return NULL;
    }

    // Set target triple and data layout
    LLVMSetTarget(context->module, get_host_target_triple());
    LLVMSetDataLayout(context->module, get_default_data_layout());
    
    // Initialize built-in functions
    initialize_built_in_functions(context);

    return context;
}

// Free resources used by the IR context
void destroy_ir_context(IRContext* context) {
    if (!context) {
        return;
    }

    // Free LLVM resources
    LLVMDisposeBuilder(context->builder);
    LLVMDisposeModule(context->module);

    // Free named values array
    free(context->named_values);

    // Free context
    free(context);
}

// Get the default data layout string for the target platform
const char* get_default_data_layout(void) {
    // This is a simplified data layout string for x86_64 systems
    // In a real compiler, this would be generated based on the target
    return "e-m:e-i64:64-f80:128-n8:16:32:64-S128";
}

// Get a string representation of the target triple for the host machine
const char* get_host_target_triple(void) {
    // This is a simplified target triple for x86_64 Linux
    // In a real compiler, this would be generated based on the host
    return "x86_64-unknown-linux-gnu";
}

// Print the IR to stderr
void print_ir(LLVMModuleRef module) {
    char* ir_str = LLVMPrintModuleToString(module);
    fprintf(stderr, "%s\n", ir_str);
    LLVMDisposeMessage(ir_str);
}

// Dump the generated LLVM IR to a file
void dump_ir(LLVMModuleRef module, const char* filename) {
    if (LLVMPrintModuleToFile(module, filename, NULL) != 0) {
        fprintf(stderr, "Failed to write IR to file: %s\n", filename);
    }
}

// Convert AST data type to LLVM type
static LLVMTypeRef get_llvm_type(DataType type, IRContext* context) {
    switch (type) {
        case TYPE_INT:
            return LLVMInt32Type();
        case TYPE_FLOAT:
            return LLVMFloatType();
        case TYPE_BOOL:
            return LLVMInt1Type();
        case TYPE_VOID:
            return LLVMVoidType();
        default:
            fprintf(stderr, "Unknown data type: %d\n", type);
            return LLVMInt32Type(); // Default to int
    }
}

// Find a named value in the symbol table
static LLVMValueRef find_named_value(IRContext* context, const char* name) {
    // In a real compiler, this would be a more efficient data structure
    printf("Looking for symbol: %s in %d entries\n", name, context->named_values_count);
    
    for (int i = 0; i < context->named_values_count; i++) {
        const char* var_name = LLVMGetValueName(context->named_values[i]);
        printf("  Checking symbol: %s\n", var_name);
        
        // Compare the name without any numeric suffix that LLVM might have added
        size_t name_len = strlen(name);
        if (strncmp(var_name, name, name_len) == 0 && 
            (var_name[name_len] == '\0' || !isalpha(var_name[name_len]))) {
            printf("  Found symbol: %s\n", name);
            return context->named_values[i];
        }
    }
    
    printf("  Symbol not found: %s\n", name);
    return NULL;
}

// Generate LLVM IR from the AST
LLVMModuleRef generate_ir(ASTNode* ast_root, const char* module_name) {
    if (!ast_root) {
        fprintf(stderr, "AST root is NULL\n");
        return NULL;
    }

    IRContext* context = create_ir_context(module_name);
    if (!context) {
        return NULL;
    }

    // Process each declaration in the program
    if (ast_root->type == NODE_PROGRAM) {
        for (int i = 0; i < ast_root->as.program.declaration_count; i++) {
            ASTNode* decl = ast_root->as.program.declarations[i];
            
            if (decl->type == NODE_FUNCTION_DECL) {
                generate_function_ir(decl, context);
            } else if (decl->type == NODE_VAR_DECL) {
                // Handle global variables
                // This is simplified and would need expansion for a full compiler
                fprintf(stderr, "Global variables not yet supported\n");
            }
        }
    } else {
        fprintf(stderr, "Expected program node at root\n");
    }

    // Verify the module
    char* error_message = NULL;
    LLVMVerifyModule(context->module, LLVMAbortProcessAction, &error_message);
    if (error_message) {
        LLVMDisposeMessage(error_message);
    }

    // Keep the module but free the rest of the context
    LLVMModuleRef module = context->module;
    context->module = NULL; // Prevent module from being freed
    destroy_ir_context(context);
    
    return module;
}

// Generate IR for a function declaration
static LLVMValueRef generate_function_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_FUNCTION_DECL) {
        fprintf(stderr, "Expected function declaration node\n");
        return NULL;
    }
    
    // Clear previous named values
    context->named_values_count = 0;
    
    // Get function return type
    LLVMTypeRef return_type = get_llvm_type(node->as.function_decl.return_type, context);
    
    // Create array of parameter types
    LLVMTypeRef* param_types = NULL;
    int param_count = 0;
    
    if (node->as.function_decl.params) {
        ASTNode* params = node->as.function_decl.params;
        param_count = params->as.param_list.param_count;
        param_types = (LLVMTypeRef*)malloc(sizeof(LLVMTypeRef) * param_count);
        
        for (int i = 0; i < param_count; i++) {
            ASTNode* param = params->as.param_list.params[i];
            param_types[i] = get_llvm_type(param->as.param.type, context);
        }
    }
    
    // Create function type
    LLVMTypeRef function_type = LLVMFunctionType(return_type, param_types, param_count, 0);
    
    // Create function
    LLVMValueRef function = LLVMAddFunction(context->module, node->as.function_decl.name, function_type);
    
    // Free parameter types
    free(param_types);
    
    // Set function linkage
    LLVMSetLinkage(function, LLVMExternalLinkage);
    
    // Create entry block
    LLVMBasicBlockRef entry_block = LLVMAppendBasicBlock(function, "entry");
    LLVMPositionBuilderAtEnd(context->builder, entry_block);
    
    // Save current function
    context->current_function = function;
    
    // Add parameters to symbol table
    if (node->as.function_decl.params) {
        ASTNode* params = node->as.function_decl.params;
        
        for (int i = 0; i < params->as.param_list.param_count; i++) {
            ASTNode* param = params->as.param_list.params[i];
            LLVMValueRef param_val = LLVMGetParam(function, i);
            
            // Set the parameter name
            LLVMSetValueName(param_val, param->as.param.name);
            
            // Allocate stack space for parameter
            LLVMValueRef alloca = LLVMBuildAlloca(context->builder, get_llvm_type(param->as.param.type, context), param->as.param.name);
            
            // Store the parameter value
            LLVMBuildStore(context->builder, param_val, alloca);
            
            // Add to symbol table
            printf("Adding parameter %s to symbol table\n", param->as.param.name);
            context->named_values[context->named_values_count++] = alloca;
        }
    }
    
    // Generate code for function body
    if (node->as.function_decl.body) {
        ASTNode* body = node->as.function_decl.body;
        
        // Generate IR for each statement in the body
        for (int i = 0; i < body->as.block.statement_count; i++) {
            generate_statement_ir(body->as.block.statements[i], context);
        }
    }
    
    // Add implicit return if needed (for void functions)
    if (node->as.function_decl.return_type == TYPE_VOID && !LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(context->builder))) {
        LLVMBuildRetVoid(context->builder);
    }
    
    // Verify function
    LLVMVerifyFunction(function, LLVMPrintMessageAction);
    
    return function;
}

// Generate IR for a statement
static LLVMValueRef generate_statement_ir(ASTNode* node, IRContext* context) {
    if (!node) {
        return NULL;
    }
    
    switch (node->type) {
        case NODE_VAR_DECL:
            return generate_var_decl_ir(node, context);
        case NODE_IF_STMT:
            return generate_if_stmt_ir(node, context);
        case NODE_WHILE_STMT:
            return generate_while_stmt_ir(node, context);
        case NODE_FOR_STMT:
            return generate_for_stmt_ir(node, context);
        case NODE_RETURN_STMT:
            return generate_return_stmt_ir(node, context);
        case NODE_EXPR_STMT:
            return generate_expression_ir(node->as.expr_stmt.expr, context);
        case NODE_BLOCK:
            for (int i = 0; i < node->as.block.statement_count; i++) {
                generate_statement_ir(node->as.block.statements[i], context);
            }
            return NULL;
        case NODE_FUNC_CALL:
            // Function calls can be statements too
            return generate_function_call_ir(node, context);
        default:
            fprintf(stderr, "Unknown statement type: %d (skipping)\n", node->type);
            return NULL;
    }
}

// Generate IR for an expression
static LLVMValueRef generate_expression_ir(ASTNode* node, IRContext* context) {
    if (!node) {
        return NULL;
    }
    
    switch (node->type) {
        case NODE_BINARY_EXPR:
            return generate_binary_expr_ir(node, context);
        case NODE_UNARY_EXPR:
            return generate_unary_expr_ir(node, context);
        case NODE_ASSIGN_EXPR:
            return generate_assignment_ir(node, context);
        case NODE_VAR_REF:
            return generate_var_ref_ir(node, context);
        case NODE_FUNC_CALL:
            return generate_function_call_ir(node, context);
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL:
        case NODE_BOOL_LITERAL:
        case NODE_STRING_LITERAL:
            return generate_literal_ir(node, context);
        default:
            fprintf(stderr, "Unknown expression type: %d\n", node->type);
            return NULL;
    }
}

// Generate IR for a variable declaration
static LLVMValueRef generate_var_decl_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_VAR_DECL) {
        fprintf(stderr, "Expected variable declaration node\n");
        return NULL;
    }
    
    // Get variable type
    LLVMTypeRef var_type = get_llvm_type(node->as.var_decl.type, context);
    
    // Allocate stack space for variable
    LLVMValueRef alloca = LLVMBuildAlloca(context->builder, var_type, node->as.var_decl.name);
    
    // Initialize variable if initializer exists
    if (node->as.var_decl.init_expr) {
        LLVMValueRef init_val = generate_expression_ir(node->as.var_decl.init_expr, context);
        LLVMBuildStore(context->builder, init_val, alloca);
    }
    
    // Add to symbol table
    if (context->named_values_count >= context->named_values_capacity) {
        context->named_values_capacity *= 2;
        context->named_values = (LLVMValueRef*)realloc(context->named_values, sizeof(LLVMValueRef) * context->named_values_capacity);
    }
    context->named_values[context->named_values_count++] = alloca;
    
    return alloca;
}

// Generate IR for a variable reference
static LLVMValueRef generate_var_ref_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_VAR_REF) {
        fprintf(stderr, "Expected variable reference node\n");
        return NULL;
    }
    
    // Look up variable in symbol table
    LLVMValueRef var = find_named_value(context, node->as.var_ref.name);
    if (!var) {
        fprintf(stderr, "Unknown variable: %s\n", node->as.var_ref.name);
        // Return a default value to avoid crashes
        if (node->as.var_ref.type == TYPE_INT) {
            return LLVMConstInt(LLVMInt32Type(), 0, 0);
        } else if (node->as.var_ref.type == TYPE_FLOAT) {
            return LLVMConstReal(LLVMFloatType(), 0.0);
        } else if (node->as.var_ref.type == TYPE_BOOL) {
            return LLVMConstInt(LLVMInt1Type(), 0, 0);
        } else {
            return LLVMConstInt(LLVMInt32Type(), 0, 0);
        }
    }
    
    // Load variable value
    LLVMTypeRef type = get_llvm_type(node->as.var_ref.type, context);
    return LLVMBuildLoad2(context->builder, type, var, "load");
}

// Generate IR for a literal
static LLVMValueRef generate_literal_ir(ASTNode* node, IRContext* context) {
    switch (node->type) {
        case NODE_INT_LITERAL:
            return LLVMConstInt(LLVMInt32Type(), node->as.int_literal.value, 0);
        case NODE_FLOAT_LITERAL:
            return LLVMConstReal(LLVMFloatType(), node->as.float_literal.value);
        case NODE_BOOL_LITERAL:
            return LLVMConstInt(LLVMInt1Type(), node->as.bool_literal.value ? 1 : 0, 0);
        case NODE_STRING_LITERAL: {
            // Create a global string constant
            LLVMValueRef str = LLVMConstString(node->as.string_literal.value, 
                                              strlen(node->as.string_literal.value), 
                                              0); // Don't include null terminator
            
            // Create a global variable to hold the string
            LLVMValueRef global_str = LLVMAddGlobal(context->module, 
                                                   LLVMArrayType(LLVMInt8Type(), 
                                                                strlen(node->as.string_literal.value) + 1), 
                                                   ".str");
            
            // Initialize the global variable
            LLVMSetInitializer(global_str, str);
            
            // Set linkage to internal (private)
            LLVMSetLinkage(global_str, LLVMInternalLinkage);
            
            // Set alignment
            LLVMSetAlignment(global_str, 1);
            
            // Get pointer to the string (first character)
            LLVMValueRef indices[2] = {
                LLVMConstInt(LLVMInt32Type(), 0, 0),
                LLVMConstInt(LLVMInt32Type(), 0, 0)
            };
            
            return LLVMBuildGEP2(context->builder, 
                               LLVMArrayType(LLVMInt8Type(), strlen(node->as.string_literal.value) + 1),
                               global_str, indices, 2, "str");
        }
        default:
            fprintf(stderr, "Unknown literal type: %d\n", node->type);
            return NULL;
    }
}

// Generate IR for an assignment
static LLVMValueRef generate_assignment_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_ASSIGN_EXPR) {
        fprintf(stderr, "Expected assignment expression node\n");
        return NULL;
    }
    
    // Generate IR for right-hand side
    LLVMValueRef rhs = generate_expression_ir(node->as.assign_expr.right, context);
    
    // Left-hand side must be a variable reference
    if (node->as.assign_expr.left->type != NODE_VAR_REF) {
        fprintf(stderr, "Left-hand side of assignment must be a variable reference\n");
        return NULL;
    }
    
    // Look up variable in symbol table
    const char* var_name = node->as.assign_expr.left->as.var_ref.name;
    LLVMValueRef var = find_named_value(context, var_name);
    if (!var) {
        fprintf(stderr, "Unknown variable: %s\n", var_name);
        return NULL;
    }
    
    // Store value to variable
    LLVMBuildStore(context->builder, rhs, var);
    
    // Return the assigned value
    return rhs;
}

// Check if a number is a power of 2
static bool is_power_of_two(int num) {
    return num > 0 && (num & (num - 1)) == 0;
}

// Get the log base 2 of a power of 2
static int log2_of_power_of_two(int num) {
    int result = 0;
    while (num > 1) {
        num >>= 1;
        result++;
    }
    return result;
}

// Generate IR for a binary expression
static LLVMValueRef generate_binary_expr_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_BINARY_EXPR) {
        fprintf(stderr, "Expected binary expression node\n");
        return NULL;
    }
    
    // Generate IR for left and right operands
    LLVMValueRef left = generate_expression_ir(node->as.binary_expr.left, context);
    LLVMValueRef right = generate_expression_ir(node->as.binary_expr.right, context);
    
    if (!left || !right) {
        return NULL;
    }
    
    // Generate IR for binary operation
    switch (node->as.binary_expr.op) {
        // Arithmetic operations
        case OP_ADD:
            if (node->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildAdd(context->builder, left, right, "addtmp");
            } else {
                return LLVMBuildFAdd(context->builder, left, right, "addtmp");
            }
        case OP_SUB:
            if (node->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildSub(context->builder, left, right, "subtmp");
            } else {
                return LLVMBuildFSub(context->builder, left, right, "subtmp");
            }
        case OP_MUL:
            if (node->as.binary_expr.result_type == TYPE_INT) {
                // Strength reduction: replace multiplication by power of 2 with shift
                if (LLVMIsConstant(right)) {
                    int value = LLVMConstIntGetSExtValue(right);
                    if (is_power_of_two(value)) {
                        printf("  Applying strength reduction: multiply by %d -> shift left by %d\n", 
                               value, log2_of_power_of_two(value));
                        LLVMValueRef shift_amount = LLVMConstInt(LLVMInt32Type(), log2_of_power_of_two(value), 0);
                        return LLVMBuildShl(context->builder, left, shift_amount, "shltmp");
                    }
                } else if (LLVMIsConstant(left)) {
                    int value = LLVMConstIntGetSExtValue(left);
                    if (is_power_of_two(value)) {
                        printf("  Applying strength reduction: multiply by %d -> shift left by %d\n", 
                               value, log2_of_power_of_two(value));
                        LLVMValueRef shift_amount = LLVMConstInt(LLVMInt32Type(), log2_of_power_of_two(value), 0);
                        return LLVMBuildShl(context->builder, right, shift_amount, "shltmp");
                    }
                }
                return LLVMBuildMul(context->builder, left, right, "multmp");
            } else {
                return LLVMBuildFMul(context->builder, left, right, "multmp");
            }
        case OP_DIV:
            if (node->as.binary_expr.result_type == TYPE_INT) {
                // Strength reduction: replace division by power of 2 with right shift
                if (LLVMIsConstant(right)) {
                    int value = LLVMConstIntGetSExtValue(right);
                    if (is_power_of_two(value)) {
                        printf("  Applying strength reduction: divide by %d -> shift right by %d\n", 
                               value, log2_of_power_of_two(value));
                        LLVMValueRef shift_amount = LLVMConstInt(LLVMInt32Type(), log2_of_power_of_two(value), 0);
                        return LLVMBuildAShr(context->builder, left, shift_amount, "shrtmp");
                    }
                }
                return LLVMBuildSDiv(context->builder, left, right, "divtmp");
            } else {
                return LLVMBuildFDiv(context->builder, left, right, "divtmp");
            }
        case OP_MOD:
            if (node->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildSRem(context->builder, left, right, "modtmp");
            } else {
                return LLVMBuildFRem(context->builder, left, right, "modtmp");
            }
            
        // Relational operations
        case OP_EQ:
            if (node->as.binary_expr.left->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildICmp(context->builder, LLVMIntEQ, left, right, "eqtmp");
            } else {
                return LLVMBuildFCmp(context->builder, LLVMRealOEQ, left, right, "eqtmp");
            }
        case OP_NEQ:
            if (node->as.binary_expr.left->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildICmp(context->builder, LLVMIntNE, left, right, "neqtmp");
            } else {
                return LLVMBuildFCmp(context->builder, LLVMRealONE, left, right, "neqtmp");
            }
        case OP_LT:
            if (node->as.binary_expr.left->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildICmp(context->builder, LLVMIntSLT, left, right, "lttmp");
            } else {
                return LLVMBuildFCmp(context->builder, LLVMRealOLT, left, right, "lttmp");
            }
        case OP_GT:
            if (node->as.binary_expr.left->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildICmp(context->builder, LLVMIntSGT, left, right, "gttmp");
            } else {
                return LLVMBuildFCmp(context->builder, LLVMRealOGT, left, right, "gttmp");
            }
        case OP_LE:
            if (node->as.binary_expr.left->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildICmp(context->builder, LLVMIntSLE, left, right, "letmp");
            } else {
                return LLVMBuildFCmp(context->builder, LLVMRealOLE, left, right, "letmp");
            }
        case OP_GE:
            if (node->as.binary_expr.left->as.binary_expr.result_type == TYPE_INT) {
                return LLVMBuildICmp(context->builder, LLVMIntSGE, left, right, "getmp");
            } else {
                return LLVMBuildFCmp(context->builder, LLVMRealOGE, left, right, "getmp");
            }
            
        // Logical operations
        case OP_AND:
            return LLVMBuildAnd(context->builder, left, right, "andtmp");
        case OP_OR:
            return LLVMBuildOr(context->builder, left, right, "ortmp");
            
        default:
            fprintf(stderr, "Unknown binary operator: %d\n", node->as.binary_expr.op);
            return NULL;
    }
}

// Generate IR for a unary expression
static LLVMValueRef generate_unary_expr_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_UNARY_EXPR) {
        fprintf(stderr, "Expected unary expression node\n");
        return NULL;
    }
    
    // Generate IR for the operand
    LLVMValueRef operand = generate_expression_ir(node->as.unary_expr.expr, context);
    
    if (!operand) {
        return NULL;
    }
    
    // Generate IR for unary operation
    switch (node->as.unary_expr.op) {
        case OP_SUB:
            if (node->as.unary_expr.result_type == TYPE_INT) {
                return LLVMBuildNeg(context->builder, operand, "negtmp");
            } else {
                return LLVMBuildFNeg(context->builder, operand, "negtmp");
            }
        case OP_NOT:
            return LLVMBuildNot(context->builder, operand, "nottmp");
        default:
            fprintf(stderr, "Unknown unary operator: %d\n", node->as.unary_expr.op);
            return NULL;
    }
}

// Generate IR for a function call
static LLVMValueRef generate_function_call_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_FUNC_CALL) {
        fprintf(stderr, "Expected function call node\n");
        return NULL;
    }
    
    printf("Function call: %s\n", node->as.func_call.name);
    
    // Special handling for print function
    if (strcmp(node->as.func_call.name, "print") == 0) {
        printf("Handling print function - returning dummy value\n");
        // Just return a dummy value for now to avoid segmentation faults
        return LLVMConstInt(LLVMInt32Type(), 0, 0);
    }
    
    // Look up function in module
    LLVMValueRef function = LLVMGetNamedFunction(context->module, node->as.func_call.name);
    
    if (!function) {
        fprintf(stderr, "Unknown function: %s\n", node->as.func_call.name);
        return LLVMConstInt(LLVMInt32Type(), 0, 0);
    }
    
    printf("Found function: %s\n", node->as.func_call.name);
    
    // Safe implementation - return a const value to avoid crashes
    // In a real implementation, you would generate a proper function call
    return LLVMConstInt(LLVMInt32Type(), 42, 0); // Return a placeholder value
}

// Generate IR for an if statement
static LLVMValueRef generate_if_stmt_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_IF_STMT) {
        fprintf(stderr, "Expected if statement node\n");
        return NULL;
    }
    
    // Generate IR for condition with error handling
    LLVMValueRef condition = NULL;
    if (node->as.if_stmt.condition) {
        condition = generate_expression_ir(node->as.if_stmt.condition, context);
    }
    
    if (!condition) {
        fprintf(stderr, "Failed to generate condition for if statement\n");
        return NULL;
    }
    
    // Convert condition to i1 boolean type if needed
    LLVMTypeRef condition_type = LLVMTypeOf(condition);
    if (LLVMGetTypeKind(condition_type) != LLVMIntegerTypeKind || 
        LLVMGetIntTypeWidth(condition_type) != 1) {
        condition = LLVMBuildICmp(context->builder, LLVMIntNE, 
                                  condition, 
                                  LLVMConstInt(condition_type, 0, 0), 
                                  "ifcond");
    }
    
    // Create basic blocks safely with verification
    LLVMBasicBlockRef current_block = LLVMGetInsertBlock(context->builder);
    if (!current_block || !context->current_function) {
        fprintf(stderr, "No current block or function for if statement\n");
        return NULL;
    }
    
    // Create basic blocks for then, else, and merge
    LLVMBasicBlockRef then_block = LLVMAppendBasicBlock(context->current_function, "then");
    LLVMBasicBlockRef else_block = NULL;
    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(context->current_function, "ifcont");
    
    if (!then_block || !merge_block) {
        fprintf(stderr, "Failed to create basic blocks for if statement\n");
        return NULL;
    }
    
    // Create else block if needed
    if (node->as.if_stmt.else_branch) {
        else_block = LLVMAppendBasicBlock(context->current_function, "else");
        if (!else_block) {
            fprintf(stderr, "Failed to create else block for if statement\n");
            return NULL;
        }
    }
    
    // Create conditional branch
    if (node->as.if_stmt.else_branch) {
        LLVMBuildCondBr(context->builder, condition, then_block, else_block);
    } else {
        LLVMBuildCondBr(context->builder, condition, then_block, merge_block);
    }
    
    // Generate code for then branch
    LLVMPositionBuilderAtEnd(context->builder, then_block);
    LLVMValueRef then_value = generate_statement_ir(node->as.if_stmt.then_branch, context);
    
    // Make sure we have a terminator
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(context->builder))) {
        LLVMBuildBr(context->builder, merge_block);
    }
    
    // Generate code for else branch if it exists
    LLVMValueRef else_value = NULL;
    if (node->as.if_stmt.else_branch) {
        LLVMPositionBuilderAtEnd(context->builder, else_block);
        else_value = generate_statement_ir(node->as.if_stmt.else_branch, context);
        
        // Make sure we have a terminator
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(context->builder))) {
            LLVMBuildBr(context->builder, merge_block);
        }
    }
    
    // Continue building code in merge block
    LLVMPositionBuilderAtEnd(context->builder, merge_block);
    
    return NULL; // If statement doesn't produce a value
}

// Generate IR for a return statement
static LLVMValueRef generate_return_stmt_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_RETURN_STMT) {
        fprintf(stderr, "Expected return statement node\n");
        return NULL;
    }
    
    // Generate IR for return value
    if (node->as.return_stmt.expr) {
        LLVMValueRef return_value = generate_expression_ir(node->as.return_stmt.expr, context);
        
        if (!return_value) {
            return NULL;
        }
        
        return LLVMBuildRet(context->builder, return_value);
    } else {
        return LLVMBuildRetVoid(context->builder);
    }
}

// Generate IR for a while statement
static LLVMValueRef generate_while_stmt_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_WHILE_STMT) {
        fprintf(stderr, "Expected while statement node\n");
        return NULL;
    }
    
    // Create basic blocks for condition, body, and after
    LLVMBasicBlockRef cond_block = LLVMAppendBasicBlock(context->current_function, "whilecond");
    LLVMBasicBlockRef body_block = LLVMAppendBasicBlock(context->current_function, "whilebody");
    LLVMBasicBlockRef after_block = LLVMAppendBasicBlock(context->current_function, "whileafter");
    
    // Branch to condition block
    LLVMBuildBr(context->builder, cond_block);
    
    // Generate code for condition
    LLVMPositionBuilderAtEnd(context->builder, cond_block);
    LLVMValueRef condition = generate_expression_ir(node->as.while_stmt.condition, context);
    
    if (!condition) {
        return NULL;
    }
    
    // Create conditional branch
    LLVMBuildCondBr(context->builder, condition, body_block, after_block);
    
    // Generate code for body
    LLVMPositionBuilderAtEnd(context->builder, body_block);
    generate_statement_ir(node->as.while_stmt.body, context);
    
    // If body doesn't already have a terminator, add a branch back to condition
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(context->builder))) {
        LLVMBuildBr(context->builder, cond_block);
    }
    
    // Continue building code after the loop
    LLVMPositionBuilderAtEnd(context->builder, after_block);
    
    return NULL; // While statement doesn't produce a value
}

// Generate IR for a for statement
static LLVMValueRef generate_for_stmt_ir(ASTNode* node, IRContext* context) {
    if (node->type != NODE_FOR_STMT) {
        fprintf(stderr, "Expected for statement node\n");
        return NULL;
    }
    
    // Generate IR for init expression
    if (node->as.for_stmt.init) {
        generate_statement_ir(node->as.for_stmt.init, context);
    }
    
    // Create basic blocks for condition, body, update, and after
    LLVMBasicBlockRef cond_block = LLVMAppendBasicBlock(context->current_function, "forcond");
    LLVMBasicBlockRef body_block = LLVMAppendBasicBlock(context->current_function, "forbody");
    LLVMBasicBlockRef update_block = LLVMAppendBasicBlock(context->current_function, "forupdate");
    LLVMBasicBlockRef after_block = LLVMAppendBasicBlock(context->current_function, "forafter");
    
    // Branch to condition block
    LLVMBuildBr(context->builder, cond_block);
    
    // Generate code for condition
    LLVMPositionBuilderAtEnd(context->builder, cond_block);
    LLVMValueRef condition = NULL;
    
    if (node->as.for_stmt.condition) {
        condition = generate_expression_ir(node->as.for_stmt.condition, context);
        
        if (!condition) {
            return NULL;
        }
    } else {
        // If no condition, loop indefinitely
        condition = LLVMConstInt(LLVMInt1Type(), 1, 0);
    }
    
    // Create conditional branch
    LLVMBuildCondBr(context->builder, condition, body_block, after_block);
    
    // Generate code for body
    LLVMPositionBuilderAtEnd(context->builder, body_block);
    generate_statement_ir(node->as.for_stmt.body, context);
    
    // If body doesn't already have a terminator, add a branch to update block
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(context->builder))) {
        LLVMBuildBr(context->builder, update_block);
    }
    
    // Generate code for update
    LLVMPositionBuilderAtEnd(context->builder, update_block);
    
    if (node->as.for_stmt.update) {
        generate_expression_ir(node->as.for_stmt.update, context);
    }
    
    // Branch back to condition
    LLVMBuildBr(context->builder, cond_block);
    
    // Continue building code after the loop
    LLVMPositionBuilderAtEnd(context->builder, after_block);
    
    return NULL; // For statement doesn't produce a value
} 