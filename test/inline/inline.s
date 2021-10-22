	.file	"inline.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "not open inline\0"
	.text
	.p2align 4,,15
	.globl	doB
	.def	doB;	.scl	2;	.type	32;	.endef
	.seh_proc	doB
doB:
	.seh_endprologue
	leaq	.LC0(%rip), %rcx
	jmp	puts
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "open inline\0"
	.text
	.p2align 4,,15
	.globl	inline_test
	.def	inline_test;	.scl	2;	.type	32;	.endef
	.seh_proc	inline_test
inline_test:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	leaq	.LC1(%rip), %rcx
	call	puts
	leaq	.LC0(%rip), %rcx
	call	puts
	xorl	%eax, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	puts;	.scl	2;	.type	32;	.endef
