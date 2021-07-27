// Реализация протокола Диффи - Хелмана

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int factorization(int p, int* fact);
int calcPrimitiveRoot(int p, int size, int* fact);
int calcRemainder(int r, int deg, int p);
int generate(int p);
int sessionKey(int pr, int num, int p);
int secretKey(int pr, int sessKey, int p);

int main() {
	char* locale = setlocale(LC_ALL, "");

	int p = 647;										// Простое число
	
	int fact[100];										// массив простых множителей для (p-1) 
	int sizeArr = factorization(p, &fact);				// количество простых множителей в массиве fact
	int pr = calcPrimitiveRoot(p, sizeArr, &fact);		// значение первообразного корня по модулю p

	int a = generate(p);
	int sessionKeyA = sessionKey(pr, a, p);

	int b = generate(p);
	int sessionKeyB = sessionKey(pr, b, p);

	int calcThroughA = secretKey(pr, sessionKeyB, p);
	int calcThroughB = secretKey(pr, sessionKeyA, p);

	sessionKeyA = 0;
	sessionKeyB = 0;

	return 0;
}

// разложение на простые множители
int factorization(int p, int * fact) {

	int number = 2;		// первое исследуемое число
	int result = p-1;		// результат деления	
	int count = 0;		// счётчки заполнения массива

	while (result >= number) {

		if (result%number == 0) {
			result /= number;

			// внесение делителя в массив
			fact[count] = number;
			count++;
		}
		else {
			number++;
		}
	}

	return count;
}

// Функция высчитывающая первообразный корень по модулю
int calcPrimitiveRoot(int p, int size, int * fact) {
	int rmndr = 0;

	// перебор среди [2;p-1)
	for (int r = 2; r < p - 1; r++) {
		int count = 0;

		// проход по каждому числу в массиве простых множителей. Можно исключить дублирование операция для одинаковых множителей
		for (int i = 0; i < size; i++) {

			int exp = (p - 1) / fact[i];

			rmndr = calcRemainder(r, exp, p);

			count++;

			// если операция с одним из множителей массива даёт единицу, то остальные можно не проверять
			if (rmndr == 1) {
				count = 0;
				break;
			}
		}

		// если деление всех чисел в группе на модуль не равно 1:
		if (count == size) {
			return r;
		}
	}
}

// Своего рода костыль. Например 2 в 168 степени в int или long не помещается. Поэтому 2 умножается на себя в цикле и сразу же делится с остатком
// Вероятно существует свойство чисел при делении с остатком, позволяющее сделать это более эффективно
// Функция высчитывающая остаток от деления числа r в степени deg на число p
int calcRemainder (int r, int deg, int p) {
	int rmndr = 1;

	for (int i = 1; i <= deg; i++) {

		int res = rmndr * r;
		rmndr = res % p;
	}

	return rmndr;
}

// Функция для генерирования случайного числа в пределах [2, p-1)
int generate(int p) {
	int result = 0;
	srand(time(NULL));
	result = 2 + rand() % (p - 2);
	return result;
}

// Функция создания сессионного ключа
int sessionKey(int pr, int num, int p ) {
	int sKey = 0;

	sKey = calcRemainder(pr, num, p);

	return sKey;
}

// Функция создания секретного ключа
int secretKey(int pr, int sessKey, int p) {
	int secKey = 0;

	secKey = calcRemainder(pr, sessKey, p);

	return secKey;
}