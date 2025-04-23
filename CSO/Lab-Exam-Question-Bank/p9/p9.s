.global find

find:
    cmpq %rsi, %rdx
    jl ret1
    
    movq %rsi, %r9
    addq %rdx, %r9
    sar $1, %r9

    cmpq (%rdi, %r9, 8), %rcx
    je retv
    jg midl
    jl midg
    after:
        call find
        ret

ret1:
    movq $-1, %rax
    ret
retv:
    movq %r9, %rax
    ret

midl:
    movq %r9, %rsi
    addq $1, %rsi
    jmp after

midg:
    movq %r9, %rdx
    addq $-1, %rdx
    jmp after
