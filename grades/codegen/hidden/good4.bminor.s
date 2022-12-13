.text
.globl collatz
collatz:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
pushq %rsi
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ -8(%rbp), %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_integer
popq %r11
popq %r10
MOVQ $10, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_character
popq %r11
popq %r10
MOVQ -8(%rbp), %rbx
MOVQ $1, %r10
CMPQ %rbx, %r10
JE .L2
MOVQ $0, %r11
JMP .L3
.L2:
MOVQ $1, %r11
.L3:
cmp $0, %r11
je .L4
MOVQ -16(%rbp), %rbx
movq %rbx, %rax
jmp .L1
jmp .L5
.L4:
.L5:
MOVQ -8(%rbp), %rbx
MOVQ $2, %r10
movq $0, %rdx
MOVQ %rbx, %rax
IDIV %r10
MOVQ %rdx, %rbx
MOVQ $0, %r10
CMPQ %rbx, %r10
JE .L6
MOVQ $0, %r11
JMP .L7
.L6:
MOVQ $1, %r11
.L7:
cmp $0, %r11
je .L8
MOVQ -8(%rbp), %rbx
MOVQ $2, %r10
movq $0, %rdx
MOVQ %rbx, %rax
IDIV %r10
MOVQ %rax, %rbx
MOVQ -16(%rbp), %r10
MOVQ $1, %r11
ADDQ %r11, %r10
MOVQ %rbx, %rdi
MOVQ %r10, %rsi
MOVQ %r11, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL collatz
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L1
jmp .L9
.L8:
MOVQ $3, %rbx
MOVQ -8(%rbp), %r10
MOVQ %rbx, %rax
IMUL %r10
MOVQ %rax, %rbx
MOVQ $1, %r10
ADDQ %r10, %rbx
MOVQ -16(%rbp), %r10
MOVQ $1, %r11
ADDQ %r11, %r10
MOVQ %rbx, %rdi
MOVQ %r10, %rsi
MOVQ %r11, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL collatz
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L1
.L9:
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
MOVQ $27, %rbx
MOVQ $0, %r10
MOVQ %rbx, %rdi
MOVQ %r10, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL collatz
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L10
.L10: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
