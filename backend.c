#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>

// Define general-purpose registers for x86-64
const char* registers[] = { "%rax", "%rbx", "%rcx", "%rdx", "%rsi", "%rdi", "%r8", "%r9", "%r10", "%r11" };
const char* reg32[] = { "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%r8d", "%r9d", "%r10d", "%r11d" };
#define MAX_REGS 10
#define MAX_VARS 100
#define MAX_LINE_LENGTH 2048
int DEBUG = 0;  // Debug flag, can be set by verbosity flag

// Symbol table for variables
typedef struct {
    char name[64];
    int offset;       // Stack offset, negative from %rbp
    bool is_alloca;   // Is this an alloca instruction
} VarInfo;

VarInfo var_table[MAX_VARS];
int var_count = 0;
int stack_offset = 0;  // Current stack offset
char last_temp_var[64] = {0}; // Store the last temporary variable name

// Debug print function
void debug_print(const char* format, ...) {
    if (DEBUG) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}

// Function to extract variable name from an LLVM variable
void extract_var_name(char* dest, const char* src) {
    int i = 0;
    // Skip % or @ prefix if present
    if (src[0] == '%' || src[0] == '@') {
        src++;
    }
    
    // Copy until space, comma, or special chars
    while (src[i] && !isspace(src[i]) && src[i] != ',' && src[i] != '(' && src[i] != ')') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Add variable to table and assign stack location
int add_var(const char* name, bool is_alloca) {
    // Check if name is already in the table
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return i; // Variable already exists
        }
    }
    
    if (var_count < MAX_VARS) {
        strcpy(var_table[var_count].name, name);
        
        if (is_alloca) {
            stack_offset += 8; // Assuming 8-byte alignment for all allocations
            var_table[var_count].offset = stack_offset;
            var_table[var_count].is_alloca = true;
        } else {
            var_table[var_count].offset = 0;
            var_table[var_count].is_alloca = false;
        }
        
        return var_count++;
    }
    
    fprintf(stderr, "Error: Too many variables\n");
    return -1;
}

