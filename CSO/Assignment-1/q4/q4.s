.global diff

diff:
    movq $0, %r8 # i = 0
    movq $9223372036854775807, %r9 # min_num = ll_max
    movq $-9223372036854775808, %rax # max_num = ll_min

.inside:
    cmpq %r9, (%rsi, %r8, 8) # if num[i] < min_num
    cmovlq (%rsi, %r8, 8), %r9 # min_num = num[i]

    cmpq (%rsi, %r8, 8), %rax # if num[i] > max_num
    cmovl (%rsi, %r8, 8), %rax # max_num = num[i]

    addq $1, %r8 # i++

.loop:
    cmpq %rdi, %r8 # i < n
    jl .inside

    subq %r9, %rax # ans = max_num - min_num
    
    ret
