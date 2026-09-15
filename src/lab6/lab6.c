#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задание 6.1. Создаем «картотеку» книг (структура Book из ЛР5).
// «Картотека» - это массив структур => нужно такой массив создать.
// Замечание: размер массива придется увеличивать по мере добавления книг

// Пользователь должен иметь возможность выполнять разные действия
// с картотекой => нужно такую возможность ему предоставить:
// это может выглядеть как вывод "меню"
// (перечень возможных действий и соответствующих реакций пользователя), например:
// - Распечатать содержимое картотеки (1)
// - Ввести новую книгу (2)
// - Удалить существующую(ие) (3)
// - Записать текущее содержимое картотеки в файл (4)
// - Считать из файла содержимое в картотеку (5)
// ... // по желанию можно добавить другие опции
// Выход из программы

// для файлового ввода/вывода используйте функции fprintf и fscanf

// Задание 2. Предоставьте пользователю возможность выводить перечень книг
// в определенном порядке - напишите функцию (функции) сортировки массива
// по любому из полей структуры.
// Замечание: признак "по какому полю сортируем" можно ввести с помощью перечисления

// определение структуры книги
struct Book {
  char title[100];   // название книги
  char author[100];  // автор
  int year;          // год издания
  float price;       // цена
  char category[50]; // категория
  int pages;         // количество страниц
};

typedef struct Book Book;

// определение структуры картотеки
typedef struct {
  Book *books;  // указатель на массив книг
  int count;    // текущее количество книг
  int capacity; // вместимость массива
} CardIndex;

// создание картотеки
CardIndex *createCardIndex(int initialCapacity) {
  CardIndex *ci = (CardIndex *)malloc(sizeof(CardIndex));
  ci->books = (Book *)malloc(initialCapacity * sizeof(Book));
  ci->count = 0;
  ci->capacity = initialCapacity;
  return ci;
}

// освобождение памяти картотеки
void freeCardIndex(CardIndex *ci) {
  free(ci->books);
  free(ci);
}

// увеличение вместимости картотеки при необходимости
void resizeCardIndex(CardIndex *ci) {
  int newCapacity = ci->capacity * 2;
  Book *newBooks = (Book *)realloc(ci->books, newCapacity * sizeof(Book));
  if (newBooks == NULL) {
    printf("Error allocating memory\n"); // ошибка выделения памяти
    return;
  }
  ci->books = newBooks;
  ci->capacity = newCapacity;
  printf("Catalog resized to %d books\n", ci->capacity); // картотека расширена до ... книг
}

// вывод информации об одной книге
void printBook(const Book *book) {
  printf("Title:     %s\n", book->title);
  printf("Author:    %s\n", book->author);
  printf("Year:      %d\n", book->year);
  printf("Price:     $%.2f\n", book->price);
  printf("Category:  %s\n", book->category);
  printf("Pages:     %d\n", book->pages);
  printf("--------------------------\n");
}

// вывод всех книг картотеки
void printAllBooks(CardIndex *ci) {
  if (ci->count == 0) {
    printf("Catalog is empty\n"); // картотека пуста
    return;
  }

  printf("Books in catalog: %d\n", ci->count); // количество книг в картотеке
  for (int i = 0; i < ci->count; i++) {
    printf("Book %d:\n", i + 1); // номер книги
    printBook(&ci->books[i]);
  }
}

// добавление новой книги
void addBook(CardIndex *ci) {
  if (ci->count >= ci->capacity) {
    resizeCardIndex(ci);
  }

  Book *newBook = &ci->books[ci->count];

  printf("Adding new book\n"); // добавление новой книги

  printf("Enter title: "); // ввод названия
  scanf(" %[^\n]", newBook->title);

  printf("Enter author: "); // ввод автора
  scanf(" %[^\n]", newBook->author);

  printf("Enter publication year: "); // ввод года издания
  scanf("%d", &newBook->year);

  printf("Enter price: $"); // ввод цены
  scanf("%f", &newBook->price);

  printf("Enter category: "); // ввод категории
  scanf(" %[^\n]", newBook->category);

  printf("Enter number of pages: "); // ввод количества страниц
  scanf("%d", &newBook->pages);

  ci->count++;
  printf("Book added successfully\n"); // книга успешно добавлена
}

// удаление книги
void deleteBook(CardIndex *ci) {
  if (ci->count == 0) {
    printf("Catalog is empty\n"); // картотека пуста
    return;
  }

  printAllBooks(ci);

  int index;
  printf("Enter book number to delete (1-%d): ", ci->count); // ввод номера книги для удаления
  scanf("%d", &index);

  if (index < 1 || index > ci->count) {
    printf("Invalid number\n"); // неверный номер
    return;
  }

  // сдвигаем книги после удалённой позиции вперёд
  for (int i = index - 1; i < ci->count - 1; i++) {
    ci->books[i] = ci->books[i + 1];
  }

  ci->count--;
  printf("Book deleted\n"); // книга удалена
}

// перечисление полей сортировки
typedef enum { SORT_BY_TITLE, SORT_BY_AUTHOR, SORT_BY_YEAR, SORT_BY_PRICE, SORT_BY_CATEGORY, SORT_BY_PAGES } SortField;

