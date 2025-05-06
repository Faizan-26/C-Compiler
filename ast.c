#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

// Create a new AST node of the specified type
ASTNode *create_node(NodeType type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    // Initialize node
    memset(node, 0, sizeof(ASTNode));
    node->type = type;
    node->parent = NULL;
    node->line_number = 0;

    return node;
}

// Free an AST and all its children
void free_ast(ASTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    // Free resources based on node type
    switch (node->type)
    {
    case NODE_PROGRAM:
        for (int i = 0; i < node->as.program.declaration_count; i++)
        {
            free_ast(node->as.program.declarations[i]);
        }
        free(node->as.program.declarations);
        break;

    case NODE_FUNCTION_DECL:
        free(node->as.function_decl.name);
        free_ast(node->as.function_decl.params);
        free_ast(node->as.function_decl.body);
        break;

    case NODE_PARAM_LIST:
        for (int i = 0; i < node->as.param_list.param_count; i++)
        {
            free_ast(node->as.param_list.params[i]);
        }
        free(node->as.param_list.params);
        break;

    case NODE_PARAM:
        free(node->as.param.name);
        break;

    case NODE_BLOCK:
        for (int i = 0; i < node->as.block.statement_count; i++)
        {
            free_ast(node->as.block.statements[i]);
        }
        free(node->as.block.statements);
        break;

    case NODE_IF_STMT:
        free_ast(node->as.if_stmt.condition);
        free_ast(node->as.if_stmt.then_branch);
        if (node->as.if_stmt.else_branch)
        {
            free_ast(node->as.if_stmt.else_branch);
        }
        break;

    case NODE_WHILE_STMT:
        free_ast(node->as.while_stmt.condition);
        free_ast(node->as.while_stmt.body);
        break;

    case NODE_FOR_STMT:
        free_ast(node->as.for_stmt.init);
        free_ast(node->as.for_stmt.condition);
        free_ast(node->as.for_stmt.update);
        free_ast(node->as.for_stmt.body);
        break;

    case NODE_SWITCH_STMT:
        free_ast(node->as.switch_stmt.expr);
        free_ast(node->as.switch_stmt.cases);
        break;

    case NODE_CASE_LIST:
        for (int i = 0; i < node->as.case_list.case_count; i++) {
            free_ast(node->as.case_list.cases[i]);
        }
        free(node->as.case_list.cases);
        break;

    case NODE_CASE_STMT:
        free_ast(node->as.case_stmt.body);
        break;

    case NODE_RETURN_STMT:
        if (node->as.return_stmt.expr)
        {
            free_ast(node->as.return_stmt.expr);
        }
        break;

    case NODE_EXPR_STMT:
        if (node->as.expr_stmt.expr)
        {
            free_ast(node->as.expr_stmt.expr);
        }
        break;

    case NODE_VAR_DECL:
        free(node->as.var_decl.name);
        if (node->as.var_decl.init_expr)
        {
            free_ast(node->as.var_decl.init_expr);
        }
        break;

    case NODE_BINARY_EXPR:
        free_ast(node->as.binary_expr.left);
        free_ast(node->as.binary_expr.right);
        break;

    case NODE_UNARY_EXPR:
        free_ast(node->as.unary_expr.expr);
        break;

    case NODE_ASSIGN_EXPR:
        free_ast(node->as.assign_expr.left);
        free_ast(node->as.assign_expr.right);
        break;

    case NODE_FUNC_CALL:
        free(node->as.func_call.name);
        for (int i = 0; i < node->as.func_call.arg_count; i++)
        {
            free_ast(node->as.func_call.args[i]);
        }
        free(node->as.func_call.args);
        break;

    case NODE_VAR_REF:
        free(node->as.var_ref.name);
        break;

    case NODE_STRING_LITERAL:
        free(node->as.string_literal.value);
        break;

    // For simple literals, no extra cleanup needed
    case NODE_INT_LITERAL:
    case NODE_FLOAT_LITERAL:
    case NODE_BOOL_LITERAL:
        break;

    default:
        fprintf(stderr, "Unknown node type in free_ast: %d\n", node->type);
        break;
    }

    // Free the node itself
    free(node);
}

// Get a string representation of a node type
const char *get_node_type_str(NodeType type)
{
    switch (type)
    {
    case NODE_PROGRAM:
        return "PROGRAM";
    case NODE_FUNCTION_DECL:
        return "FUNCTION_DECL";
    case NODE_PARAM_LIST:
        return "PARAM_LIST";
    case NODE_PARAM:
        return "PARAM";
    case NODE_BLOCK:
        return "BLOCK";
    case NODE_IF_STMT:
        return "IF_STMT";
    case NODE_WHILE_STMT:
        return "WHILE_STMT";
    case NODE_FOR_STMT:
        return "FOR_STMT";
    case NODE_SWITCH_STMT:
        return "SWITCH_STMT";
    case NODE_CASE_STMT:
        return "CASE_STMT";
    case NODE_RETURN_STMT:
        return "RETURN_STMT";
    case NODE_EXPR_STMT:
        return "EXPR_STMT";
    case NODE_VAR_DECL:
        return "VAR_DECL";
    case NODE_BINARY_EXPR:
        return "BINARY_EXPR";
    case NODE_UNARY_EXPR:
        return "UNARY_EXPR";
    case NODE_ASSIGN_EXPR:
        return "ASSIGN_EXPR";
    case NODE_FUNC_CALL:
        return "FUNC_CALL";
    case NODE_VAR_REF:
        return "VAR_REF";
    case NODE_INT_LITERAL:
        return "INT_LITERAL";
    case NODE_FLOAT_LITERAL:
        return "FLOAT_LITERAL";
    case NODE_BOOL_LITERAL:
        return "BOOL_LITERAL";
    case NODE_STRING_LITERAL:
        return "STRING_LITERAL";
    default:
        return "UNKNOWN";
    }
}

