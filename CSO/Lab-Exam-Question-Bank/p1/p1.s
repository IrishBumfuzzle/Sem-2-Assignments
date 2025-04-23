.global doSomething

doSomething:
    movq $1, %r9
    jmp loop1

inside1:
    if1:
        movq %r9, %rax
        cqto
        movq $2, %r11
        idiv %r11
        cmpq $0, %rdx
        jne elseif2
        movq %r9, %rax
        cqto
        movq $7, %r11
        idiv %r11
        cmpq $0, %rdx
        jne elseif2
        movq $-3, (%rdi, %r9, 8)
        jmp after
    elseif2:
        movq %r9, %rax
        cqto
        movq $2, %r11
        idiv %r11
        cmpq $0, %rdx
        jne elseif3
        movq $-1, (%rdi, %r9, 8)
        jmp after
    elseif3:
        movq %r9, %rax
        cqto
        movq $7, %r11
        idiv %r11
        cmpq $0, %rdx
        jne else
        movq $-2, (%rdi, %r9, 8)
        jmp after
    else:
        movq %r9, (%rdi, %r9, 8)
    after:
        addq $1, %r9

loop1:
    cmpq %rsi, %r9
    jle inside1
    ret
