// Дано число и его система счисления. Орагнизовать систему, которая будет преобразовывать исходное число в число других систем счисления

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAXSTRING 51

// перевод из десятичной СС в любую до 36
void fromDecimal(int radix, int num, int notation) {
	int result = num;
	int index = 0;

	int arr[MAXSTRING];
	char res[MAXSTRING];

	// формирование массива с числом, "записанным" задом наперёд
	do {
		arr[index] = result % notation;
		result /= notation;
		index++;
	} while (result >= notation);
	arr[index] = result;

	// разворот массива
	for (int i = 0; i <= index; i++) {
		int c = arr[index - i];

		if (c <= 9) {
			res[i] = c + 48;
		}
		else {
			res[i] = c + 55;
		}
	}
	res[index + 1] = '\0';

	printf("Число %d в СС с основанием %d равно числу %s в СС с основанием %d\n", num, radix, res, notation);
}

// перевод числа из любой СС (до 36) в десятичную
int toDecimal(int radix, char *num) {
	int size = 0;
	int indexStr = 0;
	int result = 0;

	// подсчёт количества символов в строке
	while (num[size] != '\0') {
		size++;
	}

	while (num[indexStr] != '\0')
	{
		// Если обрабатывается число, тогда ...
		if (num[indexStr] >= 48 && num[indexStr] <= 57) {
			int x = num[indexStr] - 48;
			int y = size - indexStr-1;
			result += x * pow(radix, y);
		}
		// иначе обрабатывается буква ...
		else {
			int x = num[indexStr] - 55;
			int y = size - indexStr - 1;
			result += x * pow(radix, y);
		}

		indexStr++;
	}

	return result;
}

// проверка введённых значений
bool correctValue(char* num, int radix) {
	int indexStr = 0, maxNumeral = 0; // индекс, максимальная цифра в числе

	while (num[indexStr] != '\0') {
		
		// программа работает только с СС с основанием меньше 37 и больше 1
		if (radix < 2 && radix > 36) {
			return 0;
		}

		// если ascii код элементов строки принадлежит числам и заглавным английским буквам, тогда ...
		if ((num[indexStr] >= 48 && num[indexStr] <= 57) || (num[indexStr] >= 65 && num[indexStr] <= 90)) {
			
			// перевод кодов в численные значения (десятичная система)
			// если обрабатывается цифра, тогда ...
			if (num[indexStr] < 65) {

				// если текущее число больше записанного в переемнную maxNumeral
				if (maxNumeral < num[indexStr] - 48) {
					maxNumeral = num[indexStr] - 48;
				}
			}
			// иначе обрабатывается буква, тогда ...
			else {

				// если текущее число больше записанного в переемнную maxNumeral
				if (maxNumeral < num[indexStr] - 55) {
					maxNumeral = num[indexStr] - 55;
				}
			}

			// если число содержит цифру, которая н еможет содержаться в числе с заданным основанием СС, то выход с 0 - false
			if (maxNumeral >= radix) {
				return 0;
			}
			
			indexStr++;
		}
		// если не принадлежит выход с 0 - false
		else {
			return 0;
		}
	}

	return 1;
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	char number[MAXSTRING];
	int radix = 0;

	printf("Введите число (макс. символов: 50, [0-9A-Z]): ");
	scanf_s("%50s", &number, 50);

	printf("Введите основание системы счисления (от 2 до 36): ");
	scanf_s("%d", &radix);

	if (!correctValue(&number, radix)) {
		printf("Введённые данные некорректны");
		return 1;
	}
	else {
		if (radix != 10) {

			for (int i = 2; i <= 36; i++) {
				fromDecimal(radix, toDecimal(radix, &number), i);
			}
		}
		else {
			int result = atoi(number);

			for (int i = 2; i <= 36; i++) {
				fromDecimal(radix, result, i);
			}

		}
		
	}

	return 0;
}