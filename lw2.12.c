// Функция находит в строке фрагменты, симметричные относительно центрального символа, длиной 7 и более символов (например, "abcdcba") 
// и возвращает динамический массив указателей на копии таких фрагментов.

// Задание 4. 'l' = 108, 108%9 = 0, 108/9=12, 12 больше количества заданий (12-9 == 3). Задание 3 уже готово, взял следующее

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAXSTRING 100
#define NUMCHAR 3 // количество символов в каждую сторону от центрального. В исходных данных длина искомого фрагмента 7+ (3 слева, центральный, 3 справа) 

int main() {
    char* locale = setlocale(LC_ALL, "");

    char str[MAXSTRING] = "yjoabcdcbarstqwertrewq\0";
    int countNum = 0;  // счётчик количества найденных фрагментов

    // выделение памяти под ДМУ. 
    char** arr = (char**)malloc(sizeof(char*));

    // В условии указано, что искать нужно фрагменты 7+ символов. Если строка меньше такой длины, то и фрагмента там не будет
    if (strlen(&str) < NUMCHAR*2+1) {
        printf("Строка меньше %d символов\n", NUMCHAR * 2 + 1);
        return 1;
    }
    else {
        int count = 0; // счётчик количества симметричных символов (с одной стороны)

        // перебор элементов, но не всех, а лишь тех, которые могут быть центрами симметричных фрагментов
        for (int i = NUMCHAR; i < strlen(&str) - 1 - NUMCHAR; i++) {

            // подсчёт количества симметричных символов
            for (int j = 1; str[i + j] == str[i - j]; j++) {
                count++;
            }

            // если фрагмент необходимой длины
            if (count >= NUMCHAR) {
                
                // формирование фрагмента
                char val[MAXSTRING];
                for (int k = 0; k < count * 2 + 1; k++) {
                    val[k] = str[i-count+k];
                }
                val[count * 2 + 1] = '\0';

                arr[countNum] = (char*) malloc (sizeof(char*)*(strlen(val) + 1));

                strcpy_s(arr[countNum], strlen(val) + 1, val);
                                
                countNum++;
            }

            count = 0;
        }
    }

    if (countNum == 0) {
        printf("Фрагменты в строке не найдены");
        return 1;
    }
    else {
        printf("Найдено %d фрагментов:\n", countNum);
        for (int i = 0; i < countNum; i++) {
            printf("%d фрагмент: %s\n", i + 1, arr[i]);
        }
    }

    return 0;
}
