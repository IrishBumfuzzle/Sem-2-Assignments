#    long long count = 0;
#    long long candidate = -1;
#
#    for(long long i = 0; i < n; i++){
#        if(count == 0){
#            candidate = arr[i];
#            count = 1;
#        } else if(arr[i] == candidate){
#            count++;
#        } else {
#            count--;
#        }
#    }
#
#    return candidate;

.global majority

majority:
    movq $0, %r8
    movq $-1, %rax
    movq $0, %r9
    jmp .loop

.inside:
    .if:
        cmpq $0, %r8
        jne .elseif
        movq (%rdi, %r9, 8), %rax
        movq $1, %r8
        jmp .finally
    
    .elseif:
        cmpq (%rdi, %r9, 8), %rax
        jne .else
        addq $1, %r8
        jmp .finally

    .else:
        addq $-1, %r8

    .finally:
        addq $1, %r9

.loop:
    cmpq %rsi, %r9
    jl .inside
    ret
