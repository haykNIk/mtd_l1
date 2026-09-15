/*
 * Лабораторная работа №6.
 * Структуры и динамическая память.
 * Односвязный список записей: добавление, вывод, поиск, освобождение.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[64];
    int  value;
    struct Node *next;
} Node;

static Node *list_push(Node *head, const char *name, int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Ошибка выделения памяти\n");
        return head;
    }

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';
    node->value = value;
    node->next = head;

    return node;
}

static void list_print(const Node *head)
{
    const Node *cur = head;
    int index = 0;

    if (cur == NULL) {
        printf("Список пуст\n");
        return;
    }

    while (cur != NULL) {
        printf("%2d. %-20s %d\n", index++, cur->name, cur->value);
        cur = cur->next;
    }
}

static const Node *list_find(const Node *head, const char *name)
{
    const Node *cur = head;

    while (cur != NULL) {
        if (strcmp(cur->name, name) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

static void list_free(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Node *head = NULL;

    head = list_push(head, "Иванов", 85);
    head = list_push(head, "Петров", 91);
    head = list_push(head, "Сидоров", 78);

    printf("Список записей:\n");
    list_print(head);

    const char *query = "Петров";
    const Node *found = list_find(head, query);

    if (found != NULL)
        printf("\nНайдено: %s -> %d\n", found->name, found->value);
    else
        printf("\nЗапись \"%s\" не найдена\n", query);

    list_free(head);
    return 0;
}
