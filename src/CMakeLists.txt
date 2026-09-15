cmake_minimum_required(VERSION 3.10)

project(mtd_l1 C)

set(CMAKE_C_STANDARD 11)

# Бинарник шестой лабораторной работы
add_executable(lab6
    lab6/lab6.c
)

# Бинарник, соответствующий коду в task3.c (задание на ветвление)
add_executable(task3
    task3.c
)
