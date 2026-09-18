/*
 * @Author: hayknik
 */
// Лабораторная 5.
// - указатели на функции
// - структуры

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Book.h"

// ---------------------------------------------------------------------------
// Задание 1. Указатель на функцию. "Калькулятор"
// Напишите функции:
// 1) sum - принимает два значения типа double и возвращает сумму
// 2) sub - разность
// 3) mul - произведение
// 4) div - результат деления
// 5) возведение в степень - можно воспользоваться pow() из <math.h>
// не забудьте unit-тесты
// ---------------------------------------------------------------------------

double opSum(double a, double b) { return a + b; }
double opSub(double a, double b) { return a - b; }
double opMul(double a, double b) { return a * b; }
double opDiv(double a, double b) { return a / b; }
double opPow(double a, double b) { return pow(a, b); }

// сравнение вещественных чисел с заданной точностью
static int almostEqual(double a, double b)
{
    return fabs(a - b) < 1e-9;
}

// проверка одного теста, возвращает 1, если тест пройден
static int checkOperation(const char *name, double got, double expected)
{
    if (almostEqual(got, expected)) {
        printf("  OK   %s\n", name);
        return 1;
    }
    printf("  FAIL %s: получено %g, ожидалось %g\n", name, got, expected);
    return 0;
}

// unit-тесты для арифметических операций
static void runCalculatorTests(void)
{
    int total = 0;
    int passed = 0;

    printf("Unit-тесты калькулятора:\n");

    total++; passed += checkOperation("sum(2, 3) = 5",        opSum(2.0, 3.0),   5.0);
    total++; passed += checkOperation("sub(2, 3) = -1",       opSub(2.0, 3.0),  -1.0);
    total++; passed += checkOperation("mul(2, 3) = 6",        opMul(2.0, 3.0),   6.0);
    total++; passed += checkOperation("div(6, 3) = 2",        opDiv(6.0, 3.0),   2.0);
    total++; passed += checkOperation("pow(2, 10) = 1024",    opPow(2.0, 10.0), 1024.0);
    total++; passed += checkOperation("sum(-2, 3) = 1",       opSum(-2.0, 3.0),  1.0);
    total++; passed += checkOperation("mul(0, 5) = 0",        opMul(0.0, 5.0),   0.0);
    total++; passed += checkOperation("sub(3, 3) = 0",        opSub(3.0, 3.0),   0.0);

    printf("Пройдено тестов: %d из %d\n", passed, total);
}

// Сделайте интерфейс калькулятора.
// Пока пользователь хочет пользоваться калькулятором,
// он может вводить два значения и знак операции;
// результат выводится на экран.
// Если ввод некорректный, нужно сообщить
// об этом пользователю и продолжить работу
static void runCalculator(void)
{
    printf("\n=== Задание 1. Калькулятор на указателях на функции ===\n");

    runCalculatorTests();

    // массив указателей на функции: выбор операции по индексу
    double (*operations[5])(double, double) = { opSum, opSub, opMul, opDiv, opPow };

    printf("\nДоступные операции: + - * / ^\n");

    char line[128];
    while (1) {
        printf("Введите выражение вида '2 + 3' (q - выход): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        if (line[0] == 'q' || line[0] == 'Q') {
            break;
        }

        double a = 0.0;
        double b = 0.0;
        char op = 0;

        if (sscanf(line, "%lf %c %lf", &a, &op, &b) != 3) {
            printf("Некорректный ввод, попробуйте ещё раз\n");
            continue;
        }

        int index = -1;
        switch (op) {
        case '+': index = 0; break;
        case '-': index = 1; break;
        case '*': index = 2; break;
        case '/': index = 3; break;
        case '^': index = 4; break;
        default:
            printf("Неизвестная операция '%c'\n", op);
            continue;
        }

        if (index == 3 && almostEqual(b, 0.0)) {
            printf("Деление на ноль невозможно\n");
            continue;
        }

        printf("%g %c %g = %g\n", a, op, b, operations[index](a, b));
    }
}

