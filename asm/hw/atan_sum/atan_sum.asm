	section .text
	global _arctan

_arctan:
	FLD DWORD [esp + 4]
	
	FLD st0
	FLD DWORD [MINUS_ONE]
	FMUL st0, st1
	FMUL st0, st1

	FLD1

	MOV eax, [esp + 8]
	INC eax

	CMP eax, 0
	jz L2
	;[1, -x^2, x, x]
L1: ; st0 - down, st1 - -x^2, st2 - up, st3 - res
	FADD DWORD [TWO] ; st0 - down + 2, st1 - -x^2, st2 - up, st3 - res
	

	FLD st2			 ; st0 - up, st1 - down + 2, st2 - -x^2, st3 - up, st4 - res
	 
	FMUL st0, st2	 ; st0 - up * (-x^2), st1 - down + 2, st2 - -x^2, st3 - up, st4 - res 
	FST st3			 ; st0 - up * (-x^2), st1 - down + 2, st2 - -x^2, st3 - up * (-x^2), st4 - res 

	FDIV st0, st1	 ; st0 - up * (-x^2) / (down + 2), st1 - down + 2, st2 - -x^2, st3 - up * (-x^2), st4 - res 
	FADD st4, st0	 ; st0 - up * (-x^2) / (down + 2), st1 - down + 2, st2 - -x^2, st3 - up * (-x^2), st4 - res + st0

	FSTp DWORD [TRASH]	; st0 - new_down, st1 - -x^2, st2 - new_up, st3 - new_res
	
	DEC eax
	CMP eax, 0
	JNZ L1
L2:	
	FSTP DWORD [TRASH]
	FSTP DWORD [TRASH]
	FSTP DWORD [TRASH]
	RET

	section .rdata
MINUS_ONE : dd -1.0
TWO : dd 2.0
	
	section .data
TRASH: dd 0.0