.data
X: .quad 1
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $3, %rbx
movq %rbx, -8(%rbp)
MOVQ $1, %rbx
movq %rbx, -16(%rbp)
.data
.L2: .string "hah"
.text
leaq .L2, %rbx
movq %rbx, -24(%rbp)
MOVQ -8(%rbp), %rbx
MOVQ $2, %r10
ADDQ %r10, %rbx
movq %rbx, -32(%rbp)
MOVQ $0, %rbx
movq %rbx, -40(%rbp)
MOVQ $99, %rbx
movq %rbx, -48(%rbp)
MOVQ -40(%rbp), %rbx
cmp $0, %rbx
je .L3
MOVQ $0, %rbx
movq %rbx, %rax
jmp .L1
jmp .L4
.L3:
.L4:
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
