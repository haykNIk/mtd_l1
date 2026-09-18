/*
 * @Author: hayknik
 */
#include <stdio.h>

int main()
{
    unsigned int a;

    printf("input non-negative number:\n");
    scanf("%u", &a);

    printf("the value of `a` is %u\n", a);

    unsigned int* pa = &a;
    printf("the pointer value is %p\n", pa);

    int b_value;
    printf("input a number:\n");
    scanf("%d", &b_value);
    printf("the value of `b_value` is %d\n", b_value);
    return 0;
}
