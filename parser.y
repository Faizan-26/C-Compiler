%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

/* Global variables */
ASTNode* ast_root = NULL;
SymbolTable* global_symbol_table = NULL;

/* Function declarations */
void yyerror(const char* s);
%}

/* Bison declarations */
%union {
    int int_val;
    float float_val;
    bool bool_val;
    char* string_val;
    DataType type_val;
    ASTNode* node_val;
}

/* Terminal symbols */
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL
%token <bool_val> BOOL_LITERAL
%token <string_val> STRING_LITERAL IDENTIFIER

/* Keywords */
%token INT FLOAT BOOL VOID
%token IF ELSE WHILE FOR 
%token RETURN BREAK CONTINUE
%token SWITCH CASE DEFAULT
%token PRINT READ

/* Operators */
%token EQ NEQ LE GE AND OR

/* Non-terminal symbols */
%type <node_val> program declaration_list declaration
%type <node_val> var_declaration func_declaration
%type <type_val> type_specifier
%type <node_val> params param_list param
%type <node_val> compound_stmt stmt_list statement
%type <node_val> expr_stmt selection_stmt iteration_stmt switch_stmt
%type <node_val> return_stmt break_stmt continue_stmt io_stmt
%type <node_val> case_list case_stmt default_stmt
%type <node_val> expression var assignment_expr
%type <node_val> simple_expr additive_expr term factor call
%type <node_val> args arg_list

/* Operator precedence */
%right '='
%left OR
%left AND
%left EQ NEQ
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!' UMINUS

%start program

%%

program
    : declaration_list
        {
            ast_root = create_node(NODE_PROGRAM);
            ast_root->as.program.declarations = malloc(sizeof(ASTNode*) * 1000);
            ast_root->as.program.declaration_count = 0;
            
            // Collect all declarations
            ASTNode* curr = $1;
            while (curr != NULL) {
                if (curr->type == NODE_BLOCK) {
                    for (int i = 0; i < curr->as.block.statement_count; i++) {
                        ast_root->as.program.declarations[ast_root->as.program.declaration_count++] = 
                            curr->as.block.statements[i];
                    }
                    free(curr->as.block.statements);
                    free(curr);
                } else {
                    ast_root->as.program.declarations[ast_root->as.program.declaration_count++] = curr;
                }
                curr = NULL;
            }
            
            $$ = ast_root;
        }
    ;

declaration_list
    : declaration
        { $$ = $1; }
    | declaration_list declaration
        {
            // Create a new block node to hold both declarations
            ASTNode* block = create_node(NODE_BLOCK);
            block->as.block.statements = malloc(sizeof(ASTNode*) * 2);
            block->as.block.statement_count = 2;
            block->as.block.statements[0] = $1;
            block->as.block.statements[1] = $2;
            $$ = block;
        }
    ;

declaration
    : var_declaration
        { $$ = $1; }
    | func_declaration
        { $$ = $1; }
    ;

var_declaration
    : type_specifier IDENTIFIER ';'
        {
            $$ = create_node(NODE_VAR_DECL);
            $$->as.var_decl.name = $2;
            $$->as.var_decl.type = $1;
            $$->as.var_decl.init_expr = NULL;
            $$->line_number = yylineno;
        }
    | type_specifier IDENTIFIER '=' expression ';'
        {
            $$ = create_node(NODE_VAR_DECL);
            $$->as.var_decl.name = $2;
            $$->as.var_decl.type = $1;
            $$->as.var_decl.init_expr = $4;
            $$->line_number = yylineno;
        }
    ;

type_specifier
    : INT
        { $$ = TYPE_INT; }
    | FLOAT
        { $$ = TYPE_FLOAT; }
    | BOOL
        { $$ = TYPE_BOOL; }
    | VOID
        { $$ = TYPE_VOID; }
    ;

