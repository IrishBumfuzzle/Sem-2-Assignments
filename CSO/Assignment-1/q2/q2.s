.global rot_by_two

rot_by_two:
    movq $0, %r8 # i = 0
    movq %rdx, %rcx # save pointer

    jmp .loop

.inside:
    movq (%rsi, %r8, 8), %r9
    
    leaq 2(%r8), %rax # i + 2
    movq $0, %rdx
    idivq %rdi # (i + 2) % n

    movq %r9, (%rcx, %rdx, 8) # new[^] = arr[i]
    
    addq $1, %r8 # i++

.loop:
    cmpq %rdi, %r8
    jl .inside
    ret
    
