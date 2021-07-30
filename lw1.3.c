// Дано число и его система счисления. Орагнизовать систему, которая будет преобразовывать исходное число в число других систем счисления
// Работает только с целыми и положительными числами

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXSTRLEN 31

void setRedix(int* radix);
void setNum(char* num, int *radix);
bool validRangeOfValues(int x, int y, int num);
void fromDecimal(int *radix, char *num, int *notation);
int toDecimal(int *radix, char* num);

int main() {
	char* locale = setlocale(LC_ALL, "");

	char number[MAXSTRLEN+1];			// строка с исходным числом, которое вводит пользователь
	int radix = 0;						// СС, определяемая пользователем

	setRedix(&radix);
	setNum(number, &radix);
	
	for (int i = 2; i <= 36; i++) {
		fromDecimal(&radix, number, &i);
	}

	return 0;
}

// функция для получения основания СС от пользователя
void setRedix(int* radix) {
	char rdx[10];
	bool isIncorrect = true;

	printf("Введите основание системы счисления (от 2 до 36): ");

	while (isIncorrect) {

		fgets(rdx, 10, stdin);

		// Если введено больше 10 символов. Необходимо для очистки stdin от мусора. 
		if (rdx[strlen(rdx) - 1] != '\n') {
			while (getchar() != '\n');
		}

		// Если строка имеет 1 или 2 символа (как числа в интервале от 2 до 36)
		if (validRangeOfValues(2, 3, strlen(rdx))) {

			bool isNum = false;
			int indexStr = 0;

			while (rdx[indexStr] != '\n') {

				if (rdx[indexStr] >= 48 && rdx[indexStr] <= 57) {
					indexStr++;
					isNum = true;
				}
				else {
					printf("Введено некорректное значение. Допустимы только числа\n");
					printf("Попробуйте снова: ");
					isNum = false;
					break;
				}
			}

			if (isNum) {
				int num = atoi(rdx);

				if (validRangeOfValues(2, 36, num)) {
					isIncorrect = false;
					*radix = num;
				}
				else {
					printf("Введено некорректное значение. Недопустимое значение\n");
					printf("Попробуйте снова: ");
				}
			}
		}
		else {
			printf("Введено некорректное значение. Недопустимое число символов\n");
			printf("Попробуйте снова: ");
		}
	}
}

// функция для получения числа от пользователя
void setNum(char* num, int *radix) {

	printf("Введите число (макс. символов: 31, [0-9A-Z]): ");	// для int максимальное число 2147483647, что в двоичной системе - 31 единица

	while (true) {

		fgets(num, MAXSTRLEN+1, stdin);

		// Если введено больше 31 символа. Необходимо для очистки stdin от мусора. 
		if (num[strlen(num) - 1] != '\n') {
			while (getchar() != '\n');
		}

		int indexStr = 0;		// индекс для прохода по строке
		int maxNumeral = 0;		// значение максимального числа в строке (при переводе в десятичную)
		bool isNum = true;		// флаг "Это число"

		while (num[indexStr] != '\n') {

			if ((num[indexStr] >= 48 && num[indexStr] <= 57) || (num[indexStr] >= 65 && num[indexStr] <= 90)) {
			
				// перевод кодов в численные значения (десятичная система)
				// если обрабатывается цифра, тогда ...
				if (num[indexStr] < 65) {

					if (maxNumeral < num[indexStr] - 48) {
						maxNumeral = num[indexStr] - 48;
					}
				}
				// иначе обрабатывается буква, тогда ...
				else {

					if (maxNumeral < num[indexStr] - 55) {
						maxNumeral = num[indexStr] - 55;
					}
				}

				// если число содержит цифру, которая н еможет содержаться в числе с заданным основанием СС, то выход с 0 - false
				if (maxNumeral >= *radix) {
					printf("Введено некорректное значение. Число не может быть записано в исходной СС\n");
					printf("Попробуйте снова: ");
					isNum = false;
					break;
				}
			}
			else {
				printf("Введено некорректное значение. Число содержит недопустимые символы\n");
				printf("Попробуйте снова: ");
				isNum = false;
				break;
			}

			indexStr++;
		}

		if (isNum) {
			num[indexStr] = '\0';
			break;
		}
	}
}

// Допустимая интервал значений. x - "включительно от", y - "включительно до", num - текущее значений.
bool validRangeOfValues(int x, int y, int num) {
	if (x <= num && num <= y) {
		return 1;
	}
	return 0;
}

// перевод из десятичной СС в любую до 36. radix - текущая СС, num - число в строковом представлении, notation - требуемая СС
void fromDecimal(int *radix, char *num, int *notation) {
	int result = 0;						// Значение числа в десятичной системе

	if (!validRangeOfValues(2, 36, *radix)) {
		printf("Неверное значение первого параметра - текущая система счисления (от 2 до 36 включительно)\n");
		exit(1);
	}

	if (strlen(num) == 0) {
		printf("Неверное значение второго параметра - передана пустая строка с числом\n");
		exit(1);
	}

	if (!validRangeOfValues(2, 36, *notation)) {
		printf("Неверное значение третьего параметра - требуемая система счисления (от 2 до 36 включительно)\n");
		exit(1);
	}

	if ((*radix) == 10) {
		result = atoi(num);
	}
	else {
		result = toDecimal(radix, num);
	}

	if (result < *notation-1) {
		printf("Число %s в СС с основанием %d нельзя перевести в СС с основанием %d\n", num, *radix, *notation);
		exit(0);
	}

	int arr[MAXSTRLEN+1];				// массив с числом, записанным задом наперёд
	char res[MAXSTRLEN+1];				// массив для разворота числа
	int indexStr = 0;					// счётчик для перебора массива

	// формирование массива с переведённым числом, записанным задом наперёд
	do {
		arr[indexStr] = result % *notation;
		result /= *notation;
		indexStr++;
	} while (result >= *notation);
	arr[indexStr] = result;

	// разворот массива + перевод чисел/цифр в буквенное представление
	for (int i = 0; i <= indexStr; i++) {
		int c = arr[indexStr - i];

		if (c <= 9) {
			res[i] = c + 48;
		}
		else {
			res[i] = c + 55;
		}
	}
	res[indexStr + 1] = '\0';

	printf("Число %s в СС с основанием %d равно числу %s в СС с основанием %d\n", num, *radix, res, *notation);
}

// перевод числа из любой СС (до 36) в десятичную
int toDecimal(int *radix, char *num) {
	int indexStr = 0;		// индекс элемента массива num
	int result = 0;			// результат перевода

	while (num[indexStr] != '\0')
	{
		// Если обрабатывается число, тогда ...
		if (num[indexStr] >= 48 && num[indexStr] <= 57) {
			int x = num[indexStr] - 48;
			int y = strlen(num) - indexStr - 1;
			result += x * pow(*radix, y);
		}
		// иначе обрабатывается буква ...
		else {
			int x = num[indexStr] - 55;
			int y = strlen(num) - indexStr - 1;
			result += x * pow(*radix, y);
		}

		indexStr++;
	}

	return result;
}
