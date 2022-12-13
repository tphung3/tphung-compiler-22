.data
c1: .quad 1
.data
c3: .quad 100
.text
.globl C
C:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
pushq %rsi
subq $24, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $11, %rbx
movq %rbx, -24(%rbp)
MOVQ $12, %rbx
movq %rbx, -32(%rbp)
MOVQ $13, %rbx
movq %rbx, -40(%rbp)
MOVQ -8(%rbp), %rbx
MOVQ -16(%rbp), %r10
MOVQ -24(%rbp), %r11
MOVQ -32(%rbp), %r12
ADDQ %r12, %r11
ADDQ %r11, %r10
ADDQ %r10, %rbx
movq %rbx, %rax
jmp .L1
.L1: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $1, %rbx
MOVQ $2, %r10
MOVQ %rbx, %rdi
MOVQ %r10, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL C
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L2
.L2: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
