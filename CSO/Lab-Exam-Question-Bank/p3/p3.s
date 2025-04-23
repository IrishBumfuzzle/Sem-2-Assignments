.global score

score:
    movq $0, %rsi
    jmp loop1

inside1:
    addq $1, %rsi

loop1:
    cmpb $0, (%rdi, %rsi, 1)
    jne inside1

    movq $1, %r10
    movq $0, %rax
    jmp loop2

inside2:
    movsbq -1(%rdi, %r10, 1), %r9
    negq %r9
    movsbq (%rdi, %r10, 1), %r11
    addq %r11, %r9
    cmpq $0, %r9
    jg moveon
    negq %r9 

    moveon:
        addq %r9, %rax
        addq $1, %r10

loop2:
    cmpq %r10, %rsi
    jg inside2
    ret
