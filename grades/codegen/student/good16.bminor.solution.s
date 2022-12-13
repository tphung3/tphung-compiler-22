.text

.global main
main:
	pushq %rbp
	movq  %rsp, %rbp
	subq $16,%rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	movq $3,%rbx
	movq %rbx, -8(%rbp)
	movq $1,%rbx
	movq %rbx, -16(%rbp)
	movq -16(%rbp),%rbx
	cmp $0, %rbx
	jz .L1
	movq -16(%rbp),%rbx
	pushq %r10
	pushq %r11
	mov %rbx, %rdi
	call print_boolean
	popq %r11
	popq %r10
	jmp .L2
.L1:
	movq -8(%rbp),%rbx
	pushq %r10
	pushq %r11
	mov %rbx, %rdi
	call print_integer
	popq %r11
	popq %r10
.L2:
	movq $1,%rbx
	movq %rbx,%rax
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	movq %rbp, %rsp
	popq %rbp
	ret
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	movq  %rbp, %rsp
	popq %rbp
	ret
