// Функция находит в строке пары фрагментов, содержащих последовательность одинаковых символов длиной более 3 
// (кроме пробела) и возвращает динамический массив указателей на копии таких фрагментов.

#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAXSTRING 100
#define SIZEFRAG 3 // размер фрагмента для поиска. 

// удаление пробелов. По условию: пробел - не считается. 
void delSpaces(char* str) {
	int indexStr = 0;
	int size = strlen(str);
	while (str[indexStr] != '\0') {

		if (str[indexStr] == ' ') {

			for (int i = 0; i < size - indexStr; i++)
				str[indexStr + i] = str[indexStr + 1 + i];

		}

		indexStr++;
	}
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	// Исходная строка
	char str[MAXSTRING] = "012 45 6012 78945 012";
	int indexStr = 0;
	int countNum = 0; // количество найденных фрагментов
	printf("Исходная строка: %s\n", &str);

	// выделение памяти под ДМУ. 
	// Данный массив будет содержать абсолютно копии фрагментов, найденные в строке. Исходный поисковый фрагмент не будет включён
	char** arr = (char**)malloc(sizeof(char*));

	// удаление пробелов
	delSpaces(&str);

	printf("Анализируемая строка: %s\n", &str);

	while (str[indexStr+SIZEFRAG] != '\0') {

		// формирование массива из 3х символов. При изменении sizefrag необходимо вручную менять инициализацию
		char selected[SIZEFRAG] = {str[indexStr], str[indexStr+1], str[indexStr+2] };

		// пройтись по оставшимся возможным элементам строки
		for (int i = 0; i < strlen(str) - 2*SIZEFRAG + 1; i++) {

			printf("Шаг\n");

			// Поиск совпадения в строке. При изменении sizefrag необходимо вручную менять условие
			if (str[indexStr + 3 + i] == selected[0] && str[indexStr + 4 + i] == selected[1] && str[indexStr + 5 + i] == selected[2]) {
				printf("Есть совпадение\n");

				// При изменении sizefrag необходимо вручную менять инициализацию
				char frag[SIZEFRAG+1] = { str[indexStr + 3 + i], str[indexStr + 4 + i] , str[indexStr + 5 + i] , '\0'};

				arr[countNum] = (char*)malloc(sizeof(char*) * (SIZEFRAG + 1));

				strcpy_s(arr[countNum], 4, frag);

				countNum++;

			}
		}

		indexStr++;
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
