// Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. В перечень функций входят:
// • ввод записи таблицы с клавиатуры;
// • загрузка и сохранение  таблицы в текстовом файле;
// • просмотр таблицы;
// • сортировка таблицы в порядке возрастания заданного поля;
// • поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
// • удаление записи;
// • изменение(редактирование) записи;
// • вычисление с проверкой и использованием всех pfgbctq по заданному условию и формуле(например, общая сумма на всех счетах).

// Вариант 2: Перечень полей структурированной переменной: Номер страницы, номер строки, текст изменения строки, дата изменения.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 100             // максимальный размер массива структур

typedef struct {
    int yyyy;
    int mm;
    int dd;
} date;

typedef struct {
    int pageNumber;
    int lineNumber;
    char changeText[101];
    date date;
} changingString ;


void printMenu();
void addNote(changingString* arr, int* counter);
void loadData(changingString* arr, int* counter);
void readStr(char* str, changingString* arr, int *counter);
void saveData(changingString* arr, int counter);
void printArr(changingString* arr, int counter);
void sortArrayAsc(changingString* arr, int counter);
// место для функции 6
void delNoteInArray(changingString* arr, int* counter);
void changeNodeInArray(changingString* arr, int counter);

int main()
{
    char* locale = setlocale(LC_ALL, "");
    
    changingString arrayData[MAXSIZE];
    int counter = 2;

    arrayData[0].pageNumber = 50;
    arrayData[0].lineNumber = 999;
    strcpy_s(arrayData[0].changeText, 100, "123465798012346579801234657980123465798012346579801234657980123465798012346579801234657980123465798\0");
    arrayData[0].date.dd = 23;
    arrayData[0].date.mm = 04;
    arrayData[0].date.yyyy = 1997;

    arrayData[1].pageNumber = 999;
    arrayData[1].lineNumber = 1;
    strcpy_s(arrayData[1].changeText, 100, "123465798\0");
    arrayData[1].date.dd = 1;
    arrayData[1].date.mm = 4;
    arrayData[1].date.yyyy = 12;

    
    int menu = 0;
    printMenu();

    while (true) {
        printf("----Предыдущая операция завершена----\n");
        printf("Для повторного вызова меню введите '0'\n");
        printf("Введите номер пункта:");
        scanf_s("%d", &menu);

        switch (menu) {
        case 1:
            addNote(&arrayData, &counter);
            break;
        case 2:
            loadData(&arrayData, &counter);
            break;
        case 3:
            saveData(&arrayData, counter);
            break;
        case 4:
            printArr(&arrayData, counter);
            break;
        case 5:
            sortArrayAsc(&arrayData, counter);
            break;
        case 6:
            printf(">>>>>>>>>>На данный момент функция находится в разработке<<<<<<<<<<\n");
            break;
        case 7:
            delNoteInArray(&arrayData, &counter);
            break;
        case 8:
            changeNodeInArray(&arrayData, counter);
            break;
        case 9:
            printf("Выход из программы...\n");
            return 0;
        case 0:
            printMenu();
            break;
        default:
            printf("Введены некорректные значения. Введите целое число от 1 до 9 включительно\n");
        }
    }
    return 0;
}

// 0. печать меню
void printMenu() {
    char lineHor[111] = "--------------------------------------------------------------------------------------------------------------\0";
    printf("%s\n", lineHor);
    printf("Выберите необходимую опцию: \n");
    printf("1. Ввод записи с клавиатуры\n");
    printf("2. Загрузка таблицы из .txt\n");
    printf("3. Сохранение таблицы в .txt\n");
    printf("4. Просмотр содержимого таблицы\n");
    printf("5. Сортировка таблицы в порядке возрастания\n");
    printf("6. Поиск в таблице элемента с заданным значением поля\n");
    printf("7. Удаление записи\n");
    printf("8. Изменение/редактирование записи\n");
    printf("9. Выход\n");
    printf("%s\n", lineHor);
}

