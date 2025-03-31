# int s[n];
# int len = 0;
# for(int i = 0; i < n; i++){
#     if(len == 0){
#         s[len] = i;
#         len++;
#     } else {
#         while(len > 0 && input[s[len - 1]] < input[i]){
#             ans[s[len - 1]] = input[i];
#             len--;
#         }
#         s[len] = i;
#         len++;
#     }
# }
# while(len > 0){
#     ans[s[len - 1]] = -1;
#     len--;
# }

.global marks

marks: # marks(input, ans, n)
    movq $0, %rax # len = 0
    movq $0, %rcx # i = 0
    jmp .loop1

.inside1:
    cmpq $0, %rax # if len == 0: dont jmp
    jne else1

    if1:
        pushq %rcx # s[len] = i
        addq $1, %rax # len++
        jmp .loop1

    else1:
        jmp .loop2

        .inside2:
            movq %r8, (%rsi, %r9, 8) # ans[s[len-1]] = input[i]
            addq $-1, %rax # len--

        .loop2:
            cmpq $0, %rax # if len > 0: dont jmp
            jng .loop_cont

        .loop2_2:
            popq %r9 # get top value
            movq (%rdi, %rcx, 8), %r8 # input[i]
            cmpq (%rdi, %r9, 8), %r8 # if input[i] > input[s[len-1]]
            jg .inside2
            pushq %r9 # put value back
        
        .loop_cont:
            pushq %rcx # s[len] = i
            addq $1, %rax # len++

            addq $1, %rcx # i++

.loop1:
    cmpq %rdx, %rcx # if i < n
    jl .inside1 
    jmp .loop3

.inside3:
    popq %r9 # get top value
    movq $-1, (%rsi, %r9, 8) # ans[s[len-1]] = -1
    addq $-1, %rax # len--

.loop3:
    cmpq $0, %rax # if len > 0
    jg .inside3
    ret
