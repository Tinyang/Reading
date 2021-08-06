#include <stdio.h>

typedef unsigned char *byte_pointer;

int main () {
 
    int a = 0x12345678;
    byte_pointer ap = (byte_pointer) &a;
    printf("%.2x", ap);
    //printf("%.8x", ap);
    printf("\n");


}