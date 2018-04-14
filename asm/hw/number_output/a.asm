  extern _printf
  extern _putchar
  section .text
  global _main

;print unsigned number
; eax - number
_print_unsigned_number:
  ; remember regs
  push ebx
  push edx
  push eax

  mov ebx, 10
  xor esi, esi ; digit counter

_loop_1:
  xor edx, edx ; set 0 for division
  div ebx
  add edx, '0' ; set remainder to string
  push edx

  inc esi
  test eax, eax
  jnz _loop_1

_loop_2:
  call _putchar
  pop edx
  dec esi
  jnz _loop_2

  pop eax
  pop edx
  pop ebx
  ret

;print signed number
; eax - number
_print_signed_number:
  push eax
  push esi

  test eax, eax
  jns _if_unsigned_in_signed

  mov esi, '-'

  push eax
  push esi 
  call _putchar

  pop esi
  pop eax
  neg eax
_if_unsigned_in_signed:
  call _print_unsigned_number
  
  pop eax
  pop esi
  ret

_main:
  int3
  mov eax, -2147483648
  call _print_signed_number
  ret
