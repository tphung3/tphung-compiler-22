.text
.globl strlen
strlen:
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
.data
.L4: .string "hi"
.text
leaq .L4, %rbx
MOVQ %rbx, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL strlen
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
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
.data
.L5: .string "there"
.text
leaq .L5, %r10
MOVQ %r10, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL strlen
POPQ %r11
POPQ %r10
MOVQ %rax, %r10
CMPQ %rbx, %r10
JL .L6
MOVQ $0, %r11
JMP .L7
.L6:
MOVQ $1, %r11
.L7:
cmp $0, %r11
je .L8
.data
.L10: .string "no\n"
.text
leaq .L10, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
jmp .L9
.L8:
.L9:
.data
.L11: .string "hi"
.text
leaq .L11, %rbx
MOVQ %rbx, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL strlen
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
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ %rbx, %rdi
MOVQ %rbx, %rsi
MOVQ %rbx, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
.data
.L12: .string "there"
.text
leaq .L12, %r10
MOVQ %r10, %rdi
MOVQ $1, %rsi
MOVQ $1, %rdx
MOVQ $1, %rcx
MOVQ $1, %r8
MOVQ $1, %r9
PUSHQ %r10
PUSHQ %r11
CALL strlen
POPQ %r11
POPQ %r10
MOVQ %rax, %r10
CMPQ %rbx, %r10
JL .L13
MOVQ $0, %r11
JMP .L14
.L13:
MOVQ $1, %r11
.L14:
cmp $0, %r11
je .L15
.data
.L17: .string "ok\n"
.text
leaq .L17, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
jmp .L16
.L15:
.L16:
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
MOVQ $2, %r10
MOVQ %rbx, %rax
IMUL %r10
MOVQ %rax, %rbx
movq %rbx, %rax
jmp .L18
.L18: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
