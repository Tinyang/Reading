#include <stdio.h>

typedef unsigned char *byte_pointer;//char大小只有一个字节，所以这个指针只指向一个一个字节

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++) {
        printf("%.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}


void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival); 
    show_float(fval);
    show_pointer(pval);
}


int main(int argc, char const *argv[])
{   
    int *b = 123;
    printf("%p\n", b);
    int a = 0X12345678;
    printf("%p\n", &a);
    byte_pointer ap = (byte_pointer)&a;
    printf("%p\n", ap);

    printf("%x\n", *ap );//这种写法也是取地址对应的值

    printf("%x\n", ap[0] );//ap是个地址，ap[0]用来取该地址对应的值
    printf("%x\n", ap[1] );
    printf("%x\n", ap[2] );
    printf("%x\n", ap[3] );
    

    printf("%4x\n", *ap );
    show_bytes((byte_pointer)&a, 1);
    show_bytes((byte_pointer)&a, 2);
    show_bytes((byte_pointer)&a, 3);
    //show_bytes((byte_pointer)&a,(int)4);
    //show_bytes((byte_pointer)&a,(int)20);
    //printf("%8d\n", sizeof(int));
    return 0;
}














