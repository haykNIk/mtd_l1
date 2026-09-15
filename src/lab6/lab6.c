#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задание 6.1. Создаем «картотеку» книг (структура Book из ЛР5).
// «Картотека» - это массив структур => нужно такой массив создать.
// Замечание: размер массива придется увеличивать по мере добавления книг
// 任务6.1. 创建图书“卡片索引”（来自Lab5的Book结构）。
// “卡片索引”是一个结构数组 => 需要创建这样一个数组。
// 注意：数组的大小将随着书籍的添加而增加。

// Пользователь должен иметь возможность выполнять разные действия
// с картотекой => нужно такую возможность ему предоставить:
// это может выглядеть как вывод "меню"
// (перечень возможных действий и соответствующих реакций пользователя), например:
// 用户应该能够对卡片索引执行不同的操作 => 需要提供这样的可能性：
// 这可以显示为“菜单”输出（可能操作列表及用户的相应反应），例如：
// - Распечатать содержимое картотеки (1)
//   打印卡片索引的内容
// - Ввести новую книгу (2)
//   输入新书
// - Удалить существующую(ие) (3)
//   删除现有书籍
// - Записать текущее содержимое картотеки в файл (4)
//   将卡片索引的当前内容写入文件
// - Считать из файла содержимое в картотеку (5)
//   从文件中读取内容到卡片索引
// ... // по желанию можно добавить другие опции | 按需新增
// Выход из программы | 退出程序

// для файлового ввода/вывода используйте функции fprintf и fscanf
// 对于文件输入/输出，使用fprintf和fscanf函数

// Задание 2. Предоставьте пользователю возможность выводить перечень книг
// в определенном порядке - напишите функцию (функции) сортировки массива
// по любому из полей структуры.
// Замечание: признак "по какому полю сортируем" можно ввести с помощью перечисления

// 任务2. 让用户能够按特定顺序输出书籍列表 ---
// 编写一个（或多个）根据结构的任何字段对数组进行排序的函数。
// 注意：可以通过枚举输入“按哪个字段排序”的标志。

// 定义书籍结构体 / Define the Book structure
struct Book {
  char title[100];   // 书名 / Title
  char author[100];  // 作者 / Author
  int year;          // 出版年份 / Publication year
  float price;       // 价格 / Price
  char category[50]; // 类别 / Category
  int pages;         // 页数 / Number of pages
};

typedef struct Book Book;

// 定义图书目录结构体 / Define the library catalog structure
typedef struct {
  Book *books;  // 指向书籍数组的指针 / Pointer to array of books
  int count;    // 当前书籍数量 / Current number of books
  int capacity; // 数组容量 / Array capacity
} CardIndex;

// 创建图书目录 / Create library catalog
CardIndex *createCardIndex(int initialCapacity) {
  CardIndex *ci = (CardIndex *)malloc(sizeof(CardIndex));
  ci->books = (Book *)malloc(initialCapacity * sizeof(Book));
  ci->count = 0;
  ci->capacity = initialCapacity;
  return ci;
}

// 释放图书目录内存 / Free memory allocated for catalog
void freeCardIndex(CardIndex *ci) {
  free(ci->books);
  free(ci);
}

// 扩展图书目录容量 / Resize the catalog when needed
void resizeCardIndex(CardIndex *ci) {
  int newCapacity = ci->capacity * 2;
  Book *newBooks = (Book *)realloc(ci->books, newCapacity * sizeof(Book));
  if (newBooks == NULL) {
    printf("Error allocating memory\n"); // 内存分配错误 / Memory allocation error
    return;
  }
  ci->books = newBooks;
  ci->capacity = newCapacity;
  printf("Catalog resized to %d books\n", ci->capacity); // 目录已扩展到...本书 / Catalog expanded to ... books
}

// 打印单本书信息 / Print details of a single book
void printBook(const Book *book) {
  printf("Title:     %s\n", book->title);
  printf("Author:    %s\n", book->author);
  printf("Year:      %d\n", book->year);
  printf("Price:     $%.2f\n", book->price);
  printf("Category:  %s\n", book->category);
  printf("Pages:     %d\n", book->pages);
  printf("--------------------------\n");
}

