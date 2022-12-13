.data
w: .string "no"
.text
.globl f
f:
pushq %rbp
movq %rsp, %rbp
pushq %rdi
subq $8, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
.data
.L2: .string "ok"
.text
leaq .L2, %rbx
movq %rbx, -16(%rbp)
MOVQ -16(%rbp), %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
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
.data
.L4: .string "bad!\n"
.text
leaq .L4, %rbx
MOVQ %rbx, -16(%rbp)
MOVQ -8(%rbp), %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
MOVQ $32, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_character
popq %r11
popq %r10
MOVQ w, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
.data
.L5: .string " "
.text
leaq .L5, %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
.data
.L6: .string "changed\n"
.text
leaq .L6, %rbx
MOVQ %rbx, -8(%rbp)
MOVQ -8(%rbp), %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
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
subq $8, %rsp
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
.data
.L8: .string "good"
.text
leaq .L8, %rbx
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
CALL f
POPQ %r11
POPQ %r10
MOVQ %rax, %rbx
MOVQ -8(%rbp), %rbx
movq %rbx, %rdi
pushq %r10
pushq %r11
call print_string
popq %r11
popq %r10
MOVQ $0, %rbx
movq %rbx, %rax
jmp .L7
.L7: 
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp
popq %rbp
ret
