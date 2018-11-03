	section .text
	global _print

;;;;;;;;;;;;;;;;;;;;;;;;;; operations with numbers

; small in eax
; result in [number]
_big_add_small:
	push ebx
	xor ebx, ebx
	add [number], eax
	adc [number + 4], ebx
	adc [number + 8], ebx
	adc [number + 12], ebx
	pop ebx
	ret

; small in eax
; result in [number]
_big_minus_small:
	not eax
	add eax, 1
	call _big_add_small
	ret

; small in eax
; result in [number], result in 128 bit
_big_mul_small:
	push esi
	mov esi, eax
	xor ecx, ecx
	xor ebx, ebx
	_big_mul_small_l1:
		mov eax, esi
		mul dword[number + ecx]
		add eax, ebx
		adc edx, 0
		mov ebx, edx
		mov [number + ecx], eax

		add ecx, 4
		cmp ecx, 16
		jne _big_mul_small_l1
	_big_mul_small_l1_end:
	pop esi
	ret

; small in ebx
; result in [number]
_big_div_small:
	push esi
	mov esi, 16
	xor ecx, ecx
	xor edx, edx

	_big_div_small_l1:
		sub esi, 4

		mov eax, [number + esi]
		div ebx
		mov [number + esi], eax

		cmp esi, 0
		jnz _big_div_small_l1
	_big_div_small_l1_end:
	pop esi
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;; read format
; esi - pointer to number
; result in edx
_read_number_format:
	;edx - tmp number
	xor edx, edx
	
	xor eax, eax
	mov al, [esi]
	cmp al, 0
	jz _read_number_format_l1_end

	_read_number_format_l1:
		;esi - cur digit
		sub al, '0'
		lea edx, [edx * 5]
		lea edx, [eax + edx * 2]
		
		inc esi
		mov al, [esi]
		cmp al, 0
		jnz _read_number_format_l1
	_read_number_format_l1_end:
		
		ret

;esi - pointer to string
_read_format:
	push edi
	push esi
	
	mov al, [esi]
	mov edx, [flags]
	cmp al, 0
	jz _read_format_no_number
	
	_read_format_l1:
		_read_format_check_minus:
		cmp al, '-'
		jne _read_format_check_plus
		or edx, [MINUS_MASK]
		and edx, [NOT_ZERO_MASK]
		jmp _read_format_switch_end

		_read_format_check_plus:
		cmp al, '+'
		jne _read_format_check_space
		or edx, [PLUS_MASK]
		and edx, [NOT_SPACE_MASK]
		jmp _read_format_switch_end

		_read_format_check_space:
		cmp al, ' '
		jne _read_format_check_zero
		mov ebx, [PLUS_MASK]
		and ebx, edx
		jnz _read_format_switch_end
		or edx, [SPACE_MASK]
		jmp _read_format_switch_end

		_read_format_check_zero:
		cmp al, '0'
		jne _read_format_l1_number
		mov ebx, [MINUS_MASK]
		and ebx, edx
		jnz _read_format_switch_end
		or edx, [ZERO_MASK]

		_read_format_switch_end:
		inc esi
		mov al, [esi]
		cmp al, 0
		jnz _read_format_l1
		mov [flags], edx
		jmp _read_format_no_number
		
	_read_format_l1_number:
	mov [flags], edx
	call _read_number_format
	mov [min_size_format], edx

	_read_format_no_number:
	pop esi
	pop edi
	ret