// 打印所有书籍 / Print all books in the catalog
void printAllBooks(CardIndex *ci) {
  if (ci->count == 0) {
    printf("Catalog is empty\n"); // 目录为空 / Catalog is empty
    return;
  }

  printf("Books in catalog: %d\n", ci->count); // 目录中的书籍数量 / Number of books in catalog
  for (int i = 0; i < ci->count; i++) {
    printf("Book %d:\n", i + 1); // 书籍编号 / Book number
    printBook(&ci->books[i]);
  }
}

// 添加新书 / Add a new book
void addBook(CardIndex *ci) {
  if (ci->count >= ci->capacity) {
    resizeCardIndex(ci);
  }

  Book *newBook = &ci->books[ci->count];

  printf("Adding new book\n"); // 添加新书 / Adding new book

  printf("Enter title: "); // 输入书名 / Enter title
  scanf(" %[^\n]", newBook->title);

  printf("Enter author: "); // 输入作者 / Enter author
  scanf(" %[^\n]", newBook->author);

  printf("Enter publication year: "); // 输入出版年份 / Enter publication year
  scanf("%d", &newBook->year);

  printf("Enter price: $"); // 输入价格 / Enter price
  scanf("%f", &newBook->price);

  printf("Enter category: "); // 输入类别 / Enter category
  scanf(" %[^\n]", newBook->category);

  printf("Enter number of pages: "); // 输入页数 / Enter number of pages
  scanf("%d", &newBook->pages);

  ci->count++;
  printf("Book added successfully\n"); // 书籍添加成功 / Book added successfully
}

// 删除书籍 / Delete a book
void deleteBook(CardIndex *ci) {
  if (ci->count == 0) {
    printf("Catalog is empty\n"); // 目录为空 / Catalog is empty
    return;
  }

  printAllBooks(ci);

  int index;
  printf("Enter book number to delete (1-%d): ", ci->count); // 输入要删除的书籍编号 / Enter book number to delete
  scanf("%d", &index);

  if (index < 1 || index > ci->count) {
    printf("Invalid number\n"); // 编号无效 / Invalid number
    return;
  }

  // 将删除位置之后的书籍向前移动 / Move books after the deleted position forward
  for (int i = index - 1; i < ci->count - 1; i++) {
    ci->books[i] = ci->books[i + 1];
  }

  ci->count--;
  printf("Book deleted\n"); // 书籍已删除 / Book deleted
}

// 排序字段枚举 / Enum for sorting fields
typedef enum { SORT_BY_TITLE, SORT_BY_AUTHOR, SORT_BY_YEAR, SORT_BY_PRICE, SORT_BY_CATEGORY, SORT_BY_PAGES } SortField;

// 按标题比较函数 / Compare function for title
int compareByTitle(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return strcmp(bookA->title, bookB->title);
}

// 按作者比较函数 / Compare function for author
int compareByAuthor(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return strcmp(bookA->author, bookB->author);
}

// 按年份比较函数 / Compare function for year
int compareByYear(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return bookA->year - bookB->year;
}

// 按价格比较函数 / Compare function for price
int compareByPrice(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return (bookA->price > bookB->price) - (bookA->price < bookB->price);
}

// 按类别比较函数 / Compare function for category
int compareByCategory(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return strcmp(bookA->category, bookB->category);
}

// 按页数比较函数 / Compare function for pages
int compareByPages(const void *a, const void *b) {
  const Book *bookA = (const Book *)a;
  const Book *bookB = (const Book *)b;
  return bookA->pages - bookB->pages;
}

