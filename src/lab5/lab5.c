#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ЗАДАЧА 1: КАЛЬКУЛЯТОР

double sum(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divide(double a, double b) {
    const double EPSILON = 1e-8; // Точность для проверки маленьких чисел

    if (fabs(b) < EPSILON) { // Проверяем, меньше ли модуль знаменателя EPSILON
        printf("Ошибка: деление на ноль или слишком маленькое число!\n");
        return 0;
    }
    return a / b;
}
double power(double a, double b) { return pow(a, b); }

typedef double (*CalcFunc)(double, double);

void test_calculator() {
    printf("Тестирование калькулятора\n");

    CalcFunc funcs[] = { sum, sub, mul, divide, power };
    char* names[] = { "сложение", "вычитание", "умножение", "деление", "степень" };
    double tests[][3] = {
        {10, 5, 15},
        {10, 5, 5},
        {10, 5, 50},
        {10, 5, 2},
        {2, 3, 8},
    };

    for (int i = 0; i < 5; i++) {
        double result = funcs[i](tests[i][0], tests[i][1]);
        printf("%s %.1f и %.1f: ожидалось %.1f, получилось %.1f\n",
            names[i], tests[i][0], tests[i][1], tests[i][2], result);
    }
}

void calculator_interface() {
    printf("Калькулятор\n");
    printf("Доступные операции: + - * / ^\n");

    char choice;
    do {
        double a, b;
        char op;

        printf("Введите выражение (например: 5 + 3): ");
        if (scanf("%lf %c %lf", &a, &op, &b) != 3) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }

        CalcFunc func = NULL;
        switch (op) {
        case '+': func = sum; break;
        case '-': func = sub; break;
        case '*': func = mul; break;
        case '/': func = divide; break;
        case '^': func = power; break;
        default:
            printf("Неизвестная операция\n");
            continue;
        }

        double result = func(a, b);
        printf("Результат: %.2f %c %.2f = %.4f\n", a, op, b, result);

        printf("Продолжить? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
}

// ЗАДАНИЕ 2: ОБОБЩЕННАЯ СОРТИРОВКА

void swapInt(void* a, void* b) {
    int temp = *(int*)a;
    *(int*)a = *(int*)b;
    *(int*)b = temp;
}

short cmpInt(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x < y) ? -1 : (x > y) ? 1 : 0;
}

void swapDouble(void* a, void* b) {
    double temp = *(double*)a;
    *(double*)a = *(double*)b;
    *(double*)b = temp;
}

short cmpDouble(const void* a, const void* b) {
    double x = *(double*)a;
    double y = *(double*)b;
    return (x < y) ? -1 : (x > y) ? 1 : 0;
}

void swapStr(void* a, void* b) {
    char* temp = *(char**)a;
    *(char**)a = *(char**)b;
    *(char**)b = temp;
}

short cmpStr(const void* a, const void* b) {
    const char* s1 = *(const char**)a;
    const char* s2 = *(const char**)b;
    return strcmp(s1, s2);
}

void sort(void* array, int count, size_t size,
    void (*swap)(void*, void*),
    short (*compare)(const void*, const void*)) {

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            void* elem1 = (char*)array + j * size;
            void* elem2 = (char*)array + (j + 1) * size;

            if (compare(elem1, elem2) > 0) {
                swap(elem1, elem2);
            }
        }
    }
}

void test_sorting() {
    printf("Тестирование сортировки\n");

    printf("1. Сортировка целых чисел:\n");
    int intArray[] = { 5, 7, 3, -1, 2, 3, 8, 0 };
    int intCount = sizeof(intArray) / sizeof(intArray[0]);

    printf("До сортировки: ");
    for (int i = 0; i < intCount; i++) printf("%d ", intArray[i]);

    sort(intArray, intCount, sizeof(int), swapInt, cmpInt);

    printf("\nПосле сортировки: ");
    for (int i = 0; i < intCount; i++) printf("%d ", intArray[i]);
    printf("\n");

    printf("\n2. Сортировка вещественных чисел:\n");
    double doubleArray[] = { 3.14, 2.71, 1.41, 0.0, -1.5, 5.5 };
    int doubleCount = sizeof(doubleArray) / sizeof(doubleArray[0]);

    printf("До сортировки: ");
    for (int i = 0; i < doubleCount; i++) printf("%.2f ", doubleArray[i]);

    sort(doubleArray, doubleCount, sizeof(double), swapDouble, cmpDouble);

    printf("\nПосле сортировки: ");
    for (int i = 0; i < doubleCount; i++) printf("%.2f ", doubleArray[i]);
    printf("\n");

    printf("\n3. Сортировка строк:\n");
    char* strArray[] = { "QQQ", "SDF", "ABC", "XYZ", "MNO", "AAA" };
    int strCount = sizeof(strArray) / sizeof(strArray[0]);

    printf("До сортировки: ");
    for (int i = 0; i < strCount; i++) printf("%s ", strArray[i]);

    sort(strArray, strCount, sizeof(char*), swapStr, cmpStr);

    printf("\nПосле сортировки: ");
    for (int i = 0; i < strCount; i++) printf("%s ", strArray[i]);
    printf("\n");
}

