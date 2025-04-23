.global rotation

rotation:
    movq $1, %r9
    movq $1, %r8
    movq %rdi, %r10
    jmp loop1
    
inside1:
    imulq $10, %r9
    addq $1, %r8

loop1:
    cmpq %r8, %rsi
    jg inside1
    movq $0, %r8
    movq $10, %r11

inside3:
    movq %r10, %rdi
    call primecheck
    cmpq $1, %rax
    jne reto

    movq %r10, %rax
    cqto
    idivq %r11
    movq %rax, %r10
    imulq %r9, %rdx
    addq %rdx, %r10
    addq $1, %r8

loop3:
    cmpq %r8, %rsi
    jg inside3
    movq $1, %rax
    ret

primecheck:
    movq $2, %rcx
    jmp loop2

inside2:
    movq %rdi, %rax
    cqto 
    idivq %rcx
    cmpq $0, %rdx
    je reto
    addq $1, %rcx

loop2:
    cmpq %rcx, %rdi
    jg inside2
    movq $1, %rax
    ret

reto:
    movq $0, %rax
    ret
