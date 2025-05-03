#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Data type enum
typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_ERROR
} DataType;

// AST node types
typedef enum
{
    // Program structure
    NODE_PROGRAM,
    NODE_FUNCTION_DECL,
    NODE_PARAM_LIST,
    NODE_PARAM,
    NODE_BLOCK,

    // Statements
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_SWITCH_STMT,
    NODE_CASE_STMT,
    NODE_RETURN_STMT,
    NODE_EXPR_STMT,
    NODE_VAR_DECL,

    // Expressions
    NODE_BINARY_EXPR,
    NODE_UNARY_EXPR,
    NODE_ASSIGN_EXPR,
    NODE_FUNC_CALL,
    NODE_VAR_REF,

    // Primary expressions
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_BOOL_LITERAL,
    NODE_STRING_LITERAL
} NodeType;

// Operator types
typedef enum
{
    // Arithmetic
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,

    // Relational
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,

    // Logical
    OP_AND,
    OP_OR,
    OP_NOT,

    // Assignment
    OP_ASSIGN
} OperatorType;

// Forward declaration for symbol
struct Symbol;

// AST node structure
typedef struct ASTNode
{
    NodeType type;
    struct ASTNode *parent;

    union
    {
        // Program structure
        struct
        {
            struct ASTNode **declarations;
            int declaration_count;
        } program;

        struct
        {
            char *name;
            DataType return_type;
            struct ASTNode *params;
            struct ASTNode *body;
            struct Symbol *symbol;
        } function_decl;

        struct
        {
            struct ASTNode **params;
            int param_count;
        } param_list;

        struct
        {
            char *name;
            DataType type;
            struct Symbol *symbol;
        } param;

        struct
        {
            struct ASTNode **statements;
            int statement_count;
        } block;

        // Statements
        struct
        {
            struct ASTNode *condition;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } if_stmt;

        struct
        {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_stmt;

        struct
        {
            struct ASTNode *init;
            struct ASTNode *condition;
            struct ASTNode *update;
            struct ASTNode *body;
        } for_stmt;

        struct
        {
            struct ASTNode *expr;
            struct ASTNode **cases;
            int case_count;
            struct ASTNode *default_case;
        } switch_stmt;

        struct
        {
            int value;
            struct ASTNode *body;
        } case_stmt;

        struct
        {
            struct ASTNode *expr;
        } return_stmt;

        struct
        {
            struct ASTNode *expr;
        } expr_stmt;

        struct
        {
            char *name;
            DataType type;
            struct ASTNode *init_expr;
            struct Symbol *symbol;
        } var_decl;

        // Expressions
        struct
        {
            OperatorType op;
            struct ASTNode *left;
            struct ASTNode *right;
            DataType result_type;
        } binary_expr;

        struct
        {
            OperatorType op;
            struct ASTNode *expr;
            DataType result_type;
        } unary_expr;

        struct
        {
            struct ASTNode *left;
            struct ASTNode *right;
            DataType result_type;
        } assign_expr;

        struct
        {
            char *name;
            struct ASTNode **args;
            int arg_count;
            struct Symbol *symbol;
            DataType result_type;
        } func_call;

        struct
        {
            char *name;
            struct Symbol *symbol;
            DataType type;
        } var_ref;

        // Literals
        struct
        {
            int value;
        } int_literal;

        struct
        {
            float value;
        } float_literal;

        struct
        {
            bool value;
        } bool_literal;

        struct
        {
            char *value;
        } string_literal;
    } as;

    int line_number; // For error reporting
} ASTNode;

// Symbol table entry
typedef struct Symbol
{
    char *name;
    DataType type;
    bool is_function;

    // For functions
    DataType return_type;
    DataType *param_types;
    int param_count;

    // Scope information
    int scope_level;
    struct Symbol *next; // For linked list implementation
} Symbol;

// Symbol table
typedef struct SymbolTable
{
    Symbol **symbols; // Hash table of symbols
    int size;         // Size of hash table
    int scope_level;  // Current scope level
} SymbolTable;

// External declarations
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int yylex();
extern int yyparse();
extern void yyerror(const char *s);

// AST functions
ASTNode *create_node(NodeType type);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent);

// Symbol table functions
SymbolTable *create_symbol_table(int size);
void free_symbol_table(SymbolTable *table);
Symbol *lookup_symbol(SymbolTable *table, const char *name);
Symbol *insert_symbol(SymbolTable *table, const char *name, DataType type, bool is_function);
void enter_scope(SymbolTable *table);
void exit_scope(SymbolTable *table);

// Semantic analysis
DataType check_types(ASTNode *node, SymbolTable *table);
void semantic_analysis(ASTNode *node, SymbolTable *table);

// Global variables
extern ASTNode *ast_root;
extern SymbolTable *global_symbol_table;

#endif /* COMPILER_H */