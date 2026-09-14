## 5 (штраф). Линтеры

*Линтерами* называют программы статического (т.е. без компиляции и исполнения) анализа потенциальных ошибок кода и/или мест, где он не соответствует стилю кодирования.

Например, в таком коде
```c
int main()
{
    int a; int b = 0; int c;
    b=1;
    a++;
    return 0;
    b++;
}
```
различные линтеры могут заметить следующее:
* в одной строке 3 команды (несоответствие стилю)
* `b=1` следует исправить на `b = 1` (несоответствие стилю)
* `b++` исполняется после `return` и, следовательно, не исполняется никогда
* переменная `c` не используется

Впрочем, последние два замечания вам и компилятор может сделать.

Термин "линтер" восходит к первой программе статической обработки кода, которая была создана в 70х годах для языка Си и называлась "Lint" (англ. "ворс"), - предположительно, создатели подразумевали, что утилита действует как фильтр сушилки для белья ("lint trap"), отлавливая нежелательные маленькие ворсинки.

Большинство линтеров, которые умеют замечать стилистические ошибки, умеют автоматически их исправлять.
Пожалуй, самый мощный линтер для C/C++ - CLang-Tidy, поставляемый вместе с компилятором clang.

В данном задании вам нужно будет работать с линтером `cpplint`, созданного в компании Google.

1. создайте ветку `ci/lint` из текущего состояния ветки `main` 
1. создайте файл `task5.cpp`, в котором написать какой-нибудь простой код наподобие приведённого выше
1. установите линтер [cpplint](https://github.com/cpplint/cpplint) (заметьте, что он написан на Python и может быть установлен через менеджер пакетов pip - `pip install cpplint`, который у Вас на Linux/Mac, скорее всего, уже есть; альтернативный и рекомендуемый вариант - установка через [pipx](https://github.com/pypa/pipx))
1. запустите его команой `cpplint task5.cpp`. У меня получилось следующее:
    ```
    task5.cpp:0:  No copyright message found.  You should have a line: "Copyright [year] <Copyright Owner>"  [legal/copyright] [5]
    task5.cpp:2:  { should almost always be at the end of the previous line  [whitespace/braces] [4]
    task5.cpp:3:  Weird number of spaces at line-start.  Are you using a 2-space indent?  [whitespace/indent] [3]
    task5.cpp:3:  Missing spaces around =  [whitespace/operators] [4]
    task5.cpp:4:  Weird number of spaces at line-start.  Are you using a 2-space indent?  [whitespace/indent] [3]
    task5.cpp:4:  Missing spaces around =  [whitespace/operators] [4]
    Done processing task5.cpp
    Total errors found: 6
    ```
1. создайте файл `CPPLINT.cfg` ([пример](https://github.com/ApolloAuto/apollo/blob/master/CPPLINT.cfg)). В нём отключите те предупреждения cpplint, которые Вам не нравятся (но не все): например, мне не нравится предупреждение про отсутствие копирайта, поэтому я пропишу
    ```ini
    filter=-legal/copyrignt
    ```
1. Исправьте оставшиеся ошибки
1. Добавьте `cpplint` в CI
   1. Прочтите текст задания 2 в ЛР2, если ещё это не сделали, чтобы получить общую информацию о CI GitHub Actions
   1. Добавьте в CI [настройку Python](https://github.com/actions/setup-python) (или установку [pipx](https://github.com/pypa/pipx)) и установку `cpplint`
   1. Добавьте проверку файла `task5.cpp` (других не надо)
1. Откройте Pull Request в `main` и влейте, если CI проходит (если нет, доработайте Ваши изменения и влейте)