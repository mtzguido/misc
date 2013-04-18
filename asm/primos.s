.data
S:	.string "%i "

.text
	.globl main

main:
	pushl	%ebp
	movl 	%esp, %ebp
	subl	$4, %esp # aca va el arg en int

	movl	12(%ebp),%eax
	addl	$4, %eax
	pushl	(%eax)
	call	atoi
	movl	%eax, %edi
	addl	$4, %esp

	movl	$2, %ecx

loop:
	cmpl	%edi, %ecx
	jg	break
	
	pushl	%ecx
	pushl	%ecx
	call 	f
	addl	$4, %esp
	popl	%ecx
	
	cmp	$0, %eax
	je	noprint
	
	pushl	%ecx
	pushl	%ecx
	pushl	$S
	call printf
	addl	$8, %esp
	popl	%ecx
	
noprint:	
	incl	%ecx
	jmp	loop

break:	
	call	printf
	movl	%ebp, %esp
	popl	%ebp
	ret
	
f:
	pushl	%ebp
	movl	%esp, %ebp
	
	movl	$2, %ecx
	
loopf:
	cmpl	8(%ebp), %ecx
	jge	primo
	
	movl	8(%ebp), %eax
	xorl	%edx, %edx
	idivl	%ecx
	cmpl	$0, %edx
	je	noprimo
	
	incl	%ecx
	jmp	loopf

noprimo:
	movl	$0, %eax
	jmp sale
primo:	
	movl	$1, %eax
sale:
	movl	%ebp, %esp
	popl	%ebp
	ret
	