func_declaration
    : type_specifier IDENTIFIER '(' params ')' compound_stmt
        {
            $$ = create_node(NODE_FUNCTION_DECL);
            $$->as.function_decl.name = $2;
            $$->as.function_decl.return_type = $1;
            $$->as.function_decl.params = $4;
            $$->as.function_decl.body = $6;
            $$->line_number = yylineno;
        }
    ;

params
    : param_list
        { $$ = $1; }
    | VOID
        { $$ = NULL; } // No parameters
    |  /* empty */
        { $$ = NULL; } // No parameters
    ;

param_list
    : param
        {
            $$ = create_node(NODE_PARAM_LIST);
            $$->as.param_list.params = malloc(sizeof(ASTNode*) * 100); // Arbitrary limit
            $$->as.param_list.param_count = 1;
            $$->as.param_list.params[0] = $1;
        }
    | param_list ',' param
        {
            $$ = $1;
            $$->as.param_list.params[$$->as.param_list.param_count++] = $3;
        }
    ;

param
    : type_specifier IDENTIFIER
        {
            $$ = create_node(NODE_PARAM);
            $$->as.param.name = $2;
            $$->as.param.type = $1;
            $$->line_number = yylineno;
        }
    ;

compound_stmt
    : '{' stmt_list '}'
        {
            $$ = $2; // Stmt_list now already returns a NODE_BLOCK node
            $$->line_number = yylineno;
        }
    ;

stmt_list
    : statement
        { 
            $$ = create_node(NODE_BLOCK);
            $$->as.block.statements = malloc(sizeof(ASTNode*));
            $$->as.block.statements[0] = $1;
            $$->as.block.statement_count = 1;
        }
    | stmt_list statement
        { 
            $$ = $1;
            $$->as.block.statements = realloc($$->as.block.statements, 
                sizeof(ASTNode*) * ($$->as.block.statement_count + 1));
            $$->as.block.statements[$$->as.block.statement_count++] = $2;
        }
    | /* empty */
        { 
            $$ = create_node(NODE_BLOCK);
            $$->as.block.statements = NULL;
            $$->as.block.statement_count = 0;
        }
    ;

statement
    : expr_stmt
        { $$ = $1; }
    | compound_stmt
        { $$ = $1; }
    | selection_stmt
        { $$ = $1; }
    | iteration_stmt
        { $$ = $1; }
    | switch_stmt
        { $$ = $1; }
    | return_stmt
        { $$ = $1; }
    | break_stmt
        { $$ = $1; }
    | continue_stmt
        { $$ = $1; }
    | var_declaration
        { $$ = $1; }
    | io_stmt
        { $$ = $1; }
    ;

expr_stmt
    : expression ';'
        {
            $$ = create_node(NODE_EXPR_STMT);
            $$->as.expr_stmt.expr = $1;
            $$->line_number = yylineno;
        }
    | ';'
        { $$ = NULL; } // Empty statement
    ;

selection_stmt
    : IF '(' expression ')' statement
        {
            $$ = create_node(NODE_IF_STMT);
            $$->as.if_stmt.condition = $3;
            $$->as.if_stmt.then_branch = $5;
            $$->as.if_stmt.else_branch = NULL;
            $$->line_number = yylineno;
        }
    | IF '(' expression ')' statement ELSE statement
        {
            $$ = create_node(NODE_IF_STMT);
            $$->as.if_stmt.condition = $3;
            $$->as.if_stmt.then_branch = $5;
            $$->as.if_stmt.else_branch = $7;
            $$->line_number = yylineno;
        }
    ;

