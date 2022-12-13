.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $3, %rbx
movq %rbx, -8(%rbp)
.data
.L2: .string "hah"
.text
leaq .L2, %rbx
movq %rbx, -16(%rbp)
MOVQ -8(%rbp), %rbx
MOVQ $2, %r10
ADDQ %r10, %rbx
movq %rbx, -24(%rbp)
MOVQ $1, %rbx
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
