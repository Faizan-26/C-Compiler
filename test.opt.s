# Generated x86-64 assembly from LLVM IR
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp

    #   %addtmp = add i32 %b, %a
    # Source 1 not found: b
    # Source 2 not found: a

    #   ret i32 %addtmp
    # Return value already in %eax

    #   ret i32 15
    movl $15, %eax
    leave
    ret
