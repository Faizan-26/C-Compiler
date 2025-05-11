# Generated x86-64 assembly from LLVM IR
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp

    #   ret i32 40
    movl $40, %eax
    leave
    ret
