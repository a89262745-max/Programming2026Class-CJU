#include<stdio.h>

int main(void) {
    
    int a, b;
    int sum, sub, mul, inv;

    a=10;
    b-20;
    sum=a+b;
    sub=a-b;
    mul=a*b;
    inv = -a;

    printf("a: %d, b: %d\n", a, b);
    printf("Sum: %d\n", sum);
    printf("Subtraction: %d\n", sub);
    printf("Multiplication: %d\n", mul);
    printf("Negative a: %d\n", inv);
    return 0;
}