// Get a string representation of an operator type
const char *get_op_type_str(OperatorType op)
{
    switch (op)
    {
    case OP_ADD:
        return "+";
    case OP_SUB:
        return "-";
    case OP_MUL:
        return "*";
    case OP_DIV:
        return "/";
    case OP_MOD:
        return "%";
    case OP_EQ:
        return "==";
    case OP_NEQ:
        return "!=";
    case OP_LT:
        return "<";
    case OP_GT:
        return ">";
    case OP_LE:
        return "<=";
    case OP_GE:
        return ">=";
    case OP_AND:
        return "&&";
    case OP_OR:
        return "||";
    case OP_NOT:
        return "!";
    case OP_ASSIGN:
        return "=";
    default:
        return "?";
    }
}

// Get a string representation of a data type
const char *get_data_type_str(DataType type)
{
    switch (type)
    {
    case TYPE_INT:
        return "int";
    case TYPE_FLOAT:
        return "float";
    case TYPE_BOOL:
        return "bool";
    case TYPE_VOID:
        return "void";
    case TYPE_ERROR:
        return "error";
    default:
        return "unknown";
    }
}

// Print the AST with proper indentation
void print_ast(ASTNode *node, int indent)
{
    if (node == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < indent; i++)
    {
        printf("  ");
    }

    // Print node information based on type
    printf("%s (line %d): ", get_node_type_str(node->type), node->line_number);

    switch (node->type)
    {
    case NODE_PROGRAM:
        printf("Program with %d declarations\n", node->as.program.declaration_count);
        for (int i = 0; i < node->as.program.declaration_count; i++)
        {
            print_ast(node->as.program.declarations[i], indent + 1);
        }
        break;

    case NODE_FUNCTION_DECL:
        printf("Function %s -> %s\n", node->as.function_decl.name,
               get_data_type_str(node->as.function_decl.return_type));

        if (node->as.function_decl.params != NULL)
        {
            print_ast(node->as.function_decl.params, indent + 1);
        }

        print_ast(node->as.function_decl.body, indent + 1);
        break;

    case NODE_PARAM_LIST:
        printf("Parameters (%d):\n", node->as.param_list.param_count);
        for (int i = 0; i < node->as.param_list.param_count; i++)
        {
            print_ast(node->as.param_list.params[i], indent + 1);
        }
        break;

    case NODE_PARAM:
        printf("Parameter %s: %s\n", node->as.param.name,
               get_data_type_str(node->as.param.type));
        break;

    case NODE_BLOCK:
        printf("Block with %d statements\n", node->as.block.statement_count);
        for (int i = 0; i < node->as.block.statement_count; i++)
        {
            print_ast(node->as.block.statements[i], indent + 1);
        }
        break;

    case NODE_IF_STMT:
        printf("If statement\n");

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Condition:\n");
        print_ast(node->as.if_stmt.condition, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Then branch:\n");
        print_ast(node->as.if_stmt.then_branch, indent + 2);

        if (node->as.if_stmt.else_branch != NULL)
        {
            for (int i = 0; i < indent + 1; i++)
                printf("  ");
            printf("Else branch:\n");
            print_ast(node->as.if_stmt.else_branch, indent + 2);
        }
        break;

    case NODE_WHILE_STMT:
        printf("While loop\n");

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Condition:\n");
        print_ast(node->as.while_stmt.condition, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Body:\n");
        print_ast(node->as.while_stmt.body, indent + 2);
        break;

    case NODE_FOR_STMT:
        printf("For loop\n");

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Initialization:\n");
        print_ast(node->as.for_stmt.init, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Condition:\n");
        print_ast(node->as.for_stmt.condition, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Update:\n");
        print_ast(node->as.for_stmt.update, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Body:\n");
        print_ast(node->as.for_stmt.body, indent + 2);
        break;

    case NODE_SWITCH_STMT:
        printf("%*sSwitch Expression:\n", indent, "");
        print_ast(node->as.switch_stmt.expr, indent + 2);
        printf("%*sCases:\n", indent, "");
        print_ast(node->as.switch_stmt.cases, indent + 2);
        break;

    case NODE_CASE_LIST:
        for (int i = 0; i < node->as.case_list.case_count; i++) {
            print_ast(node->as.case_list.cases[i], indent);
        }
        break;

    case NODE_CASE_STMT:
        if (node->as.case_stmt.value == -1) {
            printf("%*sDefault Case:\n", indent, "");
        } else {
            printf("%*sCase %d:\n", indent, "", node->as.case_stmt.value);
        }
        print_ast(node->as.case_stmt.body, indent + 2);
        break;

    case NODE_RETURN_STMT:
        printf("Return\n");
        if (node->as.return_stmt.expr != NULL)
        {
            print_ast(node->as.return_stmt.expr, indent + 1);
        }
        break;

    case NODE_EXPR_STMT:
        printf("Expression statement\n");
        if (node->as.expr_stmt.expr != NULL)
        {
            print_ast(node->as.expr_stmt.expr, indent + 1);
        }
        break;

    case NODE_VAR_DECL:
        printf("Variable declaration: %s: %s\n", node->as.var_decl.name,
               get_data_type_str(node->as.var_decl.type));

        if (node->as.var_decl.init_expr != NULL)
        {
            for (int i = 0; i < indent + 1; i++)
                printf("  ");
            printf("Initialization:\n");
            print_ast(node->as.var_decl.init_expr, indent + 2);
        }
        break;

    case NODE_BINARY_EXPR:
        printf("Binary expression: %s\n", get_op_type_str(node->as.binary_expr.op));

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Left operand:\n");
        print_ast(node->as.binary_expr.left, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Right operand:\n");
        print_ast(node->as.binary_expr.right, indent + 2);
        break;

    case NODE_UNARY_EXPR:
        printf("Unary expression: %s\n", get_op_type_str(node->as.unary_expr.op));
        print_ast(node->as.unary_expr.expr, indent + 1);
        break;

    case NODE_ASSIGN_EXPR:
        printf("Assignment\n");

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Left side:\n");
        print_ast(node->as.assign_expr.left, indent + 2);

        for (int i = 0; i < indent + 1; i++)
            printf("  ");
        printf("Right side:\n");
        print_ast(node->as.assign_expr.right, indent + 2);
        break;

    case NODE_FUNC_CALL:
        printf("Function call: %s (%d arguments)\n",
               node->as.func_call.name, node->as.func_call.arg_count);

        for (int i = 0; i < node->as.func_call.arg_count; i++)
        {
            for (int j = 0; j < indent + 1; j++)
                printf("  ");
            printf("Argument %d:\n", i + 1);
            print_ast(node->as.func_call.args[i], indent + 2);
        }
        break;

    case NODE_VAR_REF:
        printf("Variable reference: %s\n", node->as.var_ref.name);
        break;

    case NODE_INT_LITERAL:
        printf("Integer literal: %d\n", node->as.int_literal.value);
        break;

    case NODE_FLOAT_LITERAL:
        printf("Float literal: %f\n", node->as.float_literal.value);
        break;

    case NODE_BOOL_LITERAL:
        printf("Boolean literal: %s\n", node->as.bool_literal.value ? "true" : "false");
        break;

    case NODE_STRING_LITERAL:
        printf("String literal: \"%s\"\n", node->as.string_literal.value);
        break;

    default:
        printf("Unknown node type: %d\n", node->type);
        break;
    }
}

// Symbol table functions
SymbolTable *create_symbol_table(int size)
{
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (table == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    table->size = size;
    table->scope_level = 0;
    table->symbols = (Symbol **)calloc(size, sizeof(Symbol *));
    if (table->symbols == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    return table;
}

void free_symbol_table(SymbolTable *table)
{
    if (table == NULL)
    {
        return;
    }

    // Free all symbols
    for (int i = 0; i < table->size; i++)
    {
        Symbol *current = table->symbols[i];
        while (current != NULL)
        {
            Symbol *next = current->next;

            free(current->name);

            if (current->is_function && current->param_types != NULL)
            {
                free(current->param_types);
            }

            free(current);
            current = next;
        }
    }

    // Free the table itself
    free(table->symbols);
    free(table);
}

// Simple hash function for symbol lookup
unsigned int hash(const char *name, int size)
{
    unsigned int hash_val = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        hash_val = (hash_val * 31 + name[i]) % size;
    }
    return hash_val;
}

Symbol *lookup_symbol(SymbolTable *table, const char *name)
{
    if (table == NULL || name == NULL)
    {
        return NULL;
    }

    unsigned int index = hash(name, table->size);
    Symbol *current = table->symbols[index];

    // Find the symbol with matching name in the closest visible scope
    Symbol *found = NULL;
    int closest_scope = -1;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            // Check if this symbol is in current scope or an outer scope
            if (current->scope_level <= table->scope_level)
            {
                // If we found a symbol in a closer scope, or this is the first match
                if (found == NULL || current->scope_level > closest_scope)
                {
                    found = current;
                    closest_scope = current->scope_level;
                }
            }
        }
        current = current->next;
    }

    return found;
}

Symbol *insert_symbol(SymbolTable *table, const char *name, DataType type, bool is_function)
{
    if (table == NULL || name == NULL)
    {
        return NULL;
    }

    // Check if symbol already exists in current scope
    unsigned int index = hash(name, table->size);
    Symbol *current = table->symbols[index];

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0 && current->scope_level == table->scope_level)
        {
            // Symbol already exists in current scope
            return NULL;
        }
        current = current->next;
    }

    // Create new symbol
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    if (symbol == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    // Initialize symbol
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->is_function = is_function;
    symbol->scope_level = table->scope_level;
    symbol->next = NULL;

    if (is_function)
    {
        symbol->return_type = type;
        symbol->param_types = NULL;
        symbol->param_count = 0;
    }

    // Insert at beginning of list
    symbol->next = table->symbols[index];
    table->symbols[index] = symbol;

    return symbol;
}

void enter_scope(SymbolTable *table)
{
    if (table != NULL)
    {
        table->scope_level++;
    }
}

void exit_scope(SymbolTable *table)
{
    if (table == NULL || table->scope_level == 0)
    {
        return;
    }

    // Remove all symbols from current scope
    for (int i = 0; i < table->size; i++)
    {
        Symbol **pp = &(table->symbols[i]);

        while (*pp != NULL)
        {
            if ((*pp)->scope_level == table->scope_level)
            {
                // Remove this symbol
                Symbol *to_remove = *pp;
                *pp = to_remove->next;

                free(to_remove->name);

                if (to_remove->is_function && to_remove->param_types != NULL)
                {
                    free(to_remove->param_types);
                }

                free(to_remove);
            }
            else
            {
                pp = &((*pp)->next);
            }
        }
    }

    table->scope_level--;
}

// Type checking and semantic analysis
DataType check_types(ASTNode *node, SymbolTable *table)
{
    if (node == NULL)
    {
        return TYPE_ERROR;
    }

    switch (node->type)
    {
    case NODE_INT_LITERAL:
        return TYPE_INT;

    case NODE_FLOAT_LITERAL:
        return TYPE_FLOAT;

    case NODE_BOOL_LITERAL:
        return TYPE_BOOL;

    case NODE_STRING_LITERAL:
        return TYPE_ERROR; // No string type in our language

    case NODE_VAR_REF:
    {
        Symbol *symbol = lookup_symbol(table, node->as.var_ref.name);
        if (symbol == NULL)
        {
            fprintf(stderr, "Line %d: Error: Undefined variable '%s'\n",
                    node->line_number, node->as.var_ref.name);
            return TYPE_ERROR;
        }

        node->as.var_ref.symbol = symbol;
        node->as.var_ref.type = symbol->type;
        return symbol->type;
    }

    case NODE_BINARY_EXPR:
    {
        DataType left_type = check_types(node->as.binary_expr.left, table);
        DataType right_type = check_types(node->as.binary_expr.right, table);

        if (left_type == TYPE_ERROR || right_type == TYPE_ERROR)
        {
            return TYPE_ERROR;
        }

        // Handle type compatibility
        switch (node->as.binary_expr.op)
        {
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
        case OP_MOD:
            // Arithmetic operations
            if (left_type == TYPE_INT && right_type == TYPE_INT)
            {
                node->as.binary_expr.result_type = TYPE_INT;
                return TYPE_INT;
            }
            else if ((left_type == TYPE_INT || left_type == TYPE_FLOAT) &&
                     (right_type == TYPE_INT || right_type == TYPE_FLOAT))
            {
                node->as.binary_expr.result_type = TYPE_FLOAT;
                return TYPE_FLOAT;
            }
            else
            {
                fprintf(stderr, "Line %d: Error: Invalid operand types for arithmetic operator\n",
                        node->line_number);
                return TYPE_ERROR;
            }

        case OP_EQ:
        case OP_NEQ:
            // Equality operators (work on any matching types)
            if (left_type == right_type)
            {
                node->as.binary_expr.result_type = TYPE_BOOL;
                return TYPE_BOOL;
            }
            else if ((left_type == TYPE_INT || left_type == TYPE_FLOAT) &&
                     (right_type == TYPE_INT || right_type == TYPE_FLOAT))
            {
                node->as.binary_expr.result_type = TYPE_BOOL;
                return TYPE_BOOL;
            }
            else
            {
                fprintf(stderr, "Line %d: Error: Cannot compare values of different types\n",
                        node->line_number);
                return TYPE_ERROR;
            }

        case OP_LT:
        case OP_GT:
        case OP_LE:
        case OP_GE:
            // Relational operators (work on numeric types)
            if ((left_type == TYPE_INT || left_type == TYPE_FLOAT) &&
                (right_type == TYPE_INT || right_type == TYPE_FLOAT))
            {
                node->as.binary_expr.result_type = TYPE_BOOL;
                return TYPE_BOOL;
            }
            else
            {
                fprintf(stderr, "Line %d: Error: Relational operators require numeric operands\n",
                        node->line_number);
                return TYPE_ERROR;
            }

        case OP_AND:
        case OP_OR:
            // Logical operators (work on boolean types)
            if (left_type == TYPE_BOOL && right_type == TYPE_BOOL)
            {
                node->as.binary_expr.result_type = TYPE_BOOL;
                return TYPE_BOOL;
            }
            else
            {
                fprintf(stderr, "Line %d: Error: Logical operators require boolean operands\n",
                        node->line_number);
                return TYPE_ERROR;
            }

        default:
            fprintf(stderr, "Line %d: Error: Unknown binary operator\n", node->line_number);
            return TYPE_ERROR;
        }
    }

    case NODE_UNARY_EXPR:
    {
        DataType expr_type = check_types(node->as.unary_expr.expr, table);

        if (expr_type == TYPE_ERROR)
        {
            return TYPE_ERROR;
        }

        switch (node->as.unary_expr.op)
        {
        case OP_NOT:
            // Logical NOT
            if (expr_type == TYPE_BOOL)
            {
                node->as.unary_expr.result_type = TYPE_BOOL;
                return TYPE_BOOL;
            }
            else
            {
                fprintf(stderr, "Line %d: Error: Logical NOT requires a boolean operand\n",
                        node->line_number);
                return TYPE_ERROR;
            }

        case OP_SUB:
            // Unary minus
            if (expr_type == TYPE_INT)
            {
                node->as.unary_expr.result_type = TYPE_INT;
                return TYPE_INT;
            }
            else if (expr_type == TYPE_FLOAT)
            {
                node->as.unary_expr.result_type = TYPE_FLOAT;
                return TYPE_FLOAT;
            }
            else
            {
                fprintf(stderr, "Line %d: Error: Unary minus requires a numeric operand\n",
                        node->line_number);
                return TYPE_ERROR;
            }

        default:
            fprintf(stderr, "Line %d: Error: Unknown unary operator\n", node->line_number);
            return TYPE_ERROR;
        }
    }

    case NODE_ASSIGN_EXPR:
    {
        // Check that the left-hand side is a variable
        if (node->as.assign_expr.left->type != NODE_VAR_REF)
        {
            fprintf(stderr, "Line %d: Error: Left side of assignment must be a variable\n",
                    node->line_number);
            return TYPE_ERROR;
        }

        DataType left_type = check_types(node->as.assign_expr.left, table);
        DataType right_type = check_types(node->as.assign_expr.right, table);

        if (left_type == TYPE_ERROR || right_type == TYPE_ERROR)
        {
            return TYPE_ERROR;
        }

        // Check type compatibility with improved error reporting
        if (left_type == right_type)
        {
            node->as.assign_expr.result_type = left_type;
            return left_type;
        }
        else if (left_type == TYPE_FLOAT && right_type == TYPE_INT)
        {
            // Implicit conversion from int to float is allowed
            node->as.assign_expr.result_type = TYPE_FLOAT;
            return TYPE_FLOAT;
        }
        else
        {
            fprintf(stderr, "Line %d: Error: Cannot assign value of type %s to variable of type %s\n",
                    node->line_number, get_data_type_str(right_type), get_data_type_str(left_type));

            // Extra debugging for bool/int assignments
            if (left_type == TYPE_BOOL && right_type == TYPE_INT)
            {
                if (node->as.assign_expr.right->type == NODE_INT_LITERAL)
                {
                    fprintf(stderr, "    Found integer literal with value %d being assigned to boolean variable\n",
                            node->as.assign_expr.right->as.int_literal.value);
                }
            }

            return TYPE_ERROR;
        }
    }

    case NODE_FUNC_CALL:
    {
        // Look up the function in the symbol table
        Symbol *func = NULL;
        for (int i = 0; i < table->size; i++) {
            Symbol *curr = table->symbols[i];
            while (curr != NULL) {
                if (curr->is_function && strcmp(curr->name, node->as.func_call.name) == 0) {
                    func = curr;
                    break;
                }
                curr = curr->next;
            }
            if (func != NULL) break;
        }

        if (func == NULL) {
            fprintf(stderr, "Line %d: Error: Undefined function '%s'\n",
                    node->line_number, node->as.func_call.name);
            return TYPE_ERROR;
        }

        node->as.func_call.symbol = func;
        node->as.func_call.result_type = func->return_type;

        // Check argument count
        if (node->as.func_call.arg_count != func->param_count) {
            fprintf(stderr, "Line %d: Error: Function '%s' expects %d arguments but got %d\n",
                    node->line_number, node->as.func_call.name,
                    func->param_count, node->as.func_call.arg_count);
            return TYPE_ERROR;
        }

        // Check argument types
        bool has_error = false;
        for (int i = 0; i < node->as.func_call.arg_count; i++) {
            DataType arg_type = check_types(node->as.func_call.args[i], table);
            if (arg_type != TYPE_ERROR && arg_type != func->param_types[i]) {
                // Allow implicit int to float conversion
                if (!(func->param_types[i] == TYPE_FLOAT && arg_type == TYPE_INT)) {
                    fprintf(stderr, "Line %d: Error: Argument %d of function '%s' has type %s but expected %s\n",
                            node->line_number, i + 1, node->as.func_call.name,
                            get_data_type_str(arg_type),
                            get_data_type_str(func->param_types[i]));
                    has_error = true;
                }
            }
        }
        
        return has_error ? TYPE_ERROR : func->return_type;
    }

    case NODE_RETURN_STMT:
    {
        // Get current function symbol from the symbol table
        // We need to find the enclosing function's return type
        DataType expected_return_type = TYPE_VOID; // Default to void
        bool is_main_function = false;

        // Find the function we're in by scanning the symbol table for a function
        for (int i = 0; i < table->size; i++)
        {
            Symbol *current = table->symbols[i];
            while (current != NULL)
            {
                if (current->is_function)
                {
                    // Check if this is the main function
                    if (strcmp(current->name, "main") == 0) {
                        is_main_function = true;
                        expected_return_type = TYPE_INT;  // main must return int
                    } else {
                        // For other functions, use the declared return type
                        expected_return_type = current->return_type;
                    }
                    break;
                }
                current = current->next;
            }
        }

        if (node->as.return_stmt.expr != NULL)
        {
            DataType actual_type = check_types(node->as.return_stmt.expr, table);

            // Check if the return value type matches the function return type
            if (actual_type != TYPE_ERROR && actual_type != expected_return_type)
            {
                // Allow implicit conversion from int to float
                if (!(expected_return_type == TYPE_FLOAT && actual_type == TYPE_INT))
                {
                    // Special error message for main function
                    if (is_main_function) {
                        fprintf(stderr, "Line %d: Error: The main function must return an integer value, not %s\n",
                                node->line_number, get_data_type_str(actual_type));
                    } else {
                        fprintf(stderr, "Line %d: Error: Return value of type %s doesn't match function return type %s\n",
                                node->line_number, get_data_type_str(actual_type), get_data_type_str(expected_return_type));
                    }
                    return TYPE_ERROR;
                }
            }
            return actual_type;
        }
        else if (expected_return_type != TYPE_VOID)
        {
            // No expression provided but non-void return type expected
            if (is_main_function) {
                fprintf(stderr, "Line %d: Error: The main function must return an integer value\n",
                        node->line_number);
            } else {
                fprintf(stderr, "Line %d: Error: Function with return type %s must return a value\n",
                        node->line_number, get_data_type_str(expected_return_type));
            }
            return TYPE_ERROR;
        }
        return TYPE_VOID;
    }

    case NODE_SWITCH_STMT:
        check_types(node->as.switch_stmt.expr, table);
        semantic_analysis(node->as.switch_stmt.cases, table);
        break;

    case NODE_CASE_LIST:
        // Analyze all cases
        for (int i = 0; i < node->as.case_list.case_count; i++) {
            semantic_analysis(node->as.case_list.cases[i], table);
        }
        break;

    case NODE_CASE_STMT:
        // Analyze case body
        semantic_analysis(node->as.case_stmt.body, table);
        break;

    default:
        // Other node types are not expressions
        return TYPE_ERROR;
    }
    
    // Default return to avoid warning
    return TYPE_ERROR;
}

// Top-level semantic analysis function
void semantic_analysis(ASTNode *node, SymbolTable *table)
{
    if (node == NULL)
    {
        return;
    }

    switch (node->type)
    {
    case NODE_PROGRAM:
        // Analyze all declarations
        for (int i = 0; i < node->as.program.declaration_count; i++)
        {
            semantic_analysis(node->as.program.declarations[i], table);
        }
        break;

    case NODE_FUNCTION_DECL:
    {
        // Add function to symbol table
        Symbol *func = insert_symbol(table, node->as.function_decl.name,
                                     node->as.function_decl.return_type, true);

        if (func == NULL)
        {
            fprintf(stderr, "Line %d: Error: Function '%s' already defined\n",
                    node->line_number, node->as.function_decl.name);
            break;
        }

        node->as.function_decl.symbol = func;

        // Process parameters
        if (node->as.function_decl.params != NULL)
        {
            int param_count = node->as.function_decl.params->as.param_list.param_count;
            func->param_count = param_count;
            func->param_types = (DataType *)malloc(param_count * sizeof(DataType));

            enter_scope(table);

            for (int i = 0; i < param_count; i++)
            {
                ASTNode *param = node->as.function_decl.params->as.param_list.params[i];

                // Add parameter to symbol table
                Symbol *sym = insert_symbol(table, param->as.param.name,
                                            param->as.param.type, false);

                if (sym == NULL)
                {
                    fprintf(stderr, "Line %d: Error: Parameter '%s' already defined\n",
                            param->line_number, param->as.param.name);
                }
                else
                {
                    param->as.param.symbol = sym;
                    func->param_types[i] = param->as.param.type;
                }
            }
        }

        // Enter new scope for function body and analyze it
        enter_scope(table);
        semantic_analysis(node->as.function_decl.body, table);
        exit_scope(table);

        // Exit parameter scope if it exists
        if (node->as.function_decl.params != NULL)
        {
            exit_scope(table);
        }

        break;
    }

    case NODE_BLOCK:
        // Enter new scope for block
        enter_scope(table);

        // Analyze all statements in block
        for (int i = 0; i < node->as.block.statement_count; i++)
        {
            semantic_analysis(node->as.block.statements[i], table);
        }

        // Exit block scope
        exit_scope(table);
        break;

    case NODE_VAR_DECL:
    {
        // Add variable to symbol table
        Symbol *var = insert_symbol(table, node->as.var_decl.name,
                                    node->as.var_decl.type, false);

        if (var == NULL)
        {
            fprintf(stderr, "Line %d: Error: Variable '%s' already defined in this scope\n",
                    node->line_number, node->as.var_decl.name);
            break;
        }

        node->as.var_decl.symbol = var;

        // If there's an initializer, check its type
        if (node->as.var_decl.init_expr != NULL)
        {
            DataType init_type = check_types(node->as.var_decl.init_expr, table);

            if (init_type != TYPE_ERROR && init_type != node->as.var_decl.type)
            {
                // Allow implicit int to float conversion
                if (!(node->as.var_decl.type == TYPE_FLOAT && init_type == TYPE_INT))
                {
                    fprintf(stderr, "Line %d: Error: Cannot initialize variable of type %s with value of type %s\n",
                            node->line_number, get_data_type_str(node->as.var_decl.type),
                            get_data_type_str(init_type));
                }
            }
        }

        break;
    }

    case NODE_IF_STMT:
        // Check condition type
        if (check_types(node->as.if_stmt.condition, table) != TYPE_BOOL)
        {
            fprintf(stderr, "Line %d: Error: If condition must be a boolean expression\n",
                    node->line_number);
        }

        // Analyze branches
        semantic_analysis(node->as.if_stmt.then_branch, table);

        if (node->as.if_stmt.else_branch != NULL)
        {
            semantic_analysis(node->as.if_stmt.else_branch, table);
        }

        break;

    case NODE_WHILE_STMT:
        // Check condition type
        if (check_types(node->as.while_stmt.condition, table) != TYPE_BOOL)
        {
            fprintf(stderr, "Line %d: Error: While condition must be a boolean expression\n",
                    node->line_number);
        }

        // Analyze body
        semantic_analysis(node->as.while_stmt.body, table);
        break;

    case NODE_FOR_STMT:
        // Enter new scope for the for-loop variables
        enter_scope(table);

        // Analyze initialization
        semantic_analysis(node->as.for_stmt.init, table);

        // Check condition type
        if (check_types(node->as.for_stmt.condition, table) != TYPE_BOOL)
        {
            fprintf(stderr, "Line %d: Error: For loop condition must be a boolean expression\n",
                    node->line_number);
        }

        // Check update expression
        check_types(node->as.for_stmt.update, table);

        // Analyze body
        semantic_analysis(node->as.for_stmt.body, table);

        // Exit for-loop scope
        exit_scope(table);
        break;

    case NODE_EXPR_STMT:
        // Check expression type
        if (node->as.expr_stmt.expr != NULL)
        {
            check_types(node->as.expr_stmt.expr, table);
        }
        break;

    case NODE_RETURN_STMT:
        // Check the expression in the return statement
        if (node->as.return_stmt.expr != NULL)
        {
            check_types(node->as.return_stmt.expr, table);
        }
        break;

    default:
        // Other node types don't need special semantic analysis
        break;
    }
}

// Add this function at the end of the file, before the last #endif
void generate_graphviz(ASTNode* node, FILE* out) {
    if (node == NULL) return;

    // Generate unique node ID
    fprintf(out, "    node%p [label=\"", (void*)node);
    
    // Print node label based on type
    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "Program");
            break;
        case NODE_FUNCTION_DECL:
            fprintf(out, "Function: %s", node->as.function_decl.name);
            break;
        case NODE_PARAM_LIST:
            fprintf(out, "ParamList");
            break;
        case NODE_PARAM:
            fprintf(out, "Param: %s", node->as.param.name);
            break;
        case NODE_VAR_DECL:
            fprintf(out, "Var: %s", node->as.var_decl.name);
            break;
        case NODE_BINARY_EXPR:
            fprintf(out, "Binary: %s", get_op_type_str(node->as.binary_expr.op));
            break;
        case NODE_UNARY_EXPR:
            fprintf(out, "Unary: %s", get_op_type_str(node->as.unary_expr.op));
            break;
        case NODE_ASSIGN_EXPR:
            fprintf(out, "Assign");
            break;
        case NODE_FUNC_CALL:
            fprintf(out, "Call: %s", node->as.func_call.name);
            break;
        case NODE_VAR_REF:
            fprintf(out, "VarRef: %s", node->as.var_ref.name);
            break;
        case NODE_INT_LITERAL:
            fprintf(out, "Int: %d", node->as.int_literal.value);
            break;
        case NODE_FLOAT_LITERAL:
            fprintf(out, "Float: %f", node->as.float_literal.value);
            break;
        case NODE_BOOL_LITERAL:
            fprintf(out, "Bool: %s", node->as.bool_literal.value ? "true" : "false");
            break;
        case NODE_STRING_LITERAL:
            fprintf(out, "String: %s", node->as.string_literal.value);
            break;
        case NODE_IF_STMT:
            fprintf(out, "If");
            break;
        case NODE_WHILE_STMT:
            fprintf(out, "While");
            break;
        case NODE_FOR_STMT:
            fprintf(out, "For");
            break;
        case NODE_SWITCH_STMT:
            fprintf(out, "Switch");
            break;
        case NODE_CASE_STMT:
            if (node->as.case_stmt.value == -1) {
                fprintf(out, "  node%p [label=\"Default Case\"];\n", node);
            } else {
                fprintf(out, "  node%p [label=\"Case %d\"];\n", node, node->as.case_stmt.value);
            }
            
            if (node->as.case_stmt.body) {
                fprintf(out, "  node%p -> node%p [label=\"body\"];\n", node, node->as.case_stmt.body);
                generate_graphviz(node->as.case_stmt.body, out);
            }
            break;
        case NODE_RETURN_STMT:
            fprintf(out, "Return");
            break;
        case NODE_EXPR_STMT:
            fprintf(out, "ExprStmt");
            break;
        case NODE_BLOCK:
            fprintf(out, "Block");
            break;
        default:
            fprintf(out, "%s", get_node_type_str(node->type));
    }
    fprintf(out, "\"];\n");

    // Add edges to children
    switch (node->type) {
        case NODE_PROGRAM:
            for (int i = 0; i < node->as.program.declaration_count; i++) {
                fprintf(out, "    node%p -> node%p;\n", (void*)node, (void*)node->as.program.declarations[i]);
                generate_graphviz(node->as.program.declarations[i], out);
            }
            break;
        case NODE_FUNCTION_DECL:
            if (node->as.function_decl.params) {
                fprintf(out, "    node%p -> node%p [label=\"params\"];\n", (void*)node, (void*)node->as.function_decl.params);
                generate_graphviz(node->as.function_decl.params, out);
            }
            if (node->as.function_decl.body) {
                fprintf(out, "    node%p -> node%p [label=\"body\"];\n", (void*)node, (void*)node->as.function_decl.body);
                generate_graphviz(node->as.function_decl.body, out);
            }
            break;
        case NODE_PARAM_LIST:
            for (int i = 0; i < node->as.param_list.param_count; i++) {
                fprintf(out, "    node%p -> node%p;\n", (void*)node, (void*)node->as.param_list.params[i]);
                generate_graphviz(node->as.param_list.params[i], out);
            }
            break;
        case NODE_PARAM:
            // Parameters don't have children
            break;
        case NODE_VAR_DECL:
            if (node->as.var_decl.init_expr) {
                fprintf(out, "    node%p -> node%p [label=\"init\"];\n", (void*)node, (void*)node->as.var_decl.init_expr);
                generate_graphviz(node->as.var_decl.init_expr, out);
            }
            break;
        case NODE_BINARY_EXPR:
            fprintf(out, "    node%p -> node%p [label=\"left\"];\n", (void*)node, (void*)node->as.binary_expr.left);
            fprintf(out, "    node%p -> node%p [label=\"right\"];\n", (void*)node, (void*)node->as.binary_expr.right);
            generate_graphviz(node->as.binary_expr.left, out);
            generate_graphviz(node->as.binary_expr.right, out);
            break;
        case NODE_UNARY_EXPR:
            fprintf(out, "    node%p -> node%p;\n", (void*)node, (void*)node->as.unary_expr.expr);
            generate_graphviz(node->as.unary_expr.expr, out);
            break;
        case NODE_ASSIGN_EXPR:
            fprintf(out, "    node%p -> node%p [label=\"left\"];\n", (void*)node, (void*)node->as.assign_expr.left);
            fprintf(out, "    node%p -> node%p [label=\"right\"];\n", (void*)node, (void*)node->as.assign_expr.right);
            generate_graphviz(node->as.assign_expr.left, out);
            generate_graphviz(node->as.assign_expr.right, out);
            break;
        case NODE_FUNC_CALL:
            for (int i = 0; i < node->as.func_call.arg_count; i++) {
                fprintf(out, "    node%p -> node%p [label=\"arg%d\"];\n", (void*)node, (void*)node->as.func_call.args[i], i);
                generate_graphviz(node->as.func_call.args[i], out);
            }
            break;
        case NODE_VAR_REF:
            // Variable references don't have children
            break;
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL:
        case NODE_BOOL_LITERAL:
        case NODE_STRING_LITERAL:
            // Literals don't have children
            break;
        case NODE_IF_STMT:
            fprintf(out, "    node%p -> node%p [label=\"cond\"];\n", (void*)node, (void*)node->as.if_stmt.condition);
            fprintf(out, "    node%p -> node%p [label=\"then\"];\n", (void*)node, (void*)node->as.if_stmt.then_branch);
            if (node->as.if_stmt.else_branch) {
                fprintf(out, "    node%p -> node%p [label=\"else\"];\n", (void*)node, (void*)node->as.if_stmt.else_branch);
                generate_graphviz(node->as.if_stmt.else_branch, out);
            }
            generate_graphviz(node->as.if_stmt.condition, out);
            generate_graphviz(node->as.if_stmt.then_branch, out);
            break;
        case NODE_WHILE_STMT:
            fprintf(out, "    node%p -> node%p [label=\"cond\"];\n", (void*)node, (void*)node->as.while_stmt.condition);
            fprintf(out, "    node%p -> node%p [label=\"body\"];\n", (void*)node, (void*)node->as.while_stmt.body);
            generate_graphviz(node->as.while_stmt.condition, out);
            generate_graphviz(node->as.while_stmt.body, out);
            break;
        case NODE_FOR_STMT:
            if (node->as.for_stmt.init) {
                fprintf(out, "    node%p -> node%p [label=\"init\"];\n", (void*)node, (void*)node->as.for_stmt.init);
                generate_graphviz(node->as.for_stmt.init, out);
            }
            if (node->as.for_stmt.condition) {
                fprintf(out, "    node%p -> node%p [label=\"cond\"];\n", (void*)node, (void*)node->as.for_stmt.condition);
                generate_graphviz(node->as.for_stmt.condition, out);
            }
            if (node->as.for_stmt.update) {
                fprintf(out, "    node%p -> node%p [label=\"update\"];\n", (void*)node, (void*)node->as.for_stmt.update);
                generate_graphviz(node->as.for_stmt.update, out);
            }
            if (node->as.for_stmt.body) {
                fprintf(out, "    node%p -> node%p [label=\"body\"];\n", (void*)node, (void*)node->as.for_stmt.body);
                generate_graphviz(node->as.for_stmt.body, out);
            }
            break;
        case NODE_SWITCH_STMT: {
            fprintf(out, "  node%p [label=\"Switch Statement\"];\n", node);
            fprintf(out, "  node%p -> node%p [label=\"expression\"];\n", node, node->as.switch_stmt.expr);
            generate_graphviz(node->as.switch_stmt.expr, out);
            
            fprintf(out, "  node%p -> node%p [label=\"cases\"];\n", node, node->as.switch_stmt.cases);
            generate_graphviz(node->as.switch_stmt.cases, out);
            break;
        }
        case NODE_CASE_LIST: {
            fprintf(out, "  node%p [label=\"Case List\"];\n", node);
            for (int i = 0; i < node->as.case_list.case_count; i++) {
                fprintf(out, "  node%p -> node%p [label=\"case %d\"];\n", node, node->as.case_list.cases[i], i);
                generate_graphviz(node->as.case_list.cases[i], out);
            }
            break;
        }
        case NODE_CASE_STMT:
            if (node->as.case_stmt.body) {
                fprintf(out, "    node%p -> node%p [label=\"body\"];\n", (void*)node, (void*)node->as.case_stmt.body);
                generate_graphviz(node->as.case_stmt.body, out);
            }
            break;
        case NODE_RETURN_STMT:
            if (node->as.return_stmt.expr) {
                fprintf(out, "    node%p -> node%p;\n", (void*)node, (void*)node->as.return_stmt.expr);
                generate_graphviz(node->as.return_stmt.expr, out);
            }
            break;
        case NODE_EXPR_STMT:
            if (node->as.expr_stmt.expr) {
                fprintf(out, "    node%p -> node%p;\n", (void*)node, (void*)node->as.expr_stmt.expr);
                generate_graphviz(node->as.expr_stmt.expr, out);
            }
            break;
        case NODE_BLOCK:
            for (int i = 0; i < node->as.block.statement_count; i++) {
                fprintf(out, "    node%p -> node%p;\n", (void*)node, (void*)node->as.block.statements[i]);
                generate_graphviz(node->as.block.statements[i], out);
            }
            break;
    }
}

void print_ast_graphviz(ASTNode* node, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (!out) {
        fprintf(stderr, "Cannot open file %s for writing\n", filename);
        return;
    }

    fprintf(out, "digraph AST {\n");
    fprintf(out, "    node [shape=box];\n");
    generate_graphviz(node, out);
    fprintf(out, "}\n");
    fclose(out);
}