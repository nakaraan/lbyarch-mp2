section .text
bits 64
default rel

global asmhello
extern printf
extern puts

; Using puts instead (simpler - no format string needed)
section .data
msg db "Hello World", 0

section .text
asmhello:
    sub rsp, 32
    lea rcx, [msg]
    call puts
    add rsp, 32
    ret