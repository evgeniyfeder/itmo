    section         .text

    global          _start
_start:

    sub             rsp, 2 * 128 * 8
    lea             rdi, [rsp + 128 * 8]
    mov             rcx, 128
    call            read_long
    mov             rdi, rsp
    call            read_long
    lea             rsi, [rsp + 128 * 8]
    call            mul_long_long
	
    call            write_long

    mov             al, 0x0a
    call            write_char

    jmp             exit

; multiplicate two long number
;    rdi -- address of number #1 (long number)
;    rsi -- address of number #2 (long number)
;    rcx -- length of long numbers in qwords
; result:
;    mul is written to rax
mul_long_long:
        push rdi
        push rsi
        push rcx
	push rdx
	push rbx
	push r8
	push r10
	push r11
	push r12
        push rax
	
	sub rsp, 2 * 256 * 8

        mov r14, rdi
        mov rdi, rsp
        mov r15, rcx
        mov rcx, 256
        call set_zero
        mov rcx, r15
        mov rdi, r14

        lea r10, [rsp + 256 * 0] ;r10 -> temporary
        lea r9, [rsp + 256 * 8] ;r9 -> result

	mov r12, rcx ; r12 - iter_size
	call create_temp ;rdi -> r10

	; swap rdi and r10
	mov r11, rdi
	mov rdi, r10
	mov r10, r11 ; rdi - temp, r10 - first number

    clc
.loop:
        mov rbx, [rsi]
	call mul_long_short ;rdi <- rdi * [rsi]

        mov r8, rcx
        mov rdx, rcx
        sub rdx, r12
        add rcx, rdx

        cmp rdx, 0
        je .if_rdx_zero

        .loop_mov:
                mov rbx, 1
                shl rbx, 63
                call mul_long_short

                mov rbx, 2
                call mul_long_short

                dec rdx
                jnz .loop_mov

.if_rdx_zero:
	mov rdx, rsi
	mov rsi, r9
	call add_long_long 
	mov rsi, rdx
	mov rcx, r8

	add rsi, 8
	call get_temp ;rdi <- r10
	dec r12
    jnz .loop

        ; swap rdi and r10
        mov r11, rdi
        mov rdi, r10
        mov r10, r11 ; rdi - first number, r10 - tmp
        mov r10, r9 ; r10 - result
        call get_temp

        add rsp, 2 * 256 * 8

    pop rax
    pop r12
    pop r11
    pop r10
    pop r8
    pop rbx
    pop rdx
    pop rcx
    pop rsi
    pop rdi
    ret

; move to r10 temporary number function
; 	r10 - adress of number;
; 	rcx - size
; result:
; 	rdi - result;
get_temp:
	push rdi
	push rcx
	push r10
	push r11
	
.loop:
	mov r11, [r10]
	mov [rdi], r11
	add rdi, 8
	add r10, 8
	
	dec rcx
    jnz .loop
	
	pop r11
	pop r10
        pop rcx
        pop rdi
        ret
	
; move to r10 temporary number function
; 	rdi - adress of number
; 	rcx - size
;   r10 - adress to result
; result:
; 	r10 - result;
create_temp:
	push rdi
	push rcx
	push r10
	push r11
	
.loop:
        mov r11, [rdi]
        mov [r10], r11
	add rdi, 8
	add r10, 8
	
	dec rcx
    jnz .loop
	
	pop r11
	pop r10
        pop rcx
        pop rdi
        ret

; adds two long number
;    rdi -- address of summand #1 (long number)
;    rsi -- address of summand #2 (long number)
;    rcx -- length of long numbers in qwords
; result:
;    sum is written to rdi
add_long_long:
                push            rdi
                push            rsi
                push            rcx
		push			r10
		push			rax
				
		mov 			r10, rdi
		mov 			rdi, rsi
		mov 			rsi, r10

                clc
.loop:
                mov             rax, [rsi]
                lea             rsi, [rsi + 8]
                adc             [rdi], rax
                lea             rdi, [rdi + 8]
                dec             rcx
                jnz             .loop

				pop 			rax
				pop 			r10
                pop             rcx
                pop             rsi
                pop             rdi
                ret

; adds 64-bit number to long number
;    rdi -- address of summand #1 (long number)
;    rax -- summand #2 (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    sum is written to rdi
add_long_short:
                push            rdi
                push            rcx
                push            rdx

                xor             rdx,rdx
.loop:
                add             [rdi], rax
                adc             rdx, 0
                mov             rax, rdx
                xor             rdx, rdx
                add             rdi, 8
                dec             rcx
                jnz             .loop

                pop             rdx
                pop             rcx
                pop             rdi
                ret

