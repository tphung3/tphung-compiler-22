.text
.globl A
A:
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
.globl B
B:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
.L2: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
.text
.globl C
C:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
.L3: 
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
subq $8, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $100, %rbx
MOVQ %rbx, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL B
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ $1, %r10
SUBQ %r10, %rbx
MOVQ $10, %r10
MOVQ %rbx, %rdi
MOVQ %r10, %rsi
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
cmp $0, %rbx
je .L5
MOVQ $3, %rbx
movq %rbx, -8(%rbp)
MOVQ $2, %rbx
MOVQ $33, %r10
MOVQ %r10, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL B
POPQ %r11
POPQ %r10
MOVQ %rax, %r10
MOVQ %rbx, %rax
IMUL %r10
MOVQ %rax, %rbx
MOVQ -8(%rbp), %r10
ADDQ %r10, %rbx
movq %rbx, %rax
jmp .L4
jmp .L6
.L5:
.L6:
.data
.L7: .string "hello"
.text
leaq .L7, %rbx
MOVQ %rbx, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL C
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ %rbx, %rdi
MOVQ %rbx, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL B
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ $3, %r10
movq $0, %rdx
MOVQ %rbx, %rax
IDIV %r10
MOVQ %rdx, %rbx
movq %rbx, %rax
jmp .L4
.L4: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
.text
.globl A
A:
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
MOVQ -16(%rbp), %r10
CMPQ %rbx, %r10
JE .L9
MOVQ $0, %r11
JMP .L10
.L9:
MOVQ $1, %r11
.L10:
movq %r11, %rax
jmp .L8
.L8: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
.text
.globl B
B:
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
MOVQ $33, %r10
CMPQ %rbx, %r10
JE .L12
MOVQ $0, %r11
JMP .L13
.L12:
MOVQ $1, %r11
.L13:
cmp $0, %r11
je .L14
MOVQ $10, %rbx
movq %rbx, %rax
jmp .L11
jmp .L15
.L14:
MOVQ $11, %rbx
movq %rbx, %rax
jmp .L11
.L15:
.L11: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
.text
.globl C
C:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
subq $0, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $33, %rbx
movq %rbx, %rax
jmp .L16
.L16: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
