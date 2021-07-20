// В строке найти последовательности цифр, каждую из них считать числом в той системе счисления, которая соответствует первой цифре, 
// заменить числа в строке символами с кодами, полученными из этих чисел.
// Пример: aaa2010101bbb8343ccc – двоичная и восьмиричная системы счисления.

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAXSTRING 100


// функция для перевода чисел в десятичную систему. В исходной строке могут быть определены и обработаны только систмеы с основаниями от 2 до 9.
int inDecimal(char *num, int notation, int sysNum) {
	int result = 0;

	for (int i = 0; i < sysNum; i++) {
		int x = num[i] - 48;
		result += x * pow(notation, (sysNum-i-1));
	}

	return result;
}


// функция, обрабатывающая найденное число
void numberProcessing(char* n) {
	printf("Найдена числовая конструкция: ");
	printf("%s\n", n);
	int maxNum = 0, i = 0, sysNum = 0; // максимальная цифра, номер элемента, количество цифр в исходном числе
	char stringNumber[MAXSTRING]; // число в указанной системе счисления в формате строки
	int intNumber = 0; // число в указанной системе счисления в формате integer

	int notation = n[0] - 48; // ascii-код первого символа в число. Переменная - система счисления

	// поиск наибольшей цифры в числе. Необходимо для проверки на корректность указанной системы счисления + количество цифр в числе
	while (n[i] != '\0') {
		int value = n[i] - 48;

		if (i != 0) {
			if (value > maxNum) {
				maxNum = value;
			}

			stringNumber[i-1] = n[i];
		}

		i++;
	}

	stringNumber[i - 1] = '\0';
	intNumber = atoi(stringNumber);

	sysNum = i - 1;

	// если число может быть обработано, тогда
	if (notation > maxNum && sysNum != 0) {
		printf("Основание системы счисления: %d, число в данной системе счисления: %d, число в десятичной системе счисления: %d\n", notation, intNumber, inDecimal(&stringNumber, notation, sysNum));
		printf("\n");
	}
	// иначе... 
	else {
		printf("Данная числовая конструкция не может быть интерпретирована\n");
		printf("\n");
	}
}

void numbersInString(char* str) {
	char result[MAXSTRING]; // строка, где будет храниться найденное число

	int indexStr = 0;
	int count = 0;
	bool prewNum = false; // флаг "предыдущий символ был числом"

	while (str[indexStr] != '\0') {
		// если обрабатываемый символ - число, тогда ...
		if (isdigit(str[indexStr])) {
			// если предыдущий символ также был числом, тогда
			if (prewNum) {
				count++;
				result[count] = str[indexStr]; // строка с числом заполняется
			}
			// если предыдущий символ не был числом
			else {
				result[0] = str[indexStr]; // начинает заполняться строка
			}

			prewNum = true;
		}
		// если обрабатываемый символ - не число, тогда ...
		else {
			// если предыдущий символ был числом, тогда
			if (prewNum) {
				// записывается символ окончания строки
				count++;
				result[count] = '\0';

				numberProcessing(&result);

				//очищение строки с найденным числом (для поиска следующего)
				count = 0;
				memset(result, 0, 100);
			}
			prewNum = false;
		}

		indexStr++;
	}
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	char str[MAXSTRING] = "aaa2010101bbb8343ccc12ddd\0";

	numbersInString(&str); // функция поиска чисел в строке

	return 0;
}
