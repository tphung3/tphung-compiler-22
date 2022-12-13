.text
.globl abs
abs:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
.L1: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
.data
digits: .quad 14, 8, 6168, 42, 0, 74546
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
MOVQ $468, %rbx
MOVQ $0, %r10
SUBQ %rbx, %r10
