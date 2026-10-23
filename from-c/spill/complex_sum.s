# Reference listing for the exercise in complex_sum.jazz: register_pressure
# compiled by GCC 10.5 with -O3. It is not built by the Makefile, and must not be
# linked: it does not save the callee-saved registers (rbx, rbp, r12-r15).
	.file	"complex_sum.c"
	.text
	.p2align 4
	.globl	register_pressure
	.type	register_pressure, @function
register_pressure:
.LFB23:
	endbr64
	leaq	1(%r9), %rax
	leaq	0(,%rdi,8), %r11
	leaq	(%rsi,%rsi,2), %r14
	leaq	11(%rdx), %rsi
	subq	%rdi, %r11
	leaq	(%r8,%r8,8), %rdx
	leaq	-2(%rcx), %rdi
	movq	%rsi, %r9
	movq	%rdx, %r10
	leaq	(%r11,%r14), %r15
	subq	%rdi, %r9
	imulq	%rax, %r10
	leaq	(%r9,%r9,2), %r12
	movq	%r9, %rbp
	leaq	(%r15,%r15), %rbx
	leaq	(%rbx,%r12), %r8
	imulq	%r8, %r14
	leaq	-4(%r10), %r13
	movq	%r13, %rcx
	movq	%rsi, -72(%rsp)
	subq	%r11, %rcx
	movq	%rsi, %r11
	movq	%rdi, %rsi
	movq	%rdx, -8(%rsp)
	imulq	%rcx, %r11
	movq	%rcx, -112(%rsp)
	movq	%rdx, %rcx
	addq	%r14, %rsi
	movq	%r14, -120(%rsp)
	movq	%r15, %rdx
	subq	%rax, %rdx
	movq	%rdi, -64(%rsp)
	subq	%r11, %rcx
	movq	%r8, -56(%rsp)
	movq	%rcx, %r14
	movq	%rcx, -104(%rsp)
	imulq	%rsi, %r14
	subq	%r14, %rdx
	movq	%r14, -96(%rsp)
	imulq	%rdx, %rbp
	movq	%rdx, %r14
	movq	%r12, %rdx
	leaq	(%r10,%rbp), %rdi
	movq	%rbp, -48(%rsp)
	movq	%r8, %rbp
	movq	-120(%rsp), %r8
	movq	%rdi, -40(%rsp)
	imulq	%rbx, %rdi
	addq	%r11, %r8
	movq	%r8, -80(%rsp)
	movq	-80(%rsp), %r8
	subq	%rdi, %rdx
	movq	%rdi, %rcx
	movq	-112(%rsp), %rdi
	movq	%rdx, -32(%rsp)
	addq	%r13, %rdx
	imulq	%rdx, %rbp
	imulq	%rbp, %rdi
	movq	%rbp, -24(%rsp)
	movq	-104(%rsp), %rbp
	subq	%rdi, %r8
	movq	%rax, %rdi
	addq	-8(%rsp), %rax
	addq	-64(%rsp), %rax
	imulq	%rsi, %r8
	addq	%r10, %rax
	addq	-72(%rsp), %rax
	addq	%r13, %rax
	addq	%r9, %rax
	imulq	%r8, %rbp
	leaq	(%rax,%r12,2), %rax
	subq	%rbp, %rdi
	movq	%rbp, -88(%rsp)
	imulq	%rdi, %r14
	movq	%rdi, %rbp
	movq	%r10, %rdi
	subq	%r14, %rdi
	imulq	%rdi, %rcx
	movq	%rdi, -16(%rsp)
	movq	-32(%rsp), %rdi
	addq	%rcx, %rdi
	addq	-112(%rsp), %rax
	addq	%rbx, %rax
	addq	%r11, %rax
	addq	-56(%rsp), %rax
	addq	-104(%rsp), %rax
	addq	%rsi, %rax
	addq	-80(%rsp), %rax
	movq	-24(%rsp), %rbx
	addq	-40(%rsp), %rax
	leaq	(%r15,%rbx), %rsi
	addq	%rdx, %rax
	imulq	%rdi, %rdx
	leaq	(%rsi,%rsi,2), %r15
	addq	%r15, %rax
	addq	%rax, %r8
	movq	-96(%rsp), %rax
	addq	-120(%rsp), %rax
	addq	%rbp, %r8
	addq	-16(%rsp), %r8
	addq	-48(%rsp), %rax
	addq	%r8, %rcx
	addq	-88(%rsp), %rax
	addq	%r14, %rax
	addq	%rdi, %rcx
	leaq	(%rcx,%rax,2), %rax
	subq	%rdx, %rax
	ret
.LFE23:
	.size	register_pressure, .-register_pressure
	.ident	"GCC: (Ubuntu 10.5.0-4ubuntu2) 10.5.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
