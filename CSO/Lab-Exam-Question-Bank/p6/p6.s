.global duplicate

duplicate:
    movq $0, %r9
    jmp loop1

inside2:
    movq (%rdi, %r12, 8), %rcx
    cmpq %rcx, (%rdi, %r9, 8)
    jng after
    movq (%rdi, %r9, 8), %rcx
    pushq %rcx
    movq (%rdi, %r12, 8), %rcx
    movq %rcx, (%rdi, %r9, 8)
    popq %rcx
    movq %rcx, (%rdi, %r12, 8)

    after:
        addq $1, %r12

loop2:
    cmpq %r12, %rsi
    jg inside2
    addq $1, %r9
    jmp loop1

inside1:
    movq %r9, %r12
    addq $1, %r12
    cmpq %r12, %rsi
    jg inside2

    addq $1, %r9

loop1:
    cmpq %r9, %rsi
    jg inside1

    movq $1, %r9
    movq (%rdi), %r10
    addq $1, %r10
    
    jmp loop3

inside3:
    cmpq %r10, (%rdi, %r9, 8)
    jne reto
    addq $1, %r10
    addq $1, %r9

loop3:
    cmpq %r9, %rsi
    jg inside3
    movq $1, %rax
    ret 

reto:
    movq $0, %rax
    ret
