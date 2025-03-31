# if(n<r){
#     return 0;
# }
# if(r == 0){
#     return 1;
# }
# if(r == 1){
#     return n;
# }
# if(n == 1){
#     return 1;
# }
# return comb(n-1,r-1)+comb(n-1,r);

.global comb

return:
    ret

comb: # args(n, r)

    movq $0, %rdx # temp = 0
    cmpq %rsi, %rdi
    cmovl %rdx, %rax
    jl return # if n < r: return 0

    movq $1, %rdx # temp = 1
    cmpq $0, %rsi
    cmove %rdx, %rax
    je return # if r == 0: return 1

    cmpq $1, %rsi
    cmove %rdi, %rax
    je return # if r == 1: return n

    cmpq $1, %rdi
    cmove %rdx, %rax
    je return # if n == 1: return 1

    pushq %rdi
    pushq %rsi # save n and r

    addq $-1, %rdi
    addq $-1, %rsi 
    call comb # comb(n-1, r-1)
    popq %rsi
    popq %rdi

    pushq %rax # save ret value of above call

    addq $-1, %rdi
    call comb # comb(n-1, r)

    movq %rax, %rdx
    popq %rax
    addq %rdx, %rax # add the new value to previous value
    ret
