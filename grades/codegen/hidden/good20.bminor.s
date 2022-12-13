.text
.globl D
D:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ $5, %rbx
movq %rbx, -8(%rbp)
MOVQ -8(%rbp), %rbx
MOVQ $1, %r10
ADDQ %r10, %rbx
movq %rbx, -16(%rbp)
MOVQ $9, %rbx
movq %rbx, -24(%rbp)
MOVQ -24(%rbp), %rbx
MOVQ -8(%rbp), %r10
MOVQ $3, %r11
SUBQ %r11, %r10
ADDQ %r10, %rbx
movq %rbx, -32(%rbp)
MOVQ $1, %rbx
MOVQ $0, %r10
SUBQ %rbx, %r10
movq %r10, -40(%rbp)
MOVQ -32(%rbp), %rbx
MOVQ -24(%rbp), %r10
ADDQ %r10, %rbx
MOVQ %rbx, -32(%rbp)
MOVQ -32(%rbp), %rbx
MOVQ -40(%rbp), %r10
SUBQ %r10, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_integer
popq %r11
popq %r10
.data
.L2: .string "\n"
.text
leaq .L2, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
MOVQ $16, %rbx
movq %rbx, -48(%rbp)
MOVQ -16(%rbp), %rbx
MOVQ -48(%rbp), %r10
SUBQ %r10, %rbx
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
MOVQ $2, %rbx
MOVQ $0, %r10
SUBQ %rbx, %r10
movq %r10, -56(%rbp)
MOVQ $1000, %rbx
movq %rbx, -64(%rbp)
MOVQ -64(%rbp), %rbx
MOVQ $10, %r10
ADDQ %r10, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_integer
popq %r11
popq %r10
.data
.L3: .string "\n"
.text
leaq .L3, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
MOVQ -56(%rbp), %rbx
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
MOVQ -48(%rbp), %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_integer
popq %r11
popq %r10
MOVQ $3, %rbx
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
CALL D
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
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
