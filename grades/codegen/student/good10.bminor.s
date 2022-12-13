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
MOVQ $3, %rbx
movq %rbx, -8(%rbp)
MOVQ $1, %rbx
movq %rbx, -16(%rbp)
MOVQ $1, %rbx
cmp $0, %rbx
je .L2
.data
.L4: .string "true"
.text
leaq .L4, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
jmp .L3
.L2:
.L3:
MOVQ $1, %rbx
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
