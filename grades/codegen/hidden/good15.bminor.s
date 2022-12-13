.text
.globl strdup
strdup:
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
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
.data
.L3: .string "sssss"
.text
leaq .L3, %rbx
movq %rbx, -8(%rbp)
MOVQ -8(%rbp), %rbx
MOVQ %rbx, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL strdup
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
movq %rbx, -16(%rbp)
MOVQ -8(%rbp), %rbx
MOVQ -16(%rbp), %r10
CMPQ %rbx, %r10
JE .L4
MOVQ $0, %r11
JMP .L5
.L4:
MOVQ $1, %r11
.L5:
cmp $0, %r11
je .L6
MOVQ $22, %rbx
movq %rbx, %rax
jmp .L2
jmp .L7
.L6:
MOVQ $11, %rbx
movq %rbx, %rax
jmp .L2
.L7:
.L2: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
