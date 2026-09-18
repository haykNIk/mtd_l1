/*
 * @Author: hayknik
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

// Задание 1: Функция swap и тестирование
// Напишите функцию swap(int *i, int *j), которая меняет значения двух ячеек местами.
// Напишите как можно больше тестов для этой функции (не меньше 10)

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Тестирование функции swap
#define TEST_SWAP(condition, test_name) \
    do { \
        if (!(condition)) { \
            printf("Тест не пройден: %s\n", test_name); \
            return 1; \
        } \
    } while(0)

void test_swap_functions() {
    printf("\nТестирование функции swap\n");

    // Тест 1: Простой обмен
    {
        int a = 5, b = 10;
        swap(&a, &b);
        if (a != 10 || b != 5) {
            printf("Ошибка: простой обмен не работает\n");
        }
        else {
            printf("Тест 1 пройден: простой обмен\n");
        }
    }

    // Тест 2: Отрицательные числа
    {
        int a = -5, b = -10;
        swap(&a, &b);
        if (a != -10 || b != -5) {
            printf("Ошибка: обмен отрицательных чисел\n");
        }
        else {
            printf("Тест 2 пройден: отрицательные числа\n");
        }
    }

    // Тест 3: Нули
    {
        int a = 0, b = 0;
        swap(&a, &b);
        if (a != 0 || b != 0) {
            printf("Ошибка: обмен нулей\n");
        }
        else {
            printf("Тест 3 пройден: нули\n");
        }
    }

    // Тест 4: Положительное и отрицательное
    {
        int a = 5, b = -3;
        swap(&a, &b);
        if (a != -3 || b != 5) {
            printf("Ошибка: обмен чисел с разными знаками\n");
        }
        else {
            printf("Тест 4 пройден: разные знаки\n");
        }
    }

    // Тест 5: Большие числа
    {
        int a = 1000000, b = -1000000;
        swap(&a, &b);
        if (a != -1000000 || b != 1000000) {
            printf("Ошибка: обмен больших чисел\n");
        }
        else {
            printf("Тест 5 пройден: большие числа\n");
        }
    }

    // Тест 6: Обмен с самим собой
    {
        int a = 7;
        swap(&a, &a);
        if (a != 7) {
            printf("Ошибка: обмен с самим собой\n");
        }
        else {
            printf("Тест 6 пройден: обмен с самим собой\n");
        }
    }

    // Тест 7: Предельные значения
    {
        int a = INT_MAX, b = INT_MIN;
        swap(&a, &b);
        if (a != INT_MIN || b != INT_MAX) {
            printf("Ошибка: предельные значения\n");
        }
        else {
            printf("Тест 7 пройден: предельные значения\n");
        }
    }

    // Тест 8: Четное и нечетное
    {
        int a = 1, b = 2;
        swap(&a, &b);
        if (a != 2 || b != 1) {
            printf("Ошибка: четное и нечетное\n");
        }
        else {
            printf("Тест 8 пройден: четное и нечетное\n");
        }
    }

    // Тест 9: Двойной обмен
    {
        int a = 3, b = 4;
        swap(&a, &b);
        swap(&a, &b);
        if (a != 3 || b != 4) {
            printf("Ошибка: двойной обмен\n");
        }
        else {
            printf("Тест 9 пройден: двойной обмен\n");
        }
    }

    // Тест 10: Обмен через указатели
    {
        int a = 5, b = 10;
        int* p1 = &a;
        int* p2 = &b;
        swap(p1, p2);
        if (a != 10 || b != 5) {
            printf("Ошибка: обмен через указатели\n");
        }
        else {
            printf("Тест 10 пройден: через указатели\n");
        }
    }

    // Тест 11: Обмен элементов массива
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        swap(&arr[0], &arr[4]);
        if (arr[0] != 5 || arr[4] != 1) {
            printf("Ошибка: обмен элементов массива\n");
        }
        else {
            printf("Тест 11 пройден: элементы массива\n");
        }
    }

    printf("Все тесты пройдены!\n\n");
}

// Задание 2: Указатели на массивы в качестве аргументов
// Напишите два варианта функции поиска минимального элемента:
// 2a. во встроенном двухмерном массиве
// 2b. в динамическом двухмерном массиве (обе размерности вычисляются)

// Функция для статического массива
int find_min_static(int* matrix, int rows, int cols) {
    int min = matrix[0];
    for (int i = 0; i < rows * cols; i++) {
        if (matrix[i] < min) {
            min = matrix[i];
        }
    }
    return min;
}

// Функция для динамического массива
int find_min_dynamic(int** matrix, int rows, int cols) {
    int min = matrix[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
    }
    return min;
}

// Задание 3: Функция сравнения двух строк
// Напишите функцию сравнения двух строк - myStrCmp():
// Функция должна принимать два указателя на сравниваемые строки
// Функция должна возвращать отрицательное значение, если первая строка лексиграфически меньше второй,
// 0 - если они равны и положительное значение, если первая строка больше второй.

int my_str_cmp(const char* str1, const char* str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (unsigned char)(*str1) - (unsigned char)(*str2);
}

// Задание 4: Динамический массив с уникальными значениями
// Создайте одномерный динамический массив, заполните его значениями.
// Напишите функцию, которая добавляет в массив новое значение только при условии,
// что такого значения в массиве еще нет. Подсказка: при этом размер массива должен увеличиться!
// Для проверки напишите функцию, которая выводит значения всех элементов на экран

typedef struct {
    int* data;
    int size;
    int capacity;
} UniqueArray;

// Создание массива
UniqueArray* create_array(int initial_capacity) {
    UniqueArray* arr = (UniqueArray*)malloc(sizeof(UniqueArray));
    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = initial_capacity;
    return arr;
}

// Освобождение памяти
void free_array(UniqueArray* arr) {
    free(arr->data);
    free(arr);
}

// Проверка наличия значения
int contains(UniqueArray* arr, int value) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

// Добавление уникального значения
void add_unique(UniqueArray* arr, int value) {
    // Проверяем, есть ли уже такое значение
    if (contains(arr, value)) {
        printf("Значение %d уже есть в массиве\n", value);
        return;
    }

    // Если массив заполнен, увеличиваем его размер
    if (arr->size >= arr->capacity) {
        int new_capacity = arr->capacity * 2;
        int* new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            printf("Ошибка выделения памяти!\n");
            return;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
        printf("Массив увеличен до размера %d\n", arr->capacity);
    }

    // Добавляем новое значение
    arr->data[arr->size] = value;
    arr->size++;
    printf("Добавлено значение: %d\n", value);
}

// Вывод массива
void print_array(UniqueArray* arr) {
    printf("Массив [размер: %d, вместимость: %d]: ", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

// Задание 5: Рекурсивные функции
// 5a. Напишите рекурсивную функцию вычисления суммы первых N натуральных чисел
// 5б. Напишите рекурсивную функцию для вычисления N-го числа Фибоначчи

int sum_natural(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum_natural(n - 1);
}

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Задание 6: Функции с переменным числом параметров
// 6а. Напишите функцию varArgs, не использующую макросы,
// которая принимает переменное число аргументов типа int и выводит на печать
// число принятых параметров и их значения. Признаком конца списка параметров является нулевое значение.
// 6б. Модифицируйте функцию 6а с помощью макросов va_start, va_arg, va_end

// Вариант без макросов (работает только для некоторых компиляторов)
void print_args_no_macros(int first, ...) {
    printf("Аргументы: ");
    int* ptr = &first;
    int count = 0;

    while (*ptr != 0) {
        printf("%d ", *ptr);
        ptr++;
        count++;
    }

    printf("\nВсего аргументов: %d\n", count);
}

// Вариант с макросами (правильный способ)
void print_args_with_macros(int first, ...) {
    va_list args;
    int value;
    int count = 0;

    printf("Аргументы: ");
    va_start(args, first);

    value = first;
    while (value != 0) {
        printf("%d ", value);
        count++;
        value = va_arg(args, int);
    }

    va_end(args);
    printf("\nВсего аргументов: %d\n", count);
}

// Задание 7: Возвращение адреса
// Напишите функцию, которая находит минимальное значение в массиве,
// таким образом, чтобы ее вызов можно было использовать слева от знака
// равенства: *myMin(параметры) = 0;

int* find_min_address(int* array, int size) {
    if (size <= 0) {
        return NULL;
    }

    int* min_ptr = &array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < *min_ptr) {
            min_ptr = &array[i];
        }
    }

    return min_ptr;
}

// Основная функция для тестирования
int main() {
    printf("Лабораторная работа по программированию на C\n\n");

    // Задание 1
    test_swap_functions();

    // Задание 2
    printf("=== Задание 2: Поиск минимального элемента ===\n");

    // Статический массив
    int static_matrix[3][4] = {
        {5, 12, 3, 8},
        {15, 2, 9, 4},
        {7, 11, 6, 1}
    };

    int min_static = find_min_static((int*)static_matrix, 3, 4);
    printf("Минимальный элемент в статическом массиве: %d\n", min_static);

    // Динамический массив
    int rows = 3, cols = 4;
    int** dynamic_matrix = (int**)malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        dynamic_matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            dynamic_matrix[i][j] = static_matrix[i][j];
        }
    }

    int min_dynamic = find_min_dynamic(dynamic_matrix, rows, cols);
    printf("Минимальный элемент в динамическом массиве: %d\n", min_dynamic);

    // Освобождаем память
    for (int i = 0; i < rows; i++) {
        free(dynamic_matrix[i]);
    }
    free(dynamic_matrix);

    printf("\n");

    // Задание 3
    printf("Задание 3: Сравнение строк\n");

    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hell";
    char str4[] = "Hello World";

    printf("Сравнение '%s' и '%s': %d\n", str1, str2, my_str_cmp(str1, str2));
    printf("Сравнение '%s' и '%s': %d\n", str1, str3, my_str_cmp(str1, str3));
    printf("Сравнение '%s' и '%s': %d\n", str3, str1, my_str_cmp(str3, str1));
    printf("Сравнение '%s' и '%s': %d\n", str1, str4, my_str_cmp(str1, str4));

    printf("\n");

    // Задание 4
    printf("Задание 4: Динамический массив с уникальными значениями \n");

    UniqueArray* my_array = create_array(3);

    printf("Добавляем элементы в массив:\n");
    add_unique(my_array, 5);
    add_unique(my_array, 3);
    add_unique(my_array, 7);
    add_unique(my_array, 5);  // Дубликат
    add_unique(my_array, 2);
    add_unique(my_array, 8);
    add_unique(my_array, 3);  // Дубликат

    print_array(my_array);
    free_array(my_array);

    printf("\n");

    // Задание 5
    printf("Задание 5: Рекурсивные функции \n");

    int n = 10;
    printf("Сумма первых %d натуральных чисел: %d\n", n, sum_natural(n));
    printf("Число Фибоначчи F(%d) = %d\n", n, fibonacci(n));

    printf("\n");

    // Задание 6
    printf("Задание 6: Функции с переменным числом параметров \n");

    printf("Без макросов:\n");
    print_args_no_macros(5, 0);
    print_args_no_macros(5, 11, 0);

    printf("С макросами:\n");
    print_args_with_macros(5, 0);
    print_args_with_macros(5, 11, 0);
    print_args_with_macros(5, 11, 4, 7, -1, 0);

    printf("\n");

    // Задание 7
    printf(" Задание 7: Возвращение адреса \n");

    int numbers[] = { 5, 3, 8, 1, 9, 2 };
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Исходный массив: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    int* min_addr = find_min_address(numbers, size);
    if (min_addr != NULL) {
        printf("Минимальный элемент: %d (адрес: %p)\n", *min_addr, (void*)min_addr);

        // Меняем минимальный элемент на 0
        *min_addr = 0;

        printf("Массив после изменения: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    printf("\n");
    printf(" Все задания выполнены! \n");

    return 0;}
