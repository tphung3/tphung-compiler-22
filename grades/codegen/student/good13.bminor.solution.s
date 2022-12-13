.text

.global main
main:
	pushq %rbp
	movq  %rsp, %rbp
	subq $24,%rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	movq $3,%rbx
	movq %rbx, -8(%rbp)
	movq $1,%rbx
	movq %rbx, -16(%rbp)
	movq -8(%rbp),%rbx
	movq $3,%r10
	add %rbx, %r10
	movq %r10, -24(%rbp)
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
