void cond(short a, short *p) {

    if (a && *p < a) {
        *p = a;
    }
}

/*
cond:
 testq %rdi, %rdi
 je .L1
 cmpq %rsi,
*/



long absdiff(long x, long y) {
    long result;
    if (x < y) {
        result = y - x;
    } else {
        result = x - y;
    }

    return result;
}

/* assembly code
x in %rdi, y in %rsi
absdiff:
    movq   %rsi, %rax
    subq   %rdi, %rax   // %rax = %rax - %rdi
    movq   %rdi, %rdx
    subq   %rsi, %rdx
    cmpq   %rsi, %rdi
    cmovge %rdx, %rax
    ret
*/








