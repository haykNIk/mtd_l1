/*
 * Лабораторная работа №4.
 * Работа со строками и символами.
 * Подсчёт слов, символов и строк во введённом тексте.
 */

#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 4096

int main(void)
{
    char text[MAX_LEN];
    int c;
    int len = 0;
    int words = 0;
    int lines = 1;
    int inWord = 0;

    printf("Введите текст, завершите ввод сочетанием Ctrl+Z (Windows) / Ctrl+D:\n");

    while ((c = getchar()) != EOF && len < MAX_LEN - 1) {
        text[len++] = (char)c;

        if (c == '\n')
            ++lines;

        if (isspace(c)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            ++words;
        }
    }
    text[len] = '\0';

    printf("\n--- Итог ---\n");
    printf("Символов: %d\n", len);
    printf("Слов:     %d\n", words);
    printf("Строк:    %d\n", lines);

    return 0;
}
