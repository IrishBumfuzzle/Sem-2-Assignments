# int count = 0;
# for(int i = 0; i < n; i++){
#     int sum = arr[i];
#     for(int j = i; j < n; j++){
#         if(j != i)
#             sum += arr[j];
#         if(sum == 0)
#             count++;
#     }
# }
# return count;

.global subarray_sum

subarray_sum: # takes array and size as args
    movq $0, %rax # count = 0
    movq $0, %rdx # i = 0
    jmp .loop1


.inside1:
    movq (%rdi, %rdx, 8), %rcx # sum = arr[i]

    movq %rdx, %r8 # j = i
    jmp .loop2
    

.loop1:
    cmpq %rsi, %rdx # i < n
    jl .inside1
    ret

.inside2:
    movq $0, %r9 # temp = 0
    cmpq %r8, %rdx
    cmovne (%rdi, %r8, 8), %r9 # if i != j: temp = arr[j]
    addq %r9, %rcx # sum += temp

    leaq 1(%rax), %r9 # temp = count+1
    cmpq $0, %rcx
    cmove %r9, %rax # if sum == 0: count++

    addq $1, %r8 # j++

.loop2:
    cmpq %rsi, %r8 # j < n
    jl .inside2 

    addq $1, %rdx # i++
    jmp .loop1

