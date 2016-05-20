.section .rodata

.data
.globl global
.align 4
global: 
	.long 1

.text
.globl main
.globl aritmeticaBasica
.globl operacionX
.globl unarios
.globl iterativas
.globl selectivas

main:
	pushq	%rbp
	movq	%rsp,	%rbp
	subq	$16,	%rsp
	call	aritmeticaBasica

	pushq	%r10
	
        pushq	%r10
	movl 	$2,	%eax
	movl	%eax,	%r10d
	pushq	%r11
	movl 	$1,	%eax
	movl	%eax,	%r11d
	movl	%r11d,	%edi
	movl	%r10d,	%esi
	call	operacionX
	popq	%r11
	popq	%r10
	
        movl	%eax,	%r10d
	pushq	%r11
	
        pushq	%r10
	movl 	$6,	%eax
	movl	%eax,	%r10d
	pushq	%r11
	movl 	$5,	%eax
	movl	%eax,	%r11d
	movl	%r11d,	%edi
	movl	%r10d,	%esi
	call	operacionX
	popq	%r11
	popq	%r10
	
        movl	%eax,	%r11d
	movl	%r11d,	%edi
	movl	%r10d,	%esi
	call	operacionX
	popq	%r11
	popq	%r10
	movl	%eax,	-4(%rbp)
	call	unarios
	call	iterativas
	movl 	$0,	%eax
	jmp	retorno_main
retorno_main:
	movq	%rbp,	%rsp
	popq	%rbp
	ret

