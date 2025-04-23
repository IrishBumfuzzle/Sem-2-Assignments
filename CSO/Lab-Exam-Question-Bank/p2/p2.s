.global palin

palin:
    movq $0, %rsi
    movq $0, %r10
    jmp loop1

inside1:
    addq $1, %rsi
loop1:
    cmpb $0, (%rdi, %rsi, 1)
    jne inside1
    addq $-1, %rsi
    jmp loop2

inside2:
    movb (%rdi, %rsi, 1), %r9b
    cmpb (%rdi, %r10, 1), %r9b
    jne ret0
    addq $1, %r10
    addq $-1, %rsi

loop2:
    cmpq %r10, %rsi
    jg inside2
    movq $1, %rax
    ret

ret0:
    movq $0, %rax
    ret