; multiplies long number by a short
;    rdi -- address of multiplier #1 (long number)
;    rbx -- multiplier #2 (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    product is written to rdi
mul_long_short:
                push            rax
                push            rdi
                push            rcx
				push 			rsi
				push 			rbx
				push			rdx

                xor             rsi, rsi
.loop:
                mov             rax, [rdi]
                mul             rbx
                add             rax, rsi
                adc             rdx, 0
                mov             [rdi], rax
                add             rdi, 8
                mov             rsi, rdx
                dec             rcx
                jnz             .loop

				pop 			rdx
				pop 			rbx
				pop				rsi
                pop             rcx
                pop             rdi
                pop             rax
                ret

; divides long number by a short
;    rdi -- address of dividend (long number)
;    rbx -- divisor (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    quotient is written to rdi
;    rdx -- remainder
div_long_short:
                push            rdi
                push            rax
                push            rcx

                lea             rdi, [rdi + 8 * rcx - 8]
                xor             rdx, rdx

.loop:
                mov             rax, [rdi]
                div             rbx
                mov             [rdi], rax
                sub             rdi, 8
                dec             rcx
                jnz             .loop

                pop             rcx
                pop             rax
                pop             rdi
                ret

; assigns a zero to long number
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
set_zero:
                push            rax
                push            rdi
                push            rcx

                xor             rax, rax
                rep stosq

                pop             rcx
                pop             rdi
                pop             rax
                ret

; checks if a long number is a zero
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
; result:
;    ZF=1 if zero
is_zero:
                push            rax
                push            rdi
                push            rcx

                xor             rax, rax
                rep scasq

                pop             rcx
                pop             rdi
                pop             rax
                ret

; read long number from stdin
;    rdi -- location for output (long number)
;    rcx -- length of long number in qwords
read_long:
                push            rcx
                push            rdi

                call            set_zero
.loop:
                call            read_char
                or              rax, rax
                js              exit
                cmp             rax, 0x0a
                je              .done
                cmp             rax, '0'
                jb              .invalid_char
                cmp             rax, '9'
                ja              .invalid_char

                sub             rax, '0'
                mov             rbx, 10
                call            mul_long_short
                call            add_long_short
                jmp             .loop

.done:
                pop             rdi
                pop             rcx
                ret

.invalid_char:
                mov             rsi, invalid_char_msg
                mov             rdx, invalid_char_msg_size
                call            print_string
                call            write_char
                mov             al, 0x0a
                call            write_char

.skip_loop:
                call            read_char
                or              rax, rax
                js              exit
                cmp             rax, 0x0a
                je              exit
                jmp             .skip_loop

; write long number to stdout
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
write_long:
                push            rax
                push            rcx

                mov             rax, 20
                mul             rcx
                mov             rbp, rsp
                sub             rsp, rax

                mov             rsi, rbp

.loop:
                mov             rbx, 10
                call            div_long_short
                add             rdx, '0'
                dec             rsi
                mov             [rsi], dl
                call            is_zero
                jnz             .loop

                mov             rdx, rbp
                sub             rdx, rsi
                call            print_string

                mov             rsp, rbp
                pop             rcx
                pop             rax
                ret

; read one char from stdin
; result:
;    rax == -1 if error occurs
;    rax \in [0; 255] if OK
read_char:
                push            rcx
                push            rdi

                sub             rsp, 1
                xor             rax, rax
                xor             rdi, rdi
                mov             rsi, rsp
                mov             rdx, 1
                syscall

                cmp             rax, 1
                jne             .error
                xor             rax, rax
                mov             al, [rsp]
                add             rsp, 1

                pop             rdi
                pop             rcx
                ret
.error:
                mov             rax, -1
                add             rsp, 1
                pop             rdi
                pop             rcx
                ret

; write one char to stdout, errors are ignored
;    al -- char
write_char:
                push rdi
                push rsi
                push rax
                push rcx
                push r11
                sub             rsp, 1
                mov             [rsp], al

                mov             rax, 1
                mov             rdi, 1
                mov             rsi, rsp
                mov             rdx, 1
                syscall
                add             rsp, 1

                pop r11
                pop rcx
                pop rax
                pop rsi
                pop rdi
                ret

exit:
                mov             rax, 60
                xor             rdi, rdi
                syscall

; print string to stdout
;    rsi -- string
;    rdx -- size
print_string:
                push            rax

                mov             rax, 1
                mov             rdi, 1
                syscall

                pop             rax
                ret


                section         .rodata
invalid_char_msg:
                db              "Invalid character: "
invalid_char_msg_size: equ             $ - invalid_char_msg
