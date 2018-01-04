	.file	"fact.c"
	.text
	.globl	factorial
	.type	factorial, @function
factorial:
	movl	$1, %eax
	movl	$0, %edx
	jmp	.L2
.L3:
	imull	%edx, %eax
	addl	$1, %edx
.L2:
	cmpl	%edi, %edx
	jle	.L3
	rep ret
	.size	factorial, .-factorial
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"factorial(%d) = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
	subq	$8, %rsp
	movl	$5, %edi
	call	factorial
	movl	%eax, %edx
	movl	$5, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$8, %rsp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