// ---------------------------------------------------------------------------
// Задание 2. Указатель на функцию в качестве аргумента
// 2а. Реализуйте функцию сортировки любых объектов sort,
//     которая принимает следующие параметры:
// 1) указатель на первый сортируемый элемент (void*)
// 2) количество сортируемых элементов
// 3) размер элемента в байтах
// 4) указатель на функцию перестановки элементов, которая принимает на вход
//    два значения типа void*
// 5) указатель на функцию сравнения элементов, которая принимает также
//    два указателя и возвращает short
// ---------------------------------------------------------------------------

typedef void (*SwapFunc)(void *, void *);
typedef short (*CmpFunc)(const void *, const void *);

// обобщённая сортировка методом выбора (по возрастанию)
void sort(void *base, unsigned int count, unsigned int size, SwapFunc swapFunc, CmpFunc cmpFunc)
{
    char *pBase = (char *)base;

    for (unsigned int i = 0; i + 1 < count; i++) {
        unsigned int minIndex = i;
        for (unsigned int j = i + 1; j < count; j++) {
            if (cmpFunc(pBase + j * size, pBase + minIndex * size) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapFunc(pBase + i * size, pBase + minIndex * size);
        }
    }
}

// В качестве примера напишите функцию swapInt перестановки двух целых чисел
// (принимает два указателя на void и меняет значения местами)
// и функцию cmpInt, которая принимает два void указателя и
// возвращает тип short - результат сравнения:
// <0 - первый элемент меньше, чем второй
// =0 - равны
// >0 - первый элемент больше, чем второй

void swapInt(void *a, void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

short cmpInt(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (short)((x > y) - (x < y));
}

// Задание 2б. По аналогии с 8а создайте вспомогательные функции swapDouble
// и cmpDouble. Примените функцию sort для сортировки массива вещественных
// значений.

void swapDouble(void *a, void *b)
{
    double *pa = (double *)a;
    double *pb = (double *)b;
    double temp = *pa;
    *pa = *pb;
    *pb = temp;
}

short cmpDouble(const void *a, const void *b)
{
    double x = *(const double *)a;
    double y = *(const double *)b;
    return (short)((x > y) - (x < y));
}

// Задание 2в. По аналогии с 8а создайте вспомогательные функции - swapStr
// и cmpStr; вызовите функцию Sort для сортировки массива указателей на строки.
// char* arStr[] = {"QQQ", "SDF", "ABC"...};

void swapStr(void *a, void *b)
{
    const char **pa = (const char **)a;
    const char **pb = (const char **)b;
    const char *temp = *pa;
    *pa = *pb;
    *pb = temp;
}

short cmpStr(const void *a, const void *b)
{
    const char *x = *(const char * const *)a;
    const char *y = *(const char * const *)b;
    return (short)strcmp(x, y);
}

static void printIntArray(const int *arr, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

static void printDoubleArray(const double *arr, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        printf("%g", arr[i]);
        if (i < len - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

static void runSortDemo(void)
{
    printf("\n=== Задание 2. Обобщённая сортировка ===\n");

    // 2а. целые числа
    {
        int a[] = {5, 7, 3, -1, 2, 3};
        unsigned int aLen = (unsigned int)(sizeof(a) / sizeof(a[0]));

        printf("Целые числа до сортировки:  ");
        printIntArray(a, aLen);
        sort((void *)a, aLen, (unsigned int)sizeof(int), swapInt, cmpInt);
        printf("Целые числа после сортировки: ");
        printIntArray(a, aLen);
    }

    // 2б. вещественные числа
    {
        double d[] = {3.5, -1.25, 0.0, 2.75, 1.0};
        unsigned int dLen = (unsigned int)(sizeof(d) / sizeof(d[0]));

        printf("Вещественные до сортировки:  ");
        printDoubleArray(d, dLen);
        sort((void *)d, dLen, (unsigned int)sizeof(double), swapDouble, cmpDouble);
        printf("Вещественные после сортировки: ");
        printDoubleArray(d, dLen);
    }

    // 2в. массив указателей на строки
    {
        const char *arStr[] = {"QQQ", "SDF", "ABC", "hello", "zzz"};
        unsigned int sLen = (unsigned int)(sizeof(arStr) / sizeof(arStr[0]));

        printf("Строки до сортировки:  ");
        for (unsigned int i = 0; i < sLen; i++) {
            printf("%s ", arStr[i]);
        }
        printf("\n");

        sort((void *)arStr, sLen, (unsigned int)sizeof(arStr[0]), swapStr, cmpStr);

        printf("Строки после сортировки: ");
        for (unsigned int i = 0; i < sLen; i++) {
            printf("%s ", arStr[i]);
        }
        printf("\n");
    }
}

// ---------------------------------------------------------------------------
// Задание 3. Массивы указателей на функцию
// Напишите несколько функций вида
// - `const char* getString();`
// - `const char* getAnotherString();`
// и так далее
// каждая из функций возвращает указатель на некоторую строку
// (подумайте, какой адрес Вы имеете право возвращать из функции)
//
// Объявите и проинициализируйте массив указателей на функции.
// Вызовите различные функции из массива
// ---------------------------------------------------------------------------

// Возвращать можно адрес объекта со статической продолжительностью жизни:
// строковый литерал живёт всю программу, а адрес локального массива —
// недействителен после выхода из функции.

const char *getString(void) { return "Hello"; }
const char *getAnotherString(void) { return "World"; }
const char *getLabName(void) { return "Modern technologies in development"; }
const char *getAuthor(void) { return "hayknik"; }

static void runFunctionPointerArray(void)
{
    printf("\n=== Задание 3. Массив указателей на функции ===\n");

    const char *(*getters[])(void) = { getString, getAnotherString, getLabName, getAuthor };
    unsigned int count = (unsigned int)(sizeof(getters) / sizeof(getters[0]));

    for (unsigned int i = 0; i < count; i++) {
        printf("%u: %s\n", i, getters[i]());
    }
}

// ---------------------------------------------------------------------------
// Задание 4. Структуры
// Задание 4a. Объявите структуру Book, описывающую книгу
// (автор, заглавие, год издания, цена, категория…).
// Подумайте, какого типа могут быть поля структуры.
// Объявление структуры рекомендуется выносить в заголовочный файл.
//
// Задание 4б. Создайте разными способами (статический, динамический)
// экземпляры (объекты) типа Book
//
// Задание 4в. Заполните поля созданных объектов.
// Напоминание: в строках нужна "защита" от выхода за границы массива.
//
// Задание 4г. Напишите функцию, выводящую на экран реквизиты книги.
// Подумайте, как эффективнее передавать экземпляр Book в функцию.
// ---------------------------------------------------------------------------

// копирование строки с защитой от выхода за границы массива
static void setText(char *dst, size_t dstSize, const char *src)
{
    snprintf(dst, dstSize, "%s", src);
}

// вывод реквизитов книги (объявлена в Book.h)
void printBook(const Book *book)
{
    printf("  Заглавие:  %s\n", book->title);
    printf("  Автор:     %s\n", book->author);
    printf("  Год:       %d\n", book->year);
    printf("  Цена:      %.2f\n", book->price);
    printf("  Категория: %s\n", book->category);
}

static void runBookDemo(void)
{
    printf("\n=== Задание 4. Структуры ===\n");

    // 4б. статический экземпляр
    Book staticBook;
    setText(staticBook.title, BOOK_TITLE_LEN, "Преступление и наказание");
    setText(staticBook.author, BOOK_AUTHOR_LEN, "Ф. М. Достоевский");
    staticBook.year = 1866;
    staticBook.price = 750.50;
    setText(staticBook.category, BOOK_CATEGORY_LEN, "Роман");

    // 4б. динамический экземпляр
    Book *pDynamicBook = (Book *)malloc(sizeof(Book));
    if (pDynamicBook == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    setText(pDynamicBook->title, BOOK_TITLE_LEN, "Мастер и Маргарита");
    setText(pDynamicBook->author, BOOK_AUTHOR_LEN, "М. А. Булгаков");
    pDynamicBook->year = 1967;
    pDynamicBook->price = 890.00;
    setText(pDynamicBook->category, BOOK_CATEGORY_LEN, "Роман");

    // 4г. вывод: экземпляр передаётся по указателю
    printf("Статический экземпляр:\n");
    printBook(&staticBook);
    printf("Динамический экземпляр:\n");
    printBook(pDynamicBook);

    free(pDynamicBook);
}

int main()
{
    runCalculator();
    runSortDemo();
    runFunctionPointerArray();
    runBookDemo();

    return 0;
}
