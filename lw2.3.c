// Функция получает строку, находит самый внутренний фрагмент в скобках и вырезает его. Операция повторяется до тех пор, пока не останется скобок. 
// Полученные фрагменты и остаток строки вернуть в динамическом массиве указателей.

#include <stdio.h>
#include <locale.h>.
#include <stdlib.h>
#include <string.h>



#define MAXSTRING 100


// вырезать фрагмент. Исходная строка меняется
void cutFrag(char * str, int ptrFirst, int ptrLast) {
	int countNum = 0;
	int size = strlen(str);

	for (int i = 0; i < size - ptrLast; i++) {
		str[ptrFirst+i] = str[ptrLast + 1+i];
	}
}

// найти пару скобке. Возвращает индекс парной скобки
int findPair(char* str, int ptr) {
	int indexStr = ptr;

	while (str[indexStr] != '\0') {

		if (str[indexStr] == ')') {
			return indexStr;
		}

		indexStr++;
	}
}

// найти последнюю скобку. Возвращает индекс первой скобки
int findLast(char* str) {
	int indexStr = 0;
	int ptr = -1;

	while (str[indexStr] != '\0') {
		if (str[indexStr] == '(') {
			ptr = indexStr;
		}
		indexStr++;
	}

	return ptr;
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	// Строка должна быть составлена корректно. Каждая скобка должна иметь пару и пара должна начинаться с открывающейся скобки.
	char str[MAXSTRING] = "(qw(jt)g(ldv))dsa\0";
	printf("Исходная строка: %s\n", &str);

	char** arr = (char**)malloc(sizeof(char*));
	int countNum = 0; // счётчик количества найденных фрагментов (пар скобок)

	// бесконечный цикл. Выход - отсутствие открывающихся скобок
	while (1) {

		int start = findLast(&str); // индекс открывающейся скобки

		if (start == -1) {
			//выход из цикла, если скобки закончились (как минимум нет открывающейся)
			break;
		}

		int end = findPair(&str, findLast(&str)); // индекс закрывающейся

		//формирование фрагмента
		char val[MAXSTRING];
		for (int i = 0; i < end-start-1; i++) {
			val[i] = str[start + i+1];
		}
		val[end-start] = '\0';

		arr[countNum] = (char*)malloc(sizeof(char*) * (strlen(val) + 1));

		strcpy_s(arr[countNum], strlen(val) + 1, val);

		//вырезать найденный фрагмен твместе со скобками
		cutFrag(&str, start, end);
		countNum++;
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
		printf("Оставшаяся строка: %s\n", &str);
	}

	return 0;
}