iteration_stmt
    : WHILE '(' expression ')' statement
        {
            $$ = create_node(NODE_WHILE_STMT);
            $$->as.while_stmt.condition = $3;
            $$->as.while_stmt.body = $5;
            $$->line_number = yylineno;
        }
    | FOR '(' expression ';' expression ';' expression ')' statement
        {
            $$ = create_node(NODE_FOR_STMT);
            $$->as.for_stmt.init = $3;
            $$->as.for_stmt.condition = $5;
            $$->as.for_stmt.update = $7;
            $$->as.for_stmt.body = $9;
            $$->line_number = yylineno;
        }
    | FOR '(' var_declaration expression ';' expression ')' statement
        {
            $$ = create_node(NODE_FOR_STMT);
            $$->as.for_stmt.init = $3;
            $$->as.for_stmt.condition = $4;
            $$->as.for_stmt.update = $6;
            $$->as.for_stmt.body = $8;
            $$->line_number = yylineno;
        }
    ;

switch_stmt
    : SWITCH '(' expression ')' '{' case_list '}'
        {
            $$ = create_node(NODE_SWITCH_STMT);
            $$->as.switch_stmt.expr = $3;
            // In a real implementation, we would need to handle the case list
            $$->line_number = yylineno;
        }
    ;

case_list
    : case_stmt
        { $$ = $1; }
    | case_list case_stmt
        { $$ = $2; } // Simple case: just return the last case
    | default_stmt
        { $$ = $1; }
    | case_list default_stmt
        { $$ = $2; }
    ;

case_stmt
    : CASE INT_LITERAL ':' stmt_list
        {
            $$ = create_node(NODE_CASE_STMT);
            $$->as.case_stmt.value = $2;
            $$->as.case_stmt.body = $4;
            $$->line_number = yylineno;
        }
    ;

default_stmt
    : DEFAULT ':' stmt_list
        {
            $$ = create_node(NODE_CASE_STMT);
            $$->as.case_stmt.value = -1; // Special value for default
            $$->as.case_stmt.body = $3;
            $$->line_number = yylineno;
        }
    ;

return_stmt
    : RETURN ';'
        {
            $$ = create_node(NODE_RETURN_STMT);
            $$->as.return_stmt.expr = NULL;
            $$->line_number = yylineno;
        }
    | RETURN expression ';'
        {
            $$ = create_node(NODE_RETURN_STMT);
            $$->as.return_stmt.expr = $2;
            $$->line_number = yylineno;
        }
    ;

break_stmt
    : BREAK ';'
        {
            // For simplicity, we'll use expr_stmt for break
            $$ = create_node(NODE_EXPR_STMT);
            $$->line_number = yylineno;
        }
    ;

continue_stmt
    : CONTINUE ';'
        {
            // For simplicity, we'll use expr_stmt for continue
            $$ = create_node(NODE_EXPR_STMT);
            $$->line_number = yylineno;
        }
    ;

io_stmt
    : PRINT '(' expression ')' ';'
        {
            // For simplicity, we'll use function call for print
            $$ = create_node(NODE_FUNC_CALL);
            $$->as.func_call.name = strdup("print");
            $$->as.func_call.args = malloc(sizeof(ASTNode*));
            $$->as.func_call.args[0] = $3;
            $$->as.func_call.arg_count = 1;
            $$->line_number = yylineno;
        }
    | READ '(' var ')' ';'
        {
            // For simplicity, we'll use function call for read
            $$ = create_node(NODE_FUNC_CALL);
            $$->as.func_call.name = strdup("read");
            $$->as.func_call.args = malloc(sizeof(ASTNode*));
            $$->as.func_call.args[0] = $3;
            $$->as.func_call.arg_count = 1;
            $$->line_number = yylineno;
        }
    ;

expression
    : assignment_expr
        { $$ = $1; }
    | simple_expr
        { $$ = $1; }
    ;

assignment_expr
    : var '=' expression
        {
            $$ = create_node(NODE_ASSIGN_EXPR);
            $$->as.assign_expr.left = $1;
            $$->as.assign_expr.right = $3;
            $$->line_number = yylineno;
        }
    ;

var
    : IDENTIFIER
        {
            $$ = create_node(NODE_VAR_REF);
            $$->as.var_ref.name = $1;
            $$->line_number = yylineno;
        }
    ;