// 排序书籍 / Sort books
void sortBooks(CardIndex *ci) {
  if (ci->count < 2) {
    printf("Not enough books to sort\n"); // 书籍不足无法排序 / Not enough books to sort
    return;
  }

  printf("Choose field to sort by:\n"); // 选择排序字段 / Choose field to sort by
  printf("1. By title\n");              // 1. 按标题 / By title
  printf("2. By author\n");             // 2. 按作者 / By author
  printf("3. By year\n");               // 3. 按年份 / By year
  printf("4. By price\n");              // 4. 按价格 / By price
  printf("5. By category\n");           // 5. 按类别 / By category
  printf("6. By pages\n");              // 6. 按页数 / By pages

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
    printf("Invalid choice\n"); // 选择无效 / Invalid choice
    return;
  }

  qsort(ci->books, ci->count, sizeof(Book), compareFunc);
  printf("Catalog sorted\n"); // 目录已排序 / Catalog sorted
}

// 保存到文件 / Save to file
void saveToFile(CardIndex *ci) {
  FILE *file = fopen("books.txt", "w");
  if (file == NULL) {
    printf("Error opening file\n"); // 打开文件错误 / Error opening file
    return;
  }

  fprintf(file, "%d\n", ci->count); // 写入书籍数量 / Write number of books
  for (int i = 0; i < ci->count; i++) {
    Book *book = &ci->books[i];
    fprintf(file, "%s\n", book->title);    // 写入标题 / Write title
    fprintf(file, "%s\n", book->author);   // 写入作者 / Write author
    fprintf(file, "%d\n", book->year);     // 写入年份 / Write year
    fprintf(file, "%.2f\n", book->price);  // 写入价格 / Write price
    fprintf(file, "%s\n", book->category); // 写入类别 / Write category
    fprintf(file, "%d\n", book->pages);    // 写入页数 / Write pages
  }

  fclose(file);
  printf("Data saved to books.txt\n"); // 数据已保存到文件 / Data saved to file
}

// 从文件加载 / Load from file
void loadFromFile(CardIndex *ci) {
  FILE *file = fopen("books.txt", "r");
  if (file == NULL) {
    printf("File not found\n"); // 文件未找到 / File not found
    return;
  }

  int count;
  fscanf(file, "%d\n", &count); // 读取书籍数量 / Read number of books

  for (int i = 0; i < count; i++) {
    if (ci->count >= ci->capacity) {
      resizeCardIndex(ci);
    }

    Book *book = &ci->books[ci->count];

    fscanf(file, " %[^\n]\n", book->title);    // 读取标题 / Read title
    fscanf(file, " %[^\n]\n", book->author);   // 读取作者 / Read author
    fscanf(file, "%d\n", &book->year);         // 读取年份 / Read year
    fscanf(file, "%f\n", &book->price);        // 读取价格 / Read price
    fscanf(file, " %[^\n]\n", book->category); // 读取类别 / Read category
    fscanf(file, "%d\n", &book->pages);        // 读取页数 / Read pages

    ci->count++;
  }

  fclose(file);
  printf("Loaded %d books from file\n", count); // 已从文件加载...本书 / Loaded ... books from file
}

// 显示菜单 / Show menu
void showMenu() {
  printf("\nLibrary Catalog Menu\n"); // 图书目录菜单 / Library catalog menu
  printf("1. Show all books\n");      // 1. 显示所有书籍 / Show all books
  printf("2. Add new book\n");        // 2. 添加新书 / Add new book
  printf("3. Delete book\n");         // 3. 删除书籍 / Delete book
  printf("4. Save to file\n");        // 4. 保存到文件 / Save to file
  printf("5. Load from file\n");      // 5. 从文件加载 / Load from file
  printf("6. Sort books\n");          // 6. 排序书籍 / Sort books
  printf("0. Exit program\n");        // 0. 退出程序 / Exit program
  printf("Choose action: ");          // 选择操作 / Choose action
}

int main() {
  printf("Library Catalog System\n"); // 图书目录系统 / Library catalog system

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
    case 0: printf("Exiting program\n"); break; // 正在退出程序 / Exiting program
    default: printf("Invalid choice\n");        // 选择无效 / Invalid choice
    }
  } while (choice != 0);

  freeCardIndex(cardIndex);

  return 0;
}
