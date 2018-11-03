  extern printf
  section .text
  global main
  default rel
main:
  lea rcx, [format]
  lea rdx, [string]
  sub rsp, 40
  call printf
  add rsp, 40
  ret

  section .rdata
format: db "%s", 0xA, 0
string: db "Hello, World!", 0