// Find variable in table
int find_var(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Check if a string is an integer
bool is_integer(const char* str) {
    if (!str || *str == '\0') return false;
    
    // Skip minus sign if present
    if (*str == '-') str++;
    
    // Empty string or just a minus sign is not an integer
    if (*str == '\0') return false;
    
    // Check each character
    while (*str) {
        if (!isdigit(*str)) return false;
        str++;
    }
    
    return true;
}

// Process LLVM IR and generate assembly code
void generate_assembly(const char* input_file, const char* output_file) {
    FILE* ir = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");

    if (!ir || !out) {
        perror("File open failed");
        exit(1);
    }

    // Reset variable table
    var_count = 0;
    stack_offset = 0;
    last_temp_var[0] = '\0';

    fprintf(out, 
        "# Generated x86-64 assembly from LLVM IR\n"
        ".text\n"
        ".globl main\n"
        "main:\n"
        "    pushq %%rbp\n"
        "    movq %%rsp, %%rbp\n"
    );

    // First scan to identify alloca instructions and calculate stack size
    char line[MAX_LINE_LENGTH];
    fseek(ir, 0, SEEK_SET);
    
    while (fgets(line, sizeof(line), ir)) {
        char var_name[64] = {0};
        
        // Skip lines that don't have LLVM instructions
        if (line[0] == ';' || line[0] == '\n' || strstr(line, "define") || 
            strstr(line, "ModuleID") || strstr(line, "source_filename") || 
            strstr(line, "target") || strstr(line, "}")) {
            continue;
        }
        
        // Process alloca instructions
        if (strstr(line, "alloca")) {
            char* equals_pos = strchr(line, '=');
            if (equals_pos) {
                // Extract the variable name before the equals sign
                char* start = line;
                while (isspace(*start)) start++; // Skip leading whitespace
                if (*start == '%') {
                    start++; // Skip %
                    int i = 0;
                    while (start < equals_pos && !isspace(*start)) {
                        var_name[i++] = *start++;
                    }
                    var_name[i] = '\0';
                    
                    // Now add the variable to our table
                    if (var_name[0] != '\0') {
                        add_var(var_name, true);
                        debug_print("Added alloca variable: %s at offset -%d\n", var_name, stack_offset);
                    }
                }
            }
        }
    }
    
    // Allocate stack space
    if (stack_offset > 0) {
        fprintf(out, "    subq $%d, %%rsp     # Allocate stack space\n", stack_offset);
    }
    
    // Second scan to generate actual assembly instructions
    fseek(ir, 0, SEEK_SET);
    
    while (fgets(line, sizeof(line), ir)) {
        char dest_var[64] = {0};
        char src1[64] = {0}, src2[64] = {0};
        int immediate = 0;
        
        // Skip non-instruction lines
        if (line[0] == ';' || line[0] == '\n' || strstr(line, "define") || 
            strstr(line, "ModuleID") || strstr(line, "source_filename") || 
            strstr(line, "target") || strstr(line, "}") || strstr(line, "entry:")) {
            continue;
        }
        
        // Comment for clarity
        fprintf(out, "\n    # %s", line);
        
        // Extract the destination variable if line contains '='
        char* equals_pos = strchr(line, '=');
        if (equals_pos) {
            char* start = line;
            while (isspace(*start)) start++; // Skip leading whitespace
            if (*start == '%') {
                start++; // Skip %
                int i = 0;
                while (start < equals_pos && !isspace(*start)) {
                    dest_var[i++] = *start++;
                }
                dest_var[i] = '\0';
                
                // Save the destination variable as the last temp
                if (dest_var[0] != '\0') {
                    strcpy(last_temp_var, dest_var);
                    debug_print("Last temp var set to: %s\n", last_temp_var);
                }
            }
        }
        
        // Handle store instructions
        if (strstr(line, "store i32")) {
            char* store_pos = strstr(line, "store i32");
            if (store_pos) {
                char* comma_pos = strchr(store_pos, ',');
                if (comma_pos) {
                    // Extract source value
                    char source_val[64] = {0};
                    char* val_start = store_pos + 9; // Skip "store i32"
                    while (isspace(*val_start)) val_start++; // Skip whitespace
                    
                    // Check if it's an immediate or a variable
                    if (isdigit(*val_start) || *val_start == '-') {
                        // It's an immediate value
                        sscanf(val_start, "%d", &immediate);
                        debug_print("Store immediate: %d\n", immediate);
                    } else if (*val_start == '%') {
                        // It's a variable reference
                        val_start++; // Skip %
                        int i = 0;
                        while (val_start < comma_pos && !isspace(*val_start) && *val_start != ',') {
                            source_val[i++] = *val_start++;
                        }
                        source_val[i] = '\0';
                        debug_print("Store from variable: %s\n", source_val);
                    }
                    
                    // Extract destination
                    char* ptr_pos = strstr(comma_pos, "ptr %");
                    if (ptr_pos) {
                        ptr_pos += 5; // Skip "ptr %"
                        int i = 0;
                        while (*ptr_pos && !isspace(*ptr_pos) && *ptr_pos != ',' && *ptr_pos != ')') {
                            dest_var[i++] = *ptr_pos++;
                        }
                        dest_var[i] = '\0';
                        debug_print("Store to variable: %s\n", dest_var);
                    }
                    
                    // Generate assembly
                    int dest_idx = find_var(dest_var);
                    if (dest_idx >= 0) {
                        if (source_val[0] != '\0') {
                            // If the source is the last temp var, its value is in %eax
                            if (strcmp(source_val, last_temp_var) == 0) {
                                fprintf(out, "    movl %%eax, -%d(%%rbp)\n", var_table[dest_idx].offset);
                            } else {
                                int src_idx = find_var(source_val);
                                if (src_idx >= 0) {
                                    fprintf(out, "    movl -%d(%%rbp), %%eax\n", var_table[src_idx].offset);
                                    fprintf(out, "    movl %%eax, -%d(%%rbp)\n", var_table[dest_idx].offset);
                                } else {
                                    // Handle register or temporary
                                    fprintf(out, "    # Source not found: %s\n", source_val);
                                }
                            }
                        } else {
                            // Store immediate
                            fprintf(out, "    movl $%d, -%d(%%rbp)\n", immediate, var_table[dest_idx].offset);
                        }
                    } else {
                        fprintf(out, "    # Destination not found: %s\n", dest_var);
                    }
                }
            }
        }
        // Handle load instructions
        else if (strstr(line, "load i32")) {
            char* load_pos = strstr(line, "load i32");
            if (load_pos) {
                // Extract source variable
                char* ptr_pos = strstr(load_pos, "ptr %");
                if (ptr_pos) {
                    ptr_pos += 5; // Skip "ptr %"
                    int i = 0;
                    while (*ptr_pos && !isspace(*ptr_pos) && *ptr_pos != ',' && *ptr_pos != ')') {
                        src1[i++] = *ptr_pos++;
                    }
                    src1[i] = '\0';
                    debug_print("Load from variable: %s to %s\n", src1, dest_var);
                }
                
                // Generate assembly
                int src_idx = find_var(src1);
                if (src_idx >= 0) {
                    add_var(dest_var, false); // Add destination variable to table
                    fprintf(out, "    movl -%d(%%rbp), %%eax\n", var_table[src_idx].offset);
                } else {
                    fprintf(out, "    # Source not found: %s\n", src1);
                }
            }
        }
        // Handle shift left operations (for strength reduction)
        else if (strstr(line, "shl i32")) {
            char* shl_pos = strstr(line, "shl i32");
            if (shl_pos) {
                // Extract source variable
                char* src_pos = shl_pos + 7; // Skip "shl i32"
                while (isspace(*src_pos)) src_pos++; // Skip whitespace
                if (*src_pos == '%') {
                    src_pos++; // Skip %
                    int i = 0;
                    char* comma_pos = strchr(src_pos, ',');
                    if (comma_pos) {
                        while (src_pos < comma_pos && !isspace(*src_pos) && *src_pos != ',') {
                            src1[i++] = *src_pos++;
                        }
                        src1[i] = '\0';
                        
                        // Extract shift amount
                        src_pos = comma_pos + 1;
                        while (isspace(*src_pos)) src_pos++; // Skip whitespace
                        sscanf(src_pos, "%d", &immediate);
                        
                        debug_print("Shift left: %s by %d to %s\n", src1, immediate, dest_var);
                        
                        // Generate assembly - result will be in %eax
                        add_var(dest_var, false); // Add destination variable to table
                        fprintf(out, "    # Shift left by %d\n", immediate);
                        fprintf(out, "    shll $%d, %%eax\n", immediate);
                    }
                }
            }
        }
        // Handle return instructions
        else if (strstr(line, "ret i32")) {
            char* ret_pos = strstr(line, "ret i32");
            if (ret_pos) {
                char* val_start = ret_pos + 7; // Skip "ret i32"
                while (isspace(*val_start)) val_start++; // Skip whitespace
                
                if (isdigit(*val_start) || *val_start == '-') {
                    // It's an immediate value
                    sscanf(val_start, "%d", &immediate);
                    fprintf(out, "    movl $%d, %%eax\n", immediate);
                    debug_print("Return immediate: %d\n", immediate);
                } else if (*val_start == '%') {
                    // It's a variable reference
                    val_start++; // Skip %
                    char ret_var[64] = {0};
                    int i = 0;
                    while (*val_start && !isspace(*val_start) && *val_start != ',') {
                        ret_var[i++] = *val_start++;
                    }
                    ret_var[i] = '\0';
                    
                    debug_print("Return variable: %s\n", ret_var);
                    
                    // If returning the last temp var, the value is already in %eax
                    if (strcmp(ret_var, last_temp_var) != 0) {
                        int var_idx = find_var(ret_var);
                        if (var_idx >= 0) {
                            fprintf(out, "    movl -%d(%%rbp), %%eax\n", var_table[var_idx].offset);
                        } else {
                            fprintf(out, "    # Return var not found: %s\n", ret_var);
                        }
                    } else {
                        fprintf(out, "    # Return value already in %%eax\n");
                    }
                }
            }
        }
        // Handle addition operations
        else if (strstr(line, "add i32")) {
            char* add_pos = strstr(line, "add i32");
            if (add_pos) {
                // Extract first source operand
                char* src_pos = add_pos + 7; // Skip "add i32"
                while (isspace(*src_pos)) src_pos++; // Skip whitespace
                
                if (*src_pos == '%') {
                    src_pos++; // Skip %
                    int i = 0;
                    char* comma_pos = strchr(src_pos, ',');
                    if (comma_pos) {
                        while (src_pos < comma_pos && !isspace(*src_pos) && *src_pos != ',') {
                            src1[i++] = *src_pos++;
                        }
                        src1[i] = '\0';
                        
                        // Extract second source operand
                        src_pos = comma_pos + 1;
                        while (isspace(*src_pos)) src_pos++; // Skip whitespace
                        
                        if (*src_pos == '%') {
                            src_pos++; // Skip %
                            i = 0;
                            while (*src_pos && !isspace(*src_pos) && *src_pos != ',') {
                                src2[i++] = *src_pos++;
                            }
                            src2[i] = '\0';
                            debug_print("Add variables: %s + %s to %s\n", src1, src2, dest_var);
                        } else if (isdigit(*src_pos) || *src_pos == '-') {
                            // It's an immediate value
                            sscanf(src_pos, "%d", &immediate);
                            debug_print("Add immediate: %s + %d to %s\n", src1, immediate, dest_var);
                        }
                        
                        // Generate assembly
                        add_var(dest_var, false); // Add destination variable to table
                        
                        int src1_idx = find_var(src1);
                        if (src1_idx >= 0) {
                            fprintf(out, "    movl -%d(%%rbp), %%eax\n", var_table[src1_idx].offset);
                        } else if (strcmp(src1, last_temp_var) == 0) {
                            // Value already in %eax
                        } else {
                            fprintf(out, "    # Source 1 not found: %s\n", src1);
                        }
                        
                        if (src2[0] != '\0') {
                            int src2_idx = find_var(src2);
                            if (src2_idx >= 0) {
                                fprintf(out, "    addl -%d(%%rbp), %%eax\n", var_table[src2_idx].offset);
                            } else if (strcmp(src2, last_temp_var) == 0) {
                                // Need to move %eax to another register first
                                fprintf(out, "    movl %%eax, %%ebx\n");
                                fprintf(out, "    addl %%ebx, %%eax\n");
                            } else {
                                fprintf(out, "    # Source 2 not found: %s\n", src2);
                            }
                        } else {
                            fprintf(out, "    addl $%d, %%eax\n", immediate);
                        }
                    }
                }
            }
        }
    }

    // Function epilogue
    fprintf(out,
        "    leave\n"
        "    ret\n"
    );

    fclose(ir);
    fclose(out);
    printf("✅ Assembly written to %s\n", output_file);
}

int main(int argc, char* argv[]) {
    const char* input_file = NULL;
    const char* output_file = "output.s";
    bool verbose = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (input_file == NULL) {
            input_file = argv[i];
        }
    }
    
    // Set DEBUG based on verbose flag
    DEBUG = verbose;
    
    // If no input file is specified, print usage
    if (input_file == NULL) {
        printf("Usage: %s [options] <input_llvm_ir>\n", argv[0]);
        printf("Options:\n");
        printf("  -v, --verbose     Enable verbose output\n");
        printf("  -o <file>         Specify output assembly file (default: output.s)\n");
        return 1;
    }
    
    generate_assembly(input_file, output_file);
    
    // Assemble the file if requested
    if (verbose) {
        printf("Assembly file %s generated.\n", output_file);
        printf("To assemble and run the file:\n");
        printf("  gcc -o program %s\n", output_file);
        printf("  ./program\n");
    }
    
    return 0;
}
