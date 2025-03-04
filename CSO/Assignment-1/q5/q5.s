.global prod

prod:
    movq $1, %r8 # i = 1

    movq $1, (%rdx) # out[i] = 1
    
    jmp .loop1

.inside1:
    leaq -1(%r8), %r10
    movq (%rsi, %r10, 8), %r9 # r9 = nums[i-1]

    imulq (%rdx, %r10, 8), %r9 # r9 *= out[i-1]

    movq %r9, (%rdx, %r8, 8) # out[i] = nums[i-1] * out[i-1]

    addq $1, %r8 # i++

.loop1:
    cmpq %rdi, %r8 # i < n
    jl .inside1

    movq $1, %r9 # right = 1
    leaq -1(%rdi), %r8 # i = n-1

    jmp .loop2

.inside2:
    movq (%rdx, %r8, 8), %r10
    imulq %r9, %r10
    movq %r10, (%rdx, %r8, 8) # out[i] *= right

    imulq (%rsi, %r8, 8), %r9 # right *= nums[i]

    subq $1, %r8 # i--

.loop2:
    cmpq $0, %r8 # i >= 0
    jge .inside2

    ret
