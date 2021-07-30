# Описание:
Данный репозиторий содержит файлы с лабораторными работами второго модуля.

# Варианты лабораторных работ:
Лабораторная работа №1: 2, 3, 9  
Лабораторная работа №2: 5, 3, 12  
Лабораторная работа №3: 2  
Лабораторная работа №4: 2, 13, 10  

# Содержание репозитория:

## Лабораторная работа №1

### Задание 1

В строке найти последовательности цифр, каждую из них считать числом в той системе счисления, которая соответствует __первой цифре__, привести найденные числа к десятичной СС. Пример: aaa2010101bbb8343ccc – двоичная и восьмиричная системы счисления.

Файл с выполненным заданием: [lw1.2.c](https://github.com/VolkovYury/Eltex.module2/blob/90795e5582e41263f2b0d9aa4b2958ac8747e469/lw1.2.c)

### Задание 2

Дано число и его система счисления. Орагнизовать систему, которая будет преобразовывать исходное число в число других систем счисления.

Файл с выполненным заданием: [lw1.3.c](https://github.com/VolkovYury/Eltex.module2/blob/abeb348da3576d0d5ec0d73eee3a4033f34b12ea/lw1.3.c)

### Задание 3

"Перевернуть" в строке все слова. (Например: "Жили были дед и баба" - "илиЖ илиб дед и абаб"). Удалить слова – палинандромы.

Файл с выполненным заданием: [lw1.9.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/lw1.9.c)

## Лабораторная работа №2

### Задание 1

Функция получает строку, находит самый внутренний фрагмент в скобках и вырезает его. Операция повторяется до тех пор, пока не останется скобок. Полученные фрагменты и остаток строки вернуть в динамическом массиве указателей.

Файл с выполненным заданием: [lw2.3.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/lw2.3.c)

### Задание 2

Функция находит в строке пары фрагментов, содержащих последовательность одинаковых символов длиной более 3 (кроме пробела) и возвращает динамический массив указателей на копии таких фрагментов.

Файл с выполненным заданием: [lw2.5.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/lw2.5.c)

### Задание 3

Функция находит в строке фрагменты, симметричные относительно центрального символа, длиной 7 и более символов (например, "abcdcba") и возвращает динамический массив указателей на копии таких фрагментов.

Файл с выполненным заданием: [lw2.12.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/lw2.12.c)

## Лабораторная работа №3

### Задание 1

Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. В перечень функций входят:
- ввод записи таблицы с клавиатуры;
- загрузка и сохранение  таблицы в текстовом файле;
- просмотр таблицы;
- сортировка таблицы в порядке возрастания заданного поля;
- поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
- удаление записи;
- изменение(редактирование) записи;
- вычисление с проверкой и использованием всех pfgbctq по заданному условию и формуле(например, общая сумма на всех счетах).

Вариант 2: Перечень полей структурированной переменной: Номер страницы, номер строки, текст изменения строки, дата изменения.

Файл с выполненным заданием: [lw3.2.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/lw3.2.c)

## Дополнительные файлы

### Задание 1

Реалзиация программы для расчёта вариантов для лабораторных работ. Данная программа берёт необходимое количество первых букв фамилии, переводит каждый символы в ascii-код и делит с остатком на возможное количество вариантов. Результат - необходимый вариант работы. Если деление с остатком возвращет 0, то берётся результат целочисленного деления без остатка.

Файл с выполненным заданием: [matrix.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/matrix.c)

### Задание 2

Решение задачи о наполнении рюкзака. Вариант с использованием жадного алгоритма

Файл с выполненным заданием: [FractionalKnapsack.c](https://github.com/VolkovYury/Eltex.module2/blob/8897b4723ad5aa022938edf5e49be3c592d3aebf/FractionalKnapsack.c)

### Задание 3

Реализация протокола Диффи — Хеллмана

Файл с выполненным заданием: [Diffie-Hellman.c](https://github.com/VolkovYury/Eltex.module2/blob/d0a4bb7bb1cb572619ecc8e1ff34e05fa8d2ec16/Diffie%E2%80%93Hellman.c)