// функция сравнения по названию
int compareByTitle(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return strcmp(bookA->title, bookB->title);
}

// функция сравнения по автору
int compareByAuthor(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return strcmp(bookA->author, bookB->author);
}

// функция сравнения по году
int compareByYear(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return bookA->year - bookB->year;
}

// функция сравнения по цене
int compareByPrice(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return (bookA->price > bookB->price) - (bookA->price < bookB->price);
}

// функция сравнения по категории
int compareByCategory(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return strcmp(bookA->category, bookB->category);
}

// функция сравнения по количеству страниц
int compareByPages(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return bookA->pages - bookB->pages;
}

// сортировка книг
void sortBooks(CardIndex *ci) {
  if (ci->count < 2) {
    printf("Not enough books to sort\n"); // недостаточно книг для сортировки
    return;
  }

  printf("Choose field to sort by:\n"); // выбор поля сортировки
  printf("1. By title\n");              // 1. по названию
  printf("2. By author\n");             // 2. по автору
  printf("3. By year\n");               // 3. по году
  printf("4. By price\n");              // 4. по цене
  printf("5. By category\n");           // 5. по категории
  printf("6. By pages\n");              // 6. по количеству страниц

  int choice;
  scanf("%d", &choice);

  int (*compareFunc)(const void *, const void *);

  switch (choice) {
  case 1: compareFunc = compareByTitle;    break;
  case 2: compareFunc = compareByAuthor;   break;
  case 3: compareFunc = compareByYear;     break;
  case 4: compareFunc = compareByPrice;    break;
  case 5: compareFunc = compareByCategory; break;
  case 6: compareFunc = compareByPages;    break;
  default:
    printf("Invalid choice\n"); // неверный выбор
    return;
  }

  qsort(ci->books, ci->count, sizeof(Book), compareFunc);
  printf("Catalog sorted\n"); // картотека отсортирована
}

// сохранение в файл
void saveToFile(CardIndex *ci) {
  FILE *file = fopen("books.txt", "w");
  if (file == NULL) {
    printf("Error opening file\n"); // ошибка открытия файла
    return;
  }

  fprintf(file, "%d\n", ci->count); // запись количества книг
  for (int i = 0; i < ci->count; i++) {
    Book *book = &ci->books[i];
    fprintf(file, "%s\n", book->title);    // запись названия
    fprintf(file, "%s\n", book->author);   // запись автора
    fprintf(file, "%d\n", book->year);     // запись года
    fprintf(file, "%.2f\n", book->price);  // запись цены
    fprintf(file, "%s\n", book->category); // запись категории
    fprintf(file, "%d\n", book->pages);    // запись количества страниц
  }

  fclose(file);
  printf("Data saved to books.txt\n"); // данные сохранены в файл
}

// загрузка из файла
void loadFromFile(CardIndex *ci) {
  FILE *file = fopen("books.txt", "r");
  if (file == NULL) {
    printf("File not found\n"); // файл не найден
    return;
  }

  int count;
  fscanf(file, "%d\n", &count); // чтение количества книг

  for (int i = 0; i < count; i++) {
    if (ci->count >= ci->capacity) {
      resizeCardIndex(ci);
    }

    Book *book = &ci->books[ci->count];

    fscanf(file, " %[^\n]\n", book->title);    // чтение названия
    fscanf(file, " %[^\n]\n", book->author);   // чтение автора
    fscanf(file, "%d\n", &book->year);         // чтение года
    fscanf(file, "%f\n", &book->price);        // чтение цены
    fscanf(file, " %[^\n]\n", book->category); // чтение категории
    fscanf(file, "%d\n", &book->pages);        // чтение количества страниц

    ci->count++;
  }

  fclose(file);
  printf("Loaded %d books from file\n", count); // из файла загружено ... книг
}

// вывод меню
void showMenu() {
  printf("\nLibrary Catalog Menu\n"); // меню картотеки книг
  printf("1. Show all books\n");      // 1. показать все книги
  printf("2. Add new book\n");        // 2. добавить новую книгу
  printf("3. Delete book\n");         // 3. удалить книгу
  printf("4. Save to file\n");        // 4. сохранить в файл
  printf("5. Load from file\n");      // 5. загрузить из файла
  printf("6. Sort books\n");          // 6. отсортировать книги
  printf("0. Exit program\n");        // 0. выход из программы
  printf("Choose action: ");          // выбор действия
}

int main() {
  printf("Library Catalog System\n"); // система картотеки книг

  CardIndex *cardIndex = createCardIndex(10);

  int choice;
  do {
    showMenu();
    scanf("%d", &choice);
    switch (choice) {
    case 1: printAllBooks(cardIndex);    break;
    case 2: addBook(cardIndex);          break;
    case 3: deleteBook(cardIndex);       break;
    case 4: saveToFile(cardIndex);       break;
    case 5: loadFromFile(cardIndex);     break;
    case 6: sortBooks(cardIndex);        break;
    case 0: printf("Exiting program\n"); break; // выход из программы
    default: printf("Invalid choice\n");        // неверный выбор
    }
  } while (choice != 0);

  freeCardIndex(cardIndex);

  return 0;
}
