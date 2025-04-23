.global special

special:
    pushq %rdi
    movq $0, %r9
    movq %rdi, %r10
    movq $10, %r11
    jmp loop1

inside1:
    movq %r10, %rax
    cqto
    idivq %r11
    movq %rdx, %rdi

    call factorial
    addq %rax, %r9

    movq %r10, %rax
    cqto
    idivq %r11
    movq %rax, %r10

loop1:
    cmpq $0, %r10
    je finally
    jmp inside1

finally:
    popq %rdi
    cmpq %r9, %rdi
    je ret1
    movq $0, %rax
    ret


factorial:
    cmpq $0, %rdi
    je ret1

    pushq %rdi
    addq $-1, %rdi
    call factorial
    popq %rdi
    imulq %rdi, %rax
    ret

ret1:
    movq $1, %rax
    ret
