/*
 * Лабораторная работа №1.
 * Базовые типы, ветвления, циклы, ввод-вывод.
 * Решение квадратного уравнения ax^2 + bx + c = 0.
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
    double a, b, c;
    double d, x1, x2;

    printf("Введите коэффициенты a, b, c:\n");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Некорректный ввод\n");
        return 1;
    }

    if (fabs(a) < 1e-12) {
        printf("Это не квадратное уравнение\n");
        return 1;
    }

    d = b * b - 4 * a * c;

    if (d < 0) {
        printf("Действительных корней нет\n");
    } else if (fabs(d) < 1e-12) {
        x1 = -b / (2 * a);
        printf("Один корень: x = %.4f\n", x1);
    } else {
        x1 = (-b + sqrt(d)) / (2 * a);
        x2 = (-b - sqrt(d)) / (2 * a);
        printf("Два корня: x1 = %.4f, x2 = %.4f\n", x1, x2);
    }

    return 0;
}
