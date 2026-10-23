# gcc -O3 -S matrix.c (GCC 13.3), .cfi directives removed. Reference listing
# for matrix_optimized.jazz: other GCC versions may generate different code.
	.file	"matrix.c"
	.text
	.p2align 4
	.globl	multiply_matrices
	.type	multiply_matrices, @function
multiply_matrices:
.LFB23:
	endbr64
	testq	%rcx, %rcx
	je	.L12
	movq	%rdi, %r11
	leaq	0(,%rcx,8), %rdi
	pushq	%r13
	xorl	%r13d, %r13d
	pushq	%r12
	leaq	(%r11,%rdi), %r8
	movq	%rcx, %r12
	pushq	%rbp
	movq	%rsi, %rbp
	pushq	%rbx
	movq	%rdx, %rbx
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rbp, %r9
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L6:
	movq	%r9, %rcx
	movq	%r11, %rax
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L4:
	movq	(%rax), %rdx
	imulq	(%rcx), %rdx
	addq	$8, %rax
	addq	%rdi, %rcx
	addq	%rdx, %rsi
	cmpq	%rax, %r8
	jne	.L4
	leaq	1(%r10), %rax
	movq	%rsi, (%rbx,%r10,8)
	addq	$8, %r9
	cmpq	%rax, %r12
	je	.L5
	movq	%rax, %r10
	jmp	.L6
.L5:
	leaq	1(%r13), %rax
	addq	%rdi, %rbx
	addq	%rdi, %r11
	addq	%rdi, %r8
	cmpq	%r10, %r13
	je	.L1
	movq	%rax, %r13
	jmp	.L3
.L1:
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
.L12:
	ret
