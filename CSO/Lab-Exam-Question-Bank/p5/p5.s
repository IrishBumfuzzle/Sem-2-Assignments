.global unique

unique:
    movq $1, %r11
    movq $0, %r9
    movq (%rdi), %r10
    movq %r10, (%rdx)
    jmp loop1

inside1:
    movq (%rdx, %r9, 8), %r10
    cmpq %r10, (%rdi, %r11, 8)
    je after
    movq (%rdi, %r11, 8), %r10
    addq $1, %r9
    movq %r10, (%rdx, %r9, 8)

    after:
        addq $1, %r11


loop1:
    cmpq %r11, %rsi
    jg inside1
    addq $1, %r9
    movq %r9, (%rcx)
    ret
