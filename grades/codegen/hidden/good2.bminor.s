.data
X: .quad 11, 30, 22, 0
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
