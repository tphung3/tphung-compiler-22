.text
.globl f
f:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ -8(%rbp), %rbx
NOT %rbx
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
.data
x: .quad 4
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
MOVQ $10, %rbx
movq %rbx, -8(%rbp)
MOVQ x, %rbx
MOVQ -8(%rbp), %r10
CMPQ %rbx, %r10
JGE .L3
MOVQ $0, %r11
JMP .L4
.L3:
MOVQ $1, %r11
.L4:
MOVQ %r11, %rdi
MOVQ %r10, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ %rbx, %rdi
MOVQ %r11, %rsi
MOVQ %r10, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ %rbx, %rdi
MOVQ %rbx, %rsi
MOVQ %r11, %rdx
MOVQ %r10, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ %rbx, %rdi
MOVQ %rbx, %rsi
MOVQ %rbx, %rdx
MOVQ %r11, %rcx
MOVQ %r10, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ %rbx, %rdi
MOVQ %rbx, %rsi
MOVQ %rbx, %rdx
MOVQ %rbx, %rcx
MOVQ %r11, %r8
MOVQ %r10, %r9
PUSHQ %r10
PUSHQ %r11
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
cmp $0, %rbx
je .L5
MOVQ $1, %rbx
movq %rbx, %rax
jmp .L2
jmp .L6
.L5:
MOVQ x, %rbx
MOVQ -8(%rbp), %r10
MOVQ x, %r11
MOVQ -8(%rbp), %r12
MOVQ %r11, %rax
IMUL %r12
MOVQ %rax, %r11
SUBQ %r11, %r10
CMPQ %rbx, %r10
JG .L7
MOVQ $0, %r11
JMP .L8
.L7:
MOVQ $1, %r11
.L8:
cmp $0, %r11
je .L9
MOVQ $4, %rbx
movq %rbx, %rax
jmp .L2
jmp .L10
.L9:
MOVQ $2, %rbx
movq %rbx, %rax
jmp .L2
.L10:
.L6:
.L2: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