aritmeticaBasica:
	pushq	%rbp
	movq	%rsp,	%rbp
	subq	$32,	%rsp
	movl 	$1,	%eax
	movl	%eax,	-4(%rbp)
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$2,	%eax
	addl	%eax,	%ebx
	movl	%ebx,	%eax
	popq	%rbx
	movl	%eax,	-8(%rbp)
	pushq	%rbx
	movl	-8(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$1,	%eax
	subl	%eax,	%ebx
	movl	%ebx,	%eax
	popq	%rbx
	movl	%eax,	-12(%rbp)
	pushq	%rbx
	movl	-12(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$2,	%eax
	xchgl	 %eax,	 %ebx
	imul	%ebx
	popq	%rbx
	movl	%eax,	-16(%rbp)
	pushq	%rbx
	movl	-16(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$1,	%eax
	xchgl	 %eax,	 %ebx
	xor	%rdx,	%rdx
	idiv	%ebx
	popq	%rbx
	movl	%eax,	-20(%rbp)
	pushq	%rbx
	movl	-20(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$2,	%eax
	xchgl	 %eax,	 %ebx
	xor	%rdx,	%rdx
	idiv	%ebx
	movl	%edx,	%eax
	popq	%rbx
	movl	%eax,	-24(%rbp)
	movl 	$0,	%eax
	movl	%eax,	-16(%rbp)
	movl	%eax,	-12(%rbp)
	movl	%eax,	-8(%rbp)
	movl	%eax,	-4(%rbp)
	movl	%eax,	-28(%rbp)
retorno_aritmeticaBasica:
	movq	%rbp,	%rsp
	popq	%rbp
	ret

operacionX:
	pushq	%rbp
	movq	%rsp,	%rbp
	subq	$16,	%rsp
	movl	%edi,	-4(%rbp)
	movl	%esi,	-8(%rbp)
	pushq	%rbx
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl	-8(%rbp),	%eax
	xchgl	 %eax,	 %ebx
	xor	%rdx,	%rdx
	idiv	%ebx
	movl	%edx,	%eax
	popq	%rbx
	movl	%eax,	%ebx
	pushq	%rbx
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl	-8(%rbp),	%eax
	addl	%eax,	%ebx
	movl	%ebx,	%eax
	popq	%rbx
	movl	%eax,	%ebx
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl	-8(%rbp),	%eax
	subl	%eax,	%ebx
	movl	%ebx,	%eax
	popq	%rbx
	xchgl	 %eax,	 %ebx
	xor	%rdx,	%rdx
	idiv	%ebx
	popq	%rbx
	xchgl	 %eax,	 %ebx
	imul	%ebx
	popq	%rbx
	movl	%eax,	-12(%rbp)
	movl	-12(%rbp),	%eax
	jmp	retorno_operacionX
retorno_operacionX:
	movq	%rbp,	%rsp
	popq	%rbp
	ret

unarios:
	pushq	%rbp
	movq	%rsp,	%rbp
	subq	$48,	%rsp
	movl 	$1,	%eax
	movl	%eax,	-4(%rbp)
	movl 	$1,	%eax
	neg	%eax
	movl	%eax,	-8(%rbp)
	movl 	$1,	%eax
	neg	%eax
	sbb	%eax,	%eax
	add	$1,	%eax
	movl	%eax,	-12(%rbp)
	movl 	$0,	%eax
	neg	%eax
	sbb	%eax,	%eax
	add	$1,	%eax
	movl	%eax,	-16(%rbp)
	movl	-4(%rbp),	%r10d
	addl	$1,	%r10d
	movl	%r10d,	-4(%rbp)
	movl	%r10d,	%eax
	movl	%eax,	-20(%rbp)
	movl	-4(%rbp),	%r10d
	subl	$1,	%r10d
	movl	%r10d,	-4(%rbp)
	movl	%r10d,	%eax
	movl	%eax,	-24(%rbp)
	movl	-4(%rbp),	%r10d
	movl	%r10d,	%eax
	addl	$1,	%r10d
	movl	%r10d,	-4(%rbp)
	movl	%eax,	-28(%rbp)
	movl	-4(%rbp),	%r10d
	movl	%r10d,	%eax
	subl	$1,	%r10d
	movl	%r10d,	-4(%rbp)
	movl	%eax,	-32(%rbp)
	movl	-4(%rbp),	%eax
	movl	%eax,	-36(%rbp)
retorno_unarios:
	movq	%rbp,	%rsp
	popq	%rbp
	ret

iterativas:
	pushq	%rbp
	movq	%rsp,	%rbp
	subq	$16,	%rsp
	movl 	$0,	%eax
	movl	%eax,	-4(%rbp)
FOR_1: 
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$10,	%eax
	cmpl	%eax,	%ebx
	jge	FALSO_1
	movl	$1,	%eax
	jmp	FIN_1
FALSO_1: 
	movl	$0,	%eax
FIN_1: 
	popq	%rbx
	cmpl	$1,	%eax
	jl	FIN_FOR_1
	movl	-4(%rbp),	%eax
	movl	%eax,	-8(%rbp)
	movl	-4(%rbp),	%r10d
	movl	%r10d,	%eax
	addl	$1,	%r10d
	movl	%r10d,	-4(%rbp)
	jmp	FOR_1
FIN_FOR_1: 
WHILE_1: 
	movl 	$1,	%eax
	cmpl	$1,	%eax
	jl	FIN_WHILE_1
IF_1: 
	pushq	%rbx
	movl	-8(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$0,	%eax
	cmpl	%eax,	%ebx
	jne	FALSO_2
	movl	$1,	%eax
	jmp	FIN_2
FALSO_2: 
	movl	$0,	%eax
FIN_2: 
	popq	%rbx
	cmpl	$1,	%eax
	jl	FIN_IF_1
	jmp	FIN_WHILE_1
FIN_IF_1: 
	movl	-8(%rbp),	%r10d
	movl	%r10d,	%eax
	subl	$1,	%r10d
	movl	%r10d,	-8(%rbp)
	jmp	WHILE_1
FIN_WHILE_1: 
DO_WHILE_1: 
	movl	-4(%rbp),	%r10d
	movl	%r10d,	%eax
	subl	$1,	%r10d
	movl	%r10d,	-4(%rbp)
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$0,	%eax
	cmpl	%eax,	%ebx
	jle	FALSO_3
	movl	$1,	%eax
	jmp	FIN_3
FALSO_3: 
	movl	$0,	%eax
FIN_3: 
	popq	%rbx
	cmpl	$1,	%eax
	jl	FIN_DO_WHILE_1
	jmp	DO_WHILE_1
FIN_DO_WHILE_1: 
retorno_iterativas:
	movq	%rbp,	%rsp
	popq	%rbp
	ret

selectivas:
	pushq	%rbp
	movq	%rsp,	%rbp
	subq	$16,	%rsp
IF_2: 
	pushq	%rbx
	movl	global(%rip),	%eax
	movl	%eax,	%ebx
	movl 	$0,	%eax
	cmpl	%eax,	%ebx
	jle	FALSO_4
	movl	$1,	%eax
	jmp	FIN_4
FALSO_4: 
	movl	$0,	%eax
FIN_4: 
	popq	%rbx
	cmpl	$1,	%eax
	jl	ELSE_2
	movl 	$20,	%eax
	movl	%eax,	-4(%rbp)
	jmp	FIN_IF_2
ELSE_2: 
	movl 	$20,	%eax
	neg	%eax
	movl	%eax,	-4(%rbp)
FIN_IF_2: 
IF_3: 
	pushq	%rbx
	pushq	%rbx
	movl	-4(%rbp),	%eax
	movl	%eax,	%ebx
	movl 	$20,	%eax
	cmpl	%eax,	%ebx
	jne	FALSO_6
	movl	$1,	%eax
	jmp	FIN_6
FALSO_6: 
	movl	$0,	%eax
FIN_6: 
	popq	%rbx
	cmpl	$1,	%eax
	jl	FIN_AND_5
	pushq	%rbx
	movl	global(%rip),	%eax
	movl	%eax,	%ebx
	movl 	$0,	%eax
	cmpl	%eax,	%ebx
	jl	FALSO_7
	movl	$1,	%eax
	jmp	FIN_7
FALSO_7: 
	movl	$0,	%eax
FIN_7: 
	popq	%rbx
FIN_AND_5: 
	popq	%rbx
	cmpl	$1,	%eax
	jl	FIN_IF_3
	movl 	$0,	%eax
	movl	%eax,	-4(%rbp)
	movl	%eax,	global(%rip)
FIN_IF_3: 
retorno_selectivas:
	movq	%rbp,	%rsp
	popq	%rbp
	ret