; parse number from input
; esi - pointer to number
_read_number:
	push esi
	xor eax, eax
	mov al, [esi]
	cmp al, '-'
	jne _negative_ends
	_negative_l1:
		mov ebx, [NEG_MASK]
		xor ebx, [flags]
		mov [flags], ebx
		
		inc esi
		mov al, [esi]
		cmp al, '-'
		je _negative_l1
	_negative_ends:
	mov al, [esi]
	test al, al
	jz _read_number_l1_end
	_read_number_l1:
		; big = big * 10
		mov ecx, eax
		mov eax, 16
		push ebx
		push ecx
		call _big_mul_small
		pop ecx
		pop ebx
		mov eax, ecx
		
		; if number
		cmp eax, '0'
		jl _big_letter_case
		cmp eax, '9'
		jg _big_letter_case

		sub eax, '0'
		push ebx
		call _big_add_small
		pop ebx
		jmp _letter_case_end

		_big_letter_case:
		cmp eax, 'A'
		jl _small_letter_case
		cmp eax, 'Z'
		jg _small_letter_case

		sub eax, 'A'
		add eax, 10
		push ebx
		call _big_add_small
		pop ebx
		jmp _letter_case_end

		_small_letter_case:
		sub eax, 'a'
		add eax, 10
		push ebx
		call _big_add_small
		pop ebx
		_letter_case_end:

		inc esi
		mov al, [esi]
		test al, al
		jnz _read_number_l1
	_read_number_l1_end:
	mov ebx, [flags]
	and ebx, [NEG_MASK]
	jz _if_not_minus

	mov eax, [number + 0]
	xor eax, ~0
	mov [number + 0], eax

	mov eax, [number + 4]
	xor eax, ~0
	mov [number + 4], eax

	mov eax, [number + 12]
	xor eax, ~0
	mov [number + 12], eax

	mov eax, [number + 8]
	xor eax, ~0
	mov [number + 8], eax

	mov eax, 1
	call _big_add_small
	_if_not_minus:
	mov eax, 0x80000000
	mov ebx, [number + 12]
	and eax, ebx
	jz _read_number_if_pos_number
	
	mov eax, [NEG_MASK]
	or [flags], eax

	mov eax, [number + 0]
	xor eax, ~0
	mov [number + 0], eax

	mov eax, [number + 4]
	xor eax, ~0
	mov [number + 4], eax

	mov eax, [number + 12]
	xor eax, ~0
	mov [number + 12], eax

	mov eax, [number + 8]
	xor eax, ~0
	mov [number + 8], eax

	mov eax, 1
	call _big_add_small
	jmp _read_number_end

	_read_number_if_pos_number:
	mov eax, [NOT_NEG_MASK]
	and [flags], eax

	_read_number_end:
	pop esi
	ret

; check [number] for zero
; res in esi
_check_zero:
	push eax

	mov eax, [number]
	test eax, eax
	jnz _return_1

	mov eax, [number + 4]
	test eax, eax
	jnz _return_1

	mov eax, [number + 8]
	test eax, eax
	jnz _return_1

	mov eax, [number + 12]
	test eax, eax
	jnz _return_1

	mov esi, 0
	pop eax
	ret
	_return_1:
	mov esi, 1
	pop eax
	ret
; print unformated string
; len in ecx
_print_unformated:
	push esi

	; esi - check zero
	mov ecx, 0
	call _check_zero
	test esi, esi
	jnz _print_unformated_l1
	mov edx, '0'
	mov [tmp_str], edx
	xor edx, edx
	mov [tmp_str + 1], edx

	pop esi
	ret

	_print_unformated_l1:
		mov ebx, 10
		push ecx
		call _big_div_small
		pop ecx
		; edx - remainder
		add edx, '0'
		mov [tmp_str + ecx], dl

		inc ecx
		call _check_zero
		cmp esi, 0
		jnz _print_unformated_l1
	_print_unformated_l1_end:
	xor edx, edx
	mov [tmp_str + ecx], edx
	dec ecx
	mov [str_len], ecx
	
	pop esi
	ret

