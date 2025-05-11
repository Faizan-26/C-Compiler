# Generated x86-64 assembly from LLVM IR
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp     # Allocate stack space

    #   %x = alloca i32, align 4

    #   store i32 5, ptr %x, align 4
    movl $5, -8(%rbp)

    #   %y = alloca i32, align 4

    #   %load = load i32, ptr %x, align 4
    movl -8(%rbp), %eax

    #   %shltmp = shl i32 %load, 3
    # Shift left by 3
    shll $3, %eax

    #   store i32 %shltmp, ptr %y, align 4
    movl %eax, -16(%rbp)

    #   %load1 = load i32, ptr %y, align 4
    movl -16(%rbp), %eax

    #   ret i32 %load1
    # Return value already in %eax
    leave
    ret
