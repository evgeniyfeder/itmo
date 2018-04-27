	section .text
	global _arctan_simd

_arctan_simd:
	movss xmm0, [esp + 4]
	
	movss xmm1, xmm0
	
	movss xmm2, [MINUS_ONE]
	mulss xmm2, xmm1
	mulss xmm2, xmm1
	
	movss xmm3, [ONE]

	mov eax, [esp + 8]
	inc eax

	cmp eax, 0
	jz L2
	;[res, up, -x^2, down, tmp]
	;[up, down,0,0]
	;[-x^2, 2, res, 0]
L1: 
	addss xmm3, [TWO] 
	mulss xmm1, xmm2	 
	
	movss xmm4, xmm1 

	divss xmm4, xmm3	
	addss xmm0, xmm4	 
	
	DEC eax
	CMP eax, 0
	JNZ L1
L2:	
	movss [TRASH], xmm0
	FLD DWORD [TRASH]
	RET

	section .rdata
MINUS_ONE : dd -1.0
TWO : dd 2.0
ONE : dd 1.0
	
	section .data
TRASH: dd 1.1, 2.2, 3.3, 4.4