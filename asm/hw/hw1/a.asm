  extern _printf
  section .text
  global _main

_main:
  push string
  push format
  call _printf
  add  esp, 8
  int3
  ret

  section .rdata

format: db "%s", 0xA, 0
string: db "Hello, World!", 0
