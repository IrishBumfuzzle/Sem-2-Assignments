#    if(n == 2){
#        if(nums[0] > nums[1]) return nums[0];
#        else return nums[1];
#    }
#    int l = 0, r = n - 1;
#    while(true){
#        int curr = (l+r)/2;
#        int check = nums[curr];
#        if( (curr == 0 || nums[curr-1] <= check) && (curr == n-1 || nums[curr+1] <= check) ){
#            return nums[curr];
#        }
#        if(nums[curr-1] > nums[curr+1]) r--;
#        else l++;
#    }

.global peak

peak:
    if1:
        cmpq $2, %rsi
        jne else1
        if2:
            movw 2(%rdi), %ax
            cmpw (%rdi), %ax
            jng else2
            ret
        else2:
            movw (%rdi), %ax
            ret

    else1:
    movq $0, %r8
    movq %rsi, %r9
    addq $-1, %r9
    jmp loop

loop:
    movq $0, %r10
    addq %r8, %r10
    addq %r9, %r10
    sar $1, %r10

    movw (%rdi, %r10, 2), %r11w
    if3:
        cmpq $0, %r10
        je if4
        cmpw -2(%rdi, %r10, 2), %r11w
        jnge else3

        if4:
            movq %rsi, %rax
            addq $-1, %rax
            cmpq %r10, %rax
            je found
            cmpw 2(%rdi, %r10, 2), %r11w
            jnge else3
        found:
            movw (%rdi, %r10, 2), %ax
            ret

    else3:
        if5:
            movw -2(%rdi, %r10, 2), %ax
            cmpw 2(%rdi, %r10, 2), %ax
            jng else5
            addq $-1, %r9
            jmp finally
        else5:
            addq $1, %r8
        finally:
            jmp loop
