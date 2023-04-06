	.file	"smile.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"a+b\354\231\200 sum\354\235\230 \352\260\222\354\235\264 \352\260\231\354\212\265\353\213\210\353\213\244 ^3^"
	.align 8
.LC1:
	.string	"a+b\354\231\200 sum\354\235\230 \352\260\222\354\235\264 \353\213\244\353\246\205\353\213\210\353\213\244 OoO"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$85, -12(%rbp)
	movl	$15, -8(%rbp)
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	cmpl	%eax, -4(%rbp)
	je	.L2
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L3
.L2:
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L3:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
