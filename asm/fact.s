.data
Sin:	.string	"%i"
Sout:	.string	"%i\n"

.text
.globl main
main:
	pushl	%ebp
	movl	%esp, %ebp
	
	subl	$4, %esp

	pushl	%esp
	pushl	$Sin
	call	scanf
	addl	$8, %esp

	#ya esta en tope de la stack
	call	fact
	addl	$4, %esp

	pushl 	%eax
	pushl	$Sout
	call	printf
	addl	$8, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

fact:
	pushl	%ebp
	movl	%esp, %ebp

	cmpl	$0, 8(%ebp)
	jne	rec

	pushl	$Sin
	call	scanf
	addl	$4, %esp

	movl	$1, %eax
	jmp	salir
rec:
	movl	8(%ebp), %ecx
	decl	%ecx
	pushl	%ecx
	call fact
	addl	$4, %esp
	imull	8(%ebp)
	jmp	salir

salir:
	movl	%ebp, %esp
	popl	%ebp
	ret
