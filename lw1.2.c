// В строке найти последовательности цифр, каждую из них считать числом в той системе счисления, которая соответствует первой цифре, 
// привести найденные числа к десятичной СС.
// Пример: aaa2010101bbb8343ccc – двоичная и восьмиричная системы счисления.

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>

#define MAXSTRLEN 100

void numbersInString(char* str);
void numberProcessing(char* n);
int inDecimal(char* num, int notation, int sysNum);

int main() {
	char* locale = setlocale(LC_ALL, "");

	char str[MAXSTRLEN+1] = "eee8343c2ttt\0";

	numbersInString(str); // функция поиска чисел в строке

	return 0;
}

// функция поиска чисел в строке
void numbersInString(char *str) {
	char result[MAXSTRLEN+1];	// строка, где будет храниться найденное число
	int indexStr = 0;					// индекс элемента строки
	bool prewNum = false;		// флаг "предыдущий символ - число"

	for (int i = 0; str[i] != '\0'; i++) {
		// Проверка символа на принадлежность цифрам. 48...57 - ascii code цифр от 0 до 9
		if (str[i] >= 48 && str[i] <= 57) {

			result[indexStr] = str[i];
			indexStr++;

			// на случай, если число будет стоять в конце строки. Иначе последнее число не обрабатывается
			if (str[i + 1] == '\0') {
				result[indexStr] = '\0';
				numberProcessing(result);
				indexStr = 0;
			}

			prewNum = true;
		}
		else {
			// если предыдущий символ был числом, тогда
			if (prewNum) {
				result[indexStr] = '\0';
				numberProcessing(result);
				indexStr = 0;
			}

			prewNum = false;
		}
	}
}

// функция, обрабатывающая найденное число. Обработка заключена в определении системы счисления и переводе 
void numberProcessing(char* n) {
	printf("Найдена числовая конструкция: ");
	printf("%s\n", n);

	char stringNumber[MAXSTRLEN+1];		// число в указанной системе счисления в формате строки
	int indexStr = 1;					// индекс элемента строки
	int maxNum = 0;						// максимальная цифра

	// поиск наибольшей цифры в числе. Необходимо для проверки на корректность указанной системы счисления
	while (n[indexStr] != '\0') {
		int value = n[indexStr] - 48;

		if (value > maxNum) {
			maxNum = value;
		}

		stringNumber[indexStr - 1] = n[indexStr];

		// выйти из цикла, если всё число считано
		if (n[indexStr+1] == '\0') {
			stringNumber[indexStr] = '\0';
			break;
		}

		indexStr++;
	}

	// Число может быть обработано если основание СС строго больше максимальной цифры в найденном числе
	if ((int)(n[0] - 48) > maxNum && indexStr > 1) {
		printf("Основание системы счисления: %d, число в данной системе счисления: %s, число в десятичной системе счисления: %d\n", (int)(n[0] - 48), stringNumber, inDecimal(stringNumber, (int)(n[0] - 48), indexStr));
		printf("\n");
	}
	else {
		printf("Данная числовая конструкция не может быть интерпретирована\n");
		printf("\n");
	}
}

// функция для перевода чисел в десятичную систему. В исходной строке могут быть определены и обработаны только СС с основаниями от 2 до 9 включительно (исходя из условий).
int inDecimal(char* num, int notation, int sysNum) {
	int result = 0;

	for (int i = 0; i < sysNum; i++) {
		int x = num[i] - 48;
		double power = (double) sysNum - (double) i - 1;

		result += x * pow(notation, power);
	}

	return result;
}
