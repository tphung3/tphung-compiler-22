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
MOVQ $4, %rbx
MOVQ $9, %r10
MOVQ $2, %r11
MOVQ $0, %r12
SUBQ %r11, %r12
MOVQ $5, %r11
MOVQ $0, %r13
SUBQ %r11, %r13
SUBQ %r13, %r12
movq $0, %rdx
MOVQ %r10, %rax
IDIV %r12
MOVQ %rax, %r10
MOVQ $2, %r11
MOVQ $1, %r12
ADDQ %r12, %r11
MOVQ $4, %r12
MOVQ %r11, %rax
IMUL %r12
MOVQ %rax, %r11
MOVQ $1, %r12
SUBQ %r12, %r11
MOVQ $3, %r12
movq $0, %rdx
MOVQ %r11, %rax
IDIV %r12
MOVQ %rdx, %r11
MOVQ $7, %r12
MOVQ %r11, %rax
IMUL %r12
MOVQ %rax, %r11
MOVQ $2, %r12
MOVQ $3, %r13
MOVQ $1, %rax
CMPQ %r13, $0
JE .L2
JL .L4
.L3:
MOVQ %rax, %r14
CMPQ %r13, $0
JE .L5
SUBQ $1, %r13
IMUL %r12
JMP .L3
.L2:
MOVQ $1, %r14
JMP .L5
.L4:
MOVQ $0, %r14
.L5
SUBQ %r14, %r11
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
