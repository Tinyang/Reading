long fact_do(long n) {
    long result = 1;
    do {
        result *= n;
        n = n - 1;
    } while (n > 1);
    return result;
}


long fact_do_goto(long n) {
    long result = 1;
loop:
    result *= n;
    n = n - 1;
    if (n > 1)
        goto loop;
    
    return result;
}


/*
    fact_do:
        movl $1, %eax
    .L2:
        imulq %rdi, %rax
        subq $1, %rdi
        cmpq $1, %rdi
        jg .L2
    rep; ret
*/





















