.global summation

summation:
    imulq %rdx, %rsi
    movq $0, %r9
    movq $0, %r12
    jmp loop1

inside1:
    movq (%rdi, %r9, 8), %rax
    cqto
    movq $3, %r10
    idivq %r10
    cmpq $0, %rdx
    jne after
    movq $5, %rax
    movq (%rdi, %r9, 8), %rax
    cqto
    movq $5, %r10
    idivq %r10
    cmpq $0, %rdx
    je after
    addq (%rdi, %r9, 8), %r12

    after:
        addq $1, %r9

loop1:
    cmpq %r9, %rsi
    jg inside1
    movq %r12, %rax
    ret
