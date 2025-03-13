.global prod

prod:
    movq $1, %r8 # i = 1
    movq %rdx, %rcx
    movq $9223372036854775807, %r11 # put LL_MAX for later modulo

    movq $1, (%rcx) # out[i] = 1
    
    jmp .loop1

.inside1:
    leaq -1(%r8), %r10
    movq (%rsi, %r10, 8), %r9 # r9 = nums[i-1]

    movq (%rcx, %r10, 8), %rax
    cqto
    imulq %r9
    idivq %r11

    movq %rdx, (%rcx, %r8, 8) # out[i] = nums[i-1] * out[i-1]

    addq $1, %r8 # i++

.loop1:
    cmpq %rdi, %r8 # i < n
    jl .inside1

    movq $1, %r9 # right = 1
    leaq -1(%rdi), %r8 # i = n-1

    jmp .loop2

.inside2:
    movq (%rcx, %r8, 8), %rax
    cqto
    imulq %r9
    idivq %r11 # Taking the mod of out[i] * right by LL_MAX
    movq %rdx, (%rcx, %r8, 8) # out[i] = (right * out[i]) % LL_MAX

    movq (%rsi, %r8, 8), %rax
    cqto
    imulq %r9 # right * nums[i]
    idivq %r11 # Taking mod by LL_MAX
    movq %rdx, %r9 # right = (nums[i] * right) % LL_MAX

    subq $1, %r8 # i--

.loop2:
    cmpq $0, %r8 # i >= 0
    jge .inside2

    ret
