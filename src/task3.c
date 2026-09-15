#include <stdio.h>

int main()
{
    unsigned int a;

    printf("input non-negative number:\n");
    scanf("%u", &a);

    printf("the value of `a` is %u\n", a);

    unsigned int* pa = &a;
    printf("the pointer value is %p\n", pa);

    int b;
    printf("input a number:\n");
    scanf("%d", &b);
    printf("the value of `b` is %d\n", b);
    return 0;
}
