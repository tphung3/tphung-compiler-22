.data
a1: 
.data
a2: .quad 111
.data
a3: .quad 0
.text
.globl A
A:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ a3, %rbx
cmp $0, %rbx
je .L2
MOVQ a1, %rbx
MOVQ a2, %r10
MOVQ %rbx, %rax
IMUL %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L1
jmp .L3
.L2:
.L3:
MOVQ $3, %rbx
movq %rbx, -8(%rbp)
MOVQ a3, %rbx
NOT %rbx
NOT %rbx
NOT %rbx
cmp $0, %rbx
je .L4
MOVQ a1, %rbx
MOVQ -8(%rbp), %r10
ADDQ %r10, %rbx
movq %rbx, %rax
jmp .L1
jmp .L5
.L4:
.L5:
MOVQ $0, %rbx
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
MOVQ $1, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL A
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L6
.L6: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