; esi - pointer to string
; ecx - size of string
_print_formated:
	push esi
	push edi
	mov edx, [flags]
	mov edi, esi
	
	_check_minus:
	mov ebx, [MINUS_MASK]
	and ebx, edx
	jz _right_alligned

	_left_alligned:
	mov ebx, [NEG_MASK]
	and ebx, edx
	jz _left_alligned_positive

	mov al, '-'
	mov [esi], al
	inc esi
	jmp _left_alligned_format_end

	_left_alligned_positive:
	mov ebx, [PLUS_MASK]
	and ebx, edx
	jz _left_alligned_check_space

	mov ebx, '+'
	mov [esi], bl
	inc esi
	jmp _left_alligned_format_end

	_left_alligned_check_space:
	mov ebx, [SPACE_MASK]
	and ebx, edx
	jz _left_alligned_format_end

	mov ebx, ' '
	mov [esi], bl
	inc esi
	_left_alligned_format_end:

	cmp ecx, -1
	je _left_alligned_l1_end

	_left_alligned_l1:
		mov al, [tmp_str + ecx]
		mov [esi], al
		inc esi
		
		dec ecx
		cmp ecx, -1
		jne _left_alligned_l1
	_left_alligned_l1_end:
	mov eax, esi
	sub esi, edi
	mov edi, esi
	mov esi, eax

	cmp edi, [min_size_format]
	jge _end
	_space_insert_after:
		mov al, ' '
		mov [esi], al
		inc esi
		
		inc edi
		cmp edi, [min_size_format]
		jl _space_insert_after
		jmp _end
	
	_right_alligned:
	mov edx, [flags]
	mov ebx, [ZERO_MASK]
	and ebx, edx
	jz _right_alligned_not_zero_flag
	
	mov ebx, [NEG_MASK]
	and ebx, edx
	jz _right_alligned_positive

	mov al, '-'
	mov [esi], al
	inc esi
	jmp _right_alligned_not_zero_flag

	_right_alligned_positive:
	mov ebx, [PLUS_MASK]
	and ebx, edx
	jz _right_alligned_check_space

	mov ebx, '+'
	mov [esi], bl
	inc esi
	jmp _right_alligned_not_zero_flag

	_right_alligned_check_space:
	mov ebx, [SPACE_MASK]
	and ebx, edx
	jz _right_alligned_not_zero_flag

	mov ebx, ' '
	mov [esi], bl
	inc esi
	_right_alligned_not_zero_flag:

	mov eax, esi
	sub esi, edi
	mov edi, esi
	mov esi, eax
	add edi, [str_len]
	inc edi

	mov edx, [flags]
	mov ebx, [ZERO_MASK]
	and ebx, edx
	jnz _right_alligned_not_zero_with_not_prefix
	mov ebx, [NEG_MASK]
	and ebx, edx
	jnz _right_alligned_not_zero_with_prefix
	mov ebx, [PLUS_MASK]
	and ebx, edx
	jnz _right_alligned_not_zero_with_prefix
	mov ebx, [SPACE_MASK]
	and ebx, edx
	jnz _right_alligned_not_zero_with_prefix
	jmp _right_alligned_not_zero_with_not_prefix

	_right_alligned_not_zero_with_prefix:
	inc edi
	_right_alligned_not_zero_with_not_prefix:
	cmp edi, [min_size_format]
	jge _print_right

	_space_insert_before:
		mov edx, [flags]
		mov ebx, [ZERO_MASK]
		and ebx, edx
		jz _insert_space
		mov al, '0'
		jmp _insert_end

		_insert_space:
		mov al, ' '

		_insert_end:
		mov [esi], al
		inc esi
		
		inc edi
		cmp edi, [min_size_format]
		jne _space_insert_before
	
	_print_right:

	mov edx, [flags]
	mov ebx, [ZERO_MASK]
	and ebx, edx
	jnz _right_alligned_not_zero_after_spaces

	mov ebx, [NEG_MASK]
	and ebx, edx
	jz _right_alligned_not_zero_after_spaces_positive

	mov al, '-'
	mov [esi], al
	inc esi
	jmp _right_alligned_not_zero_after_spaces

	_right_alligned_not_zero_after_spaces_positive:
	mov ebx, [PLUS_MASK]
	and ebx, edx
	jz _right_alligned_not_zero_after_spaces_check_space

	mov ebx, '+'
	mov [esi], bl
	inc esi
	jmp _right_alligned_not_zero_after_spaces

	_right_alligned_not_zero_after_spaces_check_space:
	mov ebx, [SPACE_MASK]
	and ebx, edx
	jz _right_alligned_not_zero_after_spaces

	mov ebx, ' '
	mov [esi], bl
	inc esi

	_right_alligned_not_zero_after_spaces:
	cmp ecx, -1
	jz _end

	_print_right_l1:
		mov al, [tmp_str + ecx]
		mov [esi], al
		inc esi
		
		dec ecx
		cmp ecx, -1
		jnz _print_right_l1
	_end:
	xor eax, eax
	mov [esi], al
	pop edi
	pop esi
	ret

; set formated string 
; calling convention - cdecl(stack, reverse)
_print:
	push ebx
	push ebp
	push esi
	push edi

	xor eax, eax
	mov [flags], eax
	mov [min_size_format], eax
	mov [str_len], eax
	mov [number + 0], eax
	mov [number + 4], eax
	mov [number + 8], eax
	mov [number + 12], eax
	
	mov esi, [esp + 16 + 8]
	call _read_format
	mov esi, [esp + 16 + 12]
	call _read_number
	call _print_unformated
	; ecx - str size
	mov esi, [esp + 16 + 4]
	call _print_formated
	
	pop edi
	pop esi
	pop ebp
	pop ebx
	ret

	section .data
number: dd 0, 0, 0, 0
tmp_str: times 64 db 0
flags: dd 0
min_size_format: dd 0
str_len: dd 0
	section .rdata
MINUS_MASK: dd 1
PLUS_MASK: dd 2
SPACE_MASK: dd 4
ZERO_MASK: dd 8
NEG_MASK: dd 16

NOT_MINUS_MASK: dd ~1
NOT_PLUS_MASK: dd ~2
NOT_SPACE_MASK: dd ~4
NOT_ZERO_MASK: dd ~8
NOT_NEG_MASK: dd ~16