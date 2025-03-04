.global calc

calc:
    movq $0, %rax # ones
    movq $0, %rcx # twos
    movq $0, %r10 # bitmask

    movq $0, %r8 # i = 1
    jmp .loop

.inside:
    movq %rax, %r9
    andq (%rsi, %r8, 8), %r9 # ones & arr[i]
    orq %r9, %rcx # twos = twos | (ones & arr[i])

    xorq (%rsi, %r8, 8), %rax # one ^= arr[i]

    movq %rax, %r10
    andq %rcx, %r10
    notq %r10 # bitmask = ~(one & two)

    andq %r10, %rax # one &= bitmask
    andq %r10, %rcx # two &= bitmask

    addq $1, %r8 # i++


.loop:
    cmpq %rdi, %r8 # i < n
    jl .inside
    ret




