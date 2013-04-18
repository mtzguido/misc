.data
S:	.string	"%s\n"

.text
	.globl main
main:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	$0, %ecx
	
loop:
	cmpl	%ecx, 8(%ebp)
	je	sale
	pushl	%ecx
	pushl	%edx
	pushl	(%edx)
	pushl	$S
	call	printf
	addl	$8, %esp
	popl	%edx
	popl	%ecx

	addl	$4, %edx
	incl	%ecx

	jmp loop

sale:
	movl	%ebp, %esp
	popl	%ebp
	ret
