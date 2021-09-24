#include <stdio.h>

int main() {

int balance[] = {10,20,30,40};

int* addr1 = balance;
int* addr2 = &balance[2];
long addr3 = addr2 - addr1;

int a ;
int b = !a;

printf("Value of *ip variable: %d\n", addr1 );
printf("Value of *ip variable: %d\n", a );
printf("Value of *ip variable: %d\n", b );

//2293280
//2293284
//2293288


}