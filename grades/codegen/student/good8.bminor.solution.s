.data

.global X
X:
	.quad 1
.text

.global main
main:
	pushq %rbp
	movq  %rsp, %rbp
	subq $40,%rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	movq $3,%rbx
	movq %rbx, -8(%rbp)
	movq $0,%rbx
	movq %rbx, -16(%rbp)
.data
.S0:	.string "hah"
.text
	leaq .S0,%rbx
	movq %rbx, -24(%rbp)
	movq -8(%rbp),%rbx
	movq $2,%r10
	add %rbx, %r10
	movq %r10, -32(%rbp)
	movq $0,%rbx
	movq %rbx, -40(%rbp)
	movq -40(%rbp),%rbx
	cmp $0, %rbx
	jz .L1
	movq $0,%rbx
	movq %rbx,%rax
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	movq %rbp, %rsp
	popq %rbp
	ret
	jmp .L2
.L1:
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
