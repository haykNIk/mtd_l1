cmake_minimum_required(VERSION 3.16)

# Задание 2 ЛР1: сборка кода лабораторных прошлого семестра.
project(mtd_l1_labs LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS ON)

# ---------------------------------------------------------------------------
# Обязательные (по README) цели
# ---------------------------------------------------------------------------

# 1) бинарник шестой лабораторной
add_executable(lab6 lab6/lab6.c)

# 2) бинарник, соответствующий коду в src/task3.c
add_executable(task3 task3.c)

# ---------------------------------------------------------------------------
# Остальные лабораторные — цели по желанию
# ---------------------------------------------------------------------------
add_executable(lab1 lab1/lab1.c)
add_executable(lab2 lab2/lab2.c)
add_executable(lab3 lab3/lab3.c)
add_executable(lab4 lab4/lab4.c)
add_executable(lab5 lab5/lab5.c)
