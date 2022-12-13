.data
s: .string "no\n"
.text
.globl f
f:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
MOVQ s, %rbx
movq %rbx, -8(%rbp)
.data
.L2: .string "ok\n"
.text
leaq .L2, %rbx
MOVQ %rbx, s
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
MOVQ $1, %rdi
MOVQ $1, %rsi
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
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
MOVQ s, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
MOVQ $0, %rbx
movq %rbx, %rax
jmp .L3
.L3: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