// ЗАДАНИЕ 3: МАССИВ УКАЗАТЕЛЕЙ НА ФУНКЦИИ

const char* getString1() {
    return "Первая строка из функции 1";
}

const char* getString2() {
    return "Вторая строка из функции 2";
}

const char* getString3() {
    return "Третья строка из функции 3";
}

const char* getString4() {
    return "Четвертая строка из функции 4";
}

void test_function_array() {
    printf("Тестирование массива указателей на функции\n");

    typedef const char* (*StringFunc)();
    StringFunc functions[] = { getString1, getString2, getString3, getString4 };
    int funcCount = sizeof(functions) / sizeof(functions[0]);

    for (int i = 0; i < funcCount; i++) {
        printf("%d: %s\n", i + 1, functions[i]());
    }

    printf("Демонстрация вызова через отдельный указатель:\n");
    StringFunc myFunc = getString2;
    printf("Вызов через myFunc: %s\n", myFunc());
}

// ЗАДАНИЕ 4: СТРУКТУРЫ

struct Book {
    char title[100];
    char author[100];
    int year;
    float price;
    char category[50];
    int pages;
};

typedef struct Book Book;

void printBook(const Book* book) {
    printf("Информация о книге\n");
    printf("Название:  %s\n", book->title);
    printf("Автор:     %s\n", book->author);
    printf("Год:       %d\n", book->year);
    printf("Цена:      %.2f руб.\n", book->price);
    printf("Категория: %s\n", book->category);
    printf("Страниц:   %d\n", book->pages);
}

void safeCopy(char* dest, const char* src, size_t destSize) {
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}

void test_structures() {
    printf("Тестирование структур\n");

    printf("1. Статическая структура:\n");
    Book staticBook;
    safeCopy(staticBook.title, "Война и мир", sizeof(staticBook.title));
    safeCopy(staticBook.author, "Лев Толстой", sizeof(staticBook.author));
    staticBook.year = 1869;
    staticBook.price = 1500.50;
    safeCopy(staticBook.category, "Роман", sizeof(staticBook.category));
    staticBook.pages = 1225;

    printBook(&staticBook);

    printf("\n2. Динамическая структура:\n");
    Book* dynamicBook = (Book*)malloc(sizeof(Book));
    if (dynamicBook == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    safeCopy(dynamicBook->title, "Преступление и наказание", sizeof(dynamicBook->title));
    safeCopy(dynamicBook->author, "Федор Достоевский", sizeof(dynamicBook->author));
    dynamicBook->year = 1866;
    dynamicBook->price = 1200.75;
    safeCopy(dynamicBook->category, "Роман", sizeof(dynamicBook->category));
    dynamicBook->pages = 672;

    printBook(dynamicBook);

    printf("\n3. Массив структур:\n");
    Book library[3];

    safeCopy(library[0].title, "Мастер и Маргарита", sizeof(library[0].title));
    safeCopy(library[0].author, "Михаил Булгаков", sizeof(library[0].author));
    library[0].year = 1967;
    library[0].price = 950.25;
    safeCopy(library[0].category, "Роман", sizeof(library[0].category));
    library[0].pages = 480;

    safeCopy(library[1].title, "1984", sizeof(library[1].title));
    safeCopy(library[1].author, "Джордж Оруэлл", sizeof(library[1].author));
    library[1].year = 1949;
    library[1].price = 850.00;
    safeCopy(library[1].category, "Антиутопия", sizeof(library[1].category));
    library[1].pages = 328;

    for (int i = 0; i < 2; i++) {
        printf("Книга %d: %s\n", i + 1, library[i].title);
    }

    free(dynamicBook);
}

int main() {
    printf("Лабораторная работа 5\n");
    printf("Указатели на функции и структуры\n\n");

    test_calculator();
    calculator_interface();

    test_sorting();

    test_function_array();

    test_structures();

    printf("Все задания выполнены\n");
    return 0;
}