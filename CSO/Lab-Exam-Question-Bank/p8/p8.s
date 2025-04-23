.global wave

wave:
    movq $0, %r9
    jmp loop1

inside2:
    movq (%rdi, %r10, 8), %r11
    cmpq %r11, (%rdi, %r9, 8)
    jng after

    pushq %r11
    movq (%rdi, %r9, 8), %r11
    movq %r11, (%rdi, %r10, 8)
    popq %r11
    movq %r11, (%rdi, %r9, 8)

    after:
        addq $1, %r10

loop2:
    cmpq %r10, %rsi
    jg inside2
    addq $1, %r9

inside1:
    cmpq %r9, %rsi
    jng actual
    movq %r9, %r10
    addq $1, %r10
    jmp loop2

loop1:
    cmpq %r9, %rsi
    jg inside1

actual:
    movq $0, %r9
    addq $-1, %rsi
    jmp loop3

inside3:
    movq (%rdi, %r9, 8), %r11
    pushq %r11
    movq 8(%rdi, %r9, 8), %r11
    movq %r11, (%rdi, %r9, 8)
    popq %r11
    movq %r11, 8(%rdi, %r9, 8)
    addq $2, %r9

loop3:
    cmpq %r9, %rsi
    jg inside3
    ret
