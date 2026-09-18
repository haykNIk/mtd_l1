/*
 * @Author: hayknik
 */
#pragma once

// максимальные длины строковых полей структуры
#define BOOK_TITLE_LEN 100
#define BOOK_AUTHOR_LEN 100
#define BOOK_CATEGORY_LEN 50

// структура, описывающая книгу
typedef struct Book {
    char title[BOOK_TITLE_LEN];       // заглавие
    char author[BOOK_AUTHOR_LEN];     // автор
    int year;                         // год издания
    double price;                     // цена
    char category[BOOK_CATEGORY_LEN]; // категория
} Book;

// вывод реквизитов книги на экран.
// Экземпляр передаётся по указателю: структура большая, копировать её дорого.
void printBook(const Book *book);
