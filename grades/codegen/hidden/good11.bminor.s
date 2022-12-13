.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $40, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $20, %rbx
movq %rbx, -8(%rbp)
MOVQ -8(%rbp), %rbx
movq %rbx, -16(%rbp)
MOVQ $10, %rbx
movq %rbx, -24(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -24(%rbp), %r10
ADDQ %r10, %rbx
MOVQ %rbx, -16(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -8(%rbp), %r10
ADDQ %r10, %rbx
MOVQ %rbx, -16(%rbp)
MOVQ $2, %rbx
movq %rbx, -32(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -32(%rbp), %r10
ADDQ %r10, %rbx
MOVQ %rbx, -16(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -8(%rbp), %r10
ADDQ %r10, %rbx
MOVQ %rbx, -16(%rbp)
MOVQ $3, %rbx
movq %rbx, -40(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -40(%rbp), %r10
ADDQ %r10, %rbx
MOVQ %rbx, -16(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -8(%rbp), %r10
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
