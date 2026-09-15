/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2026-01-08 15:11:23
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2026-01-11 20:24:28
 * @FilePath: \АиП\lab2_part4\lab2_part2.c
 * @Description: настройка по умолчанию; задайте `customMade`, откройте koroFileHeader для настройки: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2026-01-08 15:11:23
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2026-01-11 20:24:00
 * @FilePath: \АиП\lab2_part4\lab2_part2.c
 * @Description: настройка по умолчанию; задайте `customMade`, откройте koroFileHeader для настройки: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2026-01-08 15:11:23
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2026-01-11 20:22:57
 * @FilePath: \АиП\lab2_part4\lab2_part2.c
 * @Description: настройка по умолчанию; задайте `customMade`, откройте koroFileHeader для настройки: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
int main() {
  // Задание 5. Арифметика указателей. Операция разыменования указателя.
  // Выполняя задание, следите за изменением значений
  // указателей и значений объектов, на которые они указывают.
  // Интерпретируте наблюдаемые результаты
  {
    int nAr[2] = {1, 3};
    int *pn = &nAr[0];
    pn[0]++; // (*pn)++;
    pn++;

    char cAr[] = {'A', 'B', 'C', 'D'};
    char *pc = &cAr[0];
    pc[1] = pc[0] + 5; // pc[0] += 5; // *(pc + 1) = (*pc) + 5;
    pc = pc + 3;

    double dAr[3] = {1.0, 2.0};
    double *pd1 = &dAr[0];
    double *pd2 = pd1;
    (*pd2) += 2;
    pd2 += 2;

    // Объясните результат выполнения операции вычитания двух указателей
    pd1 = &dAr[0];
    pd2 = &dAr[1];
    int nNumber = pd2 - pd1;
  }

  // Задание 6. Void-указатель.
  // Выполняя задание, посмотрите, какие значения присваиваются
  // void-указателю. Обратите внимание: средствами отладчика
  // нельзя посмотреть значения, на которые "указывает"
  // void-указатель
  {
    void *pVoid;
    int nObject = 5;
    char cObject = 'A';
    int *pInt = &nObject;
    pVoid = &nObject;
    pVoid = &cObject;
    pVoid = pInt;

    // Подумайте, что нужно сделать, чтобы выражение стало корректным
    // pInt = pVoid;
  }

  // Задание 7. Модификатор const. В каждом из заданий
  // объявите указатель требуемого вида
  {
    // 7a. Указатель является константой.

    // 7б. Указываемое значение является константой.

    // 7в. И указатель, и указываемое значение являются константами.
  }

  // Задание 8. Динамическая память
  // Напишите код, который предлагает пользователю ввести число 'n' с
  // клавиатуры после этого пользователю предлагается ввести ещё 'n' чисел
  // (через пробел в одной строке либо последовательно, как удобнее) результат
  // нужно записать в массив и вывести в обратном порядке на экран через
  // пробел Пример входа:
  // 5
  // 1 4 3
  // Вывод: 3 4 1
}