// 1. Ввод записи с клавиатуры. Важное замечание: множество проверок опущены ввиду особенностей работы со scanf_s. Пока не разобрался как устранить
void addNote(changingString* arr, int* counter) {
    printf("Ввод данных:\n");

    
    while (true) {
        int page = -1;
        
        if (page == -1) {
            printf("Введите номер страницы (целое число от 0 до 9999 включительно):");      // При вводе символов будет бесконечный цикл. Исправить пока не смог
            scanf_s("%d", &page);                                                           // if - задел на будущее для исправления ошибки с бесконечным циклом
        }

        if (page < 0 || page > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", page);
            arr[*counter].pageNumber = page;
            break;
        }
    }

    while (true) {
        int line = -1;

        if (line == -1) {
            printf("Введите номер cтроки (целое число от 0 до 9999 включительно):");      // При вводе символов будет бесконечный цикл. Исправить пока не смог
            scanf_s("%d", &line);                                                         // if - задел на будущее для исправления ошибки с бесконечным циклом
        }

        if (line < 0 || line > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", line);
            arr[*counter].lineNumber = line;
            break;
        }
    }

    while (true) {
        char text[101];

        printf("Введите текст (ограничено 100 символами):");      // Проверок нет. Разделители не вводить
        scanf_s("%100s", text, 100);

        printf("Введены корректные данные: %s\n", text);
        strcpy_s(arr[*counter].changeText, 100, text);
        break;
    }

    while (true) {
        int day = -1;

        if (day == -1) {
            printf("Введите день редактирования (целое число от 1 до 31 включительно):");      // При вводе символов будет бесконечный цикл. Исправить пока не смог
            scanf_s("%d", &day);                                                               // if - задел на будущее для исправления ошибки с бесконечным циклом
        }

        if (day < 1 || day > 31) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", day);
            arr[*counter].date.dd = day;
            break;
        }
    }

    while (true) {
        int month = -1;

        if (month == -1) {
            printf("Введите месяц редактирования (целое число от 1 до 12 включительно):");      // При вводе символов будет бесконечный цикл. Исправить пока не смог
            scanf_s("%d", &month);                                                              // if - задел на будущее для исправления ошибки с бесконечным циклом
        }

        if (month < 1 || month > 12) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", month);
            arr[*counter].date.mm = month;
            break;
        }
    }

    while (true) {
        int year = -1;

        if (year == -1) {
            printf("Введите год редактирования (целое число от -999 до 9999 включительно):");      // При вводе символов будет бесконечный цикл. Исправить пока не смог
            scanf_s("%d", &year);                                                                  // if - задел на будущее для исправления ошибки с бесконечным циклом
        }

        if (year < -999 || year > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", year);
            arr[*counter].date.yyyy = year;
            break;
        }
    }

    *counter += 1;
}

// 2. Загрузка данных из txt. Файл лежит в дирректории проекта. Разделитель - точка с запятой. Проверка на корректность данных в файле отсутствует. Последняя строка должна оканчиваться разделителем
void loadData(changingString* arr, int *counter) {
    FILE* fileptr;
    char nameFile[100]; // строка для имени файла

    // считаная строка
    char str[50];
    char* estr;

    printf("Введите название файла:");
    scanf_s("%100s", &nameFile, 100);

    fileptr = fopen(nameFile, "r");

    if (fileptr == NULL) {
        printf("Файл не найден\n");
        printf("Возврат в меню\n");
    }
    else {
        
        while (true) {

            // Чтение одной строки из файла
            estr = fgets(str, sizeof(str), fileptr);

            if (estr == NULL){

                if (feof(fileptr) != 0) {
                    // файл закончился
                    printf("Файл успешно прочитан. Данные добавлены к имеющейся таблице\n");
                    break;
                } else {
                    // ошибка чтения
                    printf("Ошибка чтения из файла\n");
                    break;
                }
            }

            // передача строки на обработку
            readStr(&str, arr, counter);
        }

        fclose(fileptr);
    }
}

