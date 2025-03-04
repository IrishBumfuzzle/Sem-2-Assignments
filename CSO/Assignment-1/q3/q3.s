.global palin

.ret0: # return 0
    movq $0, %rax 
    ret
    
palin:
    movq $0, %r8 # front = 0

    leaq -1(%rdi), %r9 # end = n-1

    jmp .loop

.inside:
    movb (%rsi, %r8, 1), %r10b 
    cmpb %r10b, (%rsi, %r9, 1) # if str[front] != str[end]
    jne .ret0 # return 0

    addq $1, %r8 # front++
    subq $1, %r9 # end--

.loop:
    cmp %r9, %r8 # front < end
    jl .inside

    movq $1, %rax # return 1
    ret
