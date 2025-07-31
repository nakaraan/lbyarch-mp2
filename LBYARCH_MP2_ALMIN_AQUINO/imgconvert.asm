;   RCX = height (int)
;   RDX = width (int) 
;   R8  = pointer to input integer pixels (unsigned char*)
;   R9  = pointer to output float pixels (float*)

section .text
global imgCvtGrayInttoFloat

imgCvtGrayInttoFloat:
    ; Save registers that we'll use
    push rbp
    mov rbp, rsp
    push rsi
    push rdi
    push rbx
    
    ; Calculate total number of pixels (height * width)
    mov rax, rcx
    mul rdx
    mov rbx, rax
    
    ; Initialize pointers
    mov rsi, r8
    mov rdi, r9
    
    ; Load constant 255.0 into xmm1 for division
    mov eax, 0x437f0000
    movd xmm1, eax
    
    ; Initialize loop counter
    xor rcx, rcx
    
convert_loop:
    cmp rcx, rbx
    jge done
    
    xor rax, rax
    mov al, [rsi + rcx]
    
    ; Convert integer to float
    cvtsi2ss xmm0, eax
    
    ; Divide by 255.0 to normalize to 0.0-1.0 range
    divss xmm0, xmm1
    
    ; Store result in destination array
    movss [rdi + rcx * 4], xmm0
    
    ; Increment loop counter
    inc rcx
    jmp convert_loop
    
done:
    pop rbx
    pop rdi
    pop rsi
    pop rbp
    ret