simple_expr
    : additive_expr
        { $$ = $1; }
    | simple_expr '<' additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_LT;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr '>' additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_GT;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr LE additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_LE;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr GE additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_GE;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr EQ additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_EQ;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr NEQ additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_NEQ;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr AND additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_AND;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | simple_expr OR additive_expr
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_OR;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    ;

additive_expr
    : term
        { $$ = $1; }
    | additive_expr '+' term
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_ADD;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | additive_expr '-' term
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_SUB;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    ;

term
    : factor
        { $$ = $1; }
    | term '*' factor
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_MUL;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | term '/' factor
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_DIV;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    | term '%' factor
        {
            $$ = create_node(NODE_BINARY_EXPR);
            $$->as.binary_expr.op = OP_MOD;
            $$->as.binary_expr.left = $1;
            $$->as.binary_expr.right = $3;
            $$->line_number = yylineno;
        }
    ;

factor
    : '(' expression ')'
        { $$ = $2; }
    | var
        { $$ = $1; }
    | call
        { $$ = $1; }
    | INT_LITERAL
        {
            $$ = create_node(NODE_INT_LITERAL);
            $$->as.int_literal.value = $1;
            $$->line_number = yylineno;
        }
    | FLOAT_LITERAL
        {
            $$ = create_node(NODE_FLOAT_LITERAL);
            $$->as.float_literal.value = $1;
            $$->line_number = yylineno;
        }
    | BOOL_LITERAL
        {
            $$ = create_node(NODE_BOOL_LITERAL);
            $$->as.bool_literal.value = $1;
            $$->line_number = yylineno;
        }
    | STRING_LITERAL
        {
            $$ = create_node(NODE_STRING_LITERAL);
            $$->as.string_literal.value = $1;
            $$->line_number = yylineno;
        }
    | '-' factor %prec UMINUS
        {
            $$ = create_node(NODE_UNARY_EXPR);
            $$->as.unary_expr.op = OP_SUB;
            $$->as.unary_expr.expr = $2;
            $$->line_number = yylineno;
        }
    | '!' factor
        {
            $$ = create_node(NODE_UNARY_EXPR);
            $$->as.unary_expr.op = OP_NOT;
            $$->as.unary_expr.expr = $2;
            $$->line_number = yylineno;
        }
    ;

call
    : IDENTIFIER '(' args ')'
        {
            $$ = create_node(NODE_FUNC_CALL);
            $$->as.func_call.name = $1;
            // In a real implementation, we would need to handle args
            $$->line_number = yylineno;
        }
    ;

args
    : arg_list
        { $$ = $1; }
    | /* empty */
        { $$ = NULL; }
    ;

arg_list
    : expression
        { $$ = $1; }
    | arg_list ',' expression
        {
            // In a real implementation, we would need to create a linked list
            // or array of arguments. For simplicity, just return the first argument.
            $$ = $1;
        }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}

int main(int argc, char* argv[]) {
    // Initialize global symbols table
    global_symbol_table = create_symbol_table(100);
    
    // Parse from file if specified, otherwise from stdin
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    // Parse input
    yyparse();
    
    // Perform semantic analysis
    if (ast_root != NULL) {
        semantic_analysis(ast_root, global_symbol_table);
        
        // Print AST in text format
        printf("Abstract Syntax Tree (Text Format):\n");
        print_ast(ast_root, 0);
        
        // Generate Graphviz visualization
        printf("\nGenerating AST visualization...\n");
        print_ast_graphviz(ast_root, "ast.dot");
        printf("AST visualization saved to ast.dot\n");
        printf("To view the AST, run: dot -Tpng ast.dot -o ast.png\n");
    }
    
    // Clean up
    if (ast_root != NULL) {
        free_ast(ast_root);
    }
    
    free_symbol_table(global_symbol_table);
    
    return 0;
}