// 2.вспомогательная. Разбор строки на составные элементы
void readStr(char * str, changingString* arr, int *counter) {
    char arrResult[6][100];             // массив из 6 строковых значений
    int countArray = 0;                 // счётчик данного массива

    char result[100];                   // изъятый фрагмент строки с данными, которые будут занесены в вышеназванный массив
    int count = 0;                      // счётчик данного массива

    // проход по одной строке из документа
    for (int i = 0; i < strlen(str)-1; i++) {

        if (str[i] != ';') {
            result[count] = str[i];
            count++;
        }
        else {
            result[count] = '\0';

            strcpy(arrResult[countArray], result);
            countArray++;

            memset(result, 0, 100);
            count = 0;
        }

        // для записи в массив строк последнего элемента
        if (str[i+1] == '\n') {
            result[count] = '\0';

            strcpy(arrResult[countArray], result);
            countArray++;

            memset(result, 0, 100);
            count = 0;
        }
    }

    //на данном этапе сформирован массив строк с исходными данными
    // данный масив записывается в необходимые места, но прежде строки конвертируются в числа (где это нужно).
    arr[*counter].pageNumber = atoi(arrResult[0]);
    arr[*counter].lineNumber = atoi(arrResult[1]);
    strcpy(arr[*counter].changeText, arrResult[2]);
    arr[*counter].date.dd = atoi(arrResult[3]);
    arr[*counter].date.mm = atoi(arrResult[4]);
    arr[*counter].date.yyyy = atoi(arrResult[5]);

    *counter += 1;
}

// 3. Сохранение данных в txt. Без проверки на возможность создания файла
void saveData(changingString* arr, int counter) {
    FILE* fileptr;
    char nameFile[100]; // строка для имени файла

    printf("Введите название файла:");
    scanf_s("%100s", &nameFile, 100);

    fileptr = fopen(nameFile, "w");

    for (int i = 0; i < counter; i++) {

        char str[200];

        sprintf(str, "%d;", arr[i].pageNumber);

        char val[100];
        sprintf(val, "%d;", arr[i].lineNumber);
        strcat(str, val);
        memset(val, 0, 100);

        strcat(str, arr[i].changeText);

        sprintf(val, ";%d;", arr[i].date.dd);
        strcat(str, val);
        memset(val, 0, 100);
        
        sprintf(val, "%d;", arr[i].date.mm);
        strcat(str, val);
        memset(val, 0, 100);

        sprintf(val, "%d\n", arr[i].date.yyyy);
        strcat(str, val);
        memset(val, 0, 100);

        fputs(str, fileptr);
    }

    printf("Таблица успешно сохранена в файл '%s'", nameFile);
    fclose(fileptr);
}

// 4. функция выводит содержимое массива в виде таблицы
void printArr(changingString* arr, int counter) {
    char lineHor[111] = "--------------------------------------------------------------------------------------------------------------\0";

    printf("\n");
    printf("Массив данных:\n");
    printf("%s\n", lineHor);
    printf("|PAGE|LINE|                                     NEW LINE TEXT                                     |   DATE   |\n");
    printf("%s\n", lineHor);

    for (int i = 0; i < counter; i++) {

        if (strlen(arr[i].changeText) > 82) {
            printf("|%4d|%4d| %.82s... |%2d.%2d.%4d|\n", arr[i].pageNumber, arr[i].lineNumber, arr[i].changeText, arr[i].date.dd, arr[i].date.mm, arr[i].date.yyyy);
            printf("%s\n", lineHor);
        }
        else {
            printf("|%4d|%4d| %85.99s |%2d.%2d.%4d|\n", arr[i].pageNumber, arr[i].lineNumber, arr[i].changeText, arr[i].date.dd, arr[i].date.mm, arr[i].date.yyyy);
            printf("%s\n", lineHor);
        }
    }
    //printf("--------------------------------------------------------------------------------------------------------------\n");
}

// 5. Функция сортирует массив в порядке возрастания. сортировка по дате пока отсутствует
void sortArrayAsc(changingString* arr, int counter) {

    int number = 0;
    printf("Введите номер поля, по которому будет проводиться сортировка (в рамках данного задания доступны 1 и 2): ");
    scanf_s("%d", &number);

    if (number == 1 || number == 2) {

        for (int i = counter - 1; i > 0; i--) {

            for (int k = 0; k < i; k++) {

                if (number == 1) {

                    if (arr[k].pageNumber > arr[k + 1].pageNumber) {

                        changingString buffer;

                        buffer = arr[k];
                        arr[k] = arr[k + 1];
                        arr[k + 1] = buffer;
                    }
                }
                else if (number == 2) {

                    if (arr[k].lineNumber > arr[k + 1].lineNumber) {

                        changingString buffer;

                        buffer = arr[k];
                        arr[k] = arr[k + 1];
                        arr[k + 1] = buffer;
                    }
                }
            }
        }

        printf("Сортировка выполнена успешно\n");
    }
    else {
        printf("Введены некорректные значения\n");
    }
}

// 6. Функция поиска


// 7. Функция удаления записи по номеру
void delNoteInArray(changingString* arr, int* counter) {

    int number = 0;
    printf("Введите порядковый номер записи, которую необходимо удалить:");
    scanf_s("%d", &number);

    if (number > *counter || *counter == 0) {
        printf("Данная запись отсутствует в таблице\n");
        exit;
    }
    else if (number == *counter && *counter>0) {
        *counter -= 1;
    }
    else {

        for (int i = number - 1; i < *counter-1; i++) {

            arr[i] = arr[i + 1];
        }

        *counter -= 1;
    }
    printf("Данная запись успешно удалена\n");
}

// 8. Функция для изменения содержимого строки
void changeNodeInArray(changingString* arr, int counter) {
    int val = 0;
    char text[101];
    int number = 0;
    printf("Введите порядковый номер строки для внесения изменений:");
    scanf_s("%d", &number);

    if (number > counter) {
        printf("Данная строка отсутствует\n");
        exit;
    }

    int column = 0;
    printf("Введите номер cтолбца для внесения изменений (от 1 до 6 включительно):");
    scanf_s("%d", &column);

    switch (column) {
    case 1:
        
        printf("Введите значение номера страницы (целое число от 0 до 9999 включительно):");
        scanf_s("%d", &val);

        if (val < 0 || val > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", val);
            arr[number - 1].pageNumber = val;
        }

        break;
    case 2:

        printf("Введите значение номера строки (целое число от 0 до 9999 включительно):");
        scanf_s("%d", &val);

        if (val < 0 || val > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", val);
            arr[number - 1].lineNumber = val;
        }

        break;
    case 3:

        printf("Введите текст (ограничено 100 символами):");      // Проверок нет. Разделители не вводить
        scanf_s("%100s", text, 100);

        strcpy_s(arr[number - 1].changeText, 100, text);

        break;
    case 4:

        printf("Введите день редактирования (целое число от 1 до 31 включительно):");
        scanf_s("%d", &val);

        if (val < 0 || val > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", val);
            arr[number - 1].date.dd = val;
        }

        break;
    case 5:

        printf("Введите месяц редактирования (целое число от 1 до 12 включительно):");
        scanf_s("%d", &val);

        if (val < 0 || val > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", val);
            arr[number - 1].date.mm = val;
        }

        break;
    case 6:

        printf("Введите год редактирования (целое число от -999 до 9999 включительно):");
        scanf_s("%d", &val);

        if (val < 0 || val > 9999) {
            printf("Неверный ввод. Попробуйте снова\n");
        }
        else {
            printf("Введены корректные данные: %d\n", val);
            arr[number - 1].date.yyyy = val;
        }

        break;
    default:
        printf("Введены некорректные значения\n");
        break;
    }
}