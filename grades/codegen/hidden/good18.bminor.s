.data
b1: .quad 3
.data
b2: .quad 6
.data
b3: .quad 9
.text
.globl B
B:
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
MOVQ b1, %rbx
MOVQ b2, %r10
MOVQ %rbx, %rax
IMUL %r10
MOVQ %rax, %rbx
MOVQ -8(%rbp), %r10
MOVQ -16(%rbp), %r11
movq $0, %rdx
MOVQ %r10, %rax
IDIV %r11
MOVQ %rdx, %r10
ADDQ %r10, %rbx
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
MOVQ $37, %rbx
MOVQ %rbx, -8(%rbp)
MOVQ -8(%rbp), %rbx
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
MOVQ $5, %rbx
MOVQ %rbx, %rdi
