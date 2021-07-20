// "Перевернуть" в строке все слова. (Например: "Жили были дед и баба" - "илиЖ илиб дед и абаб"). Удалить слова – палинандромы.

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define MAXSTRING 100

// Палиндром слово или нет?
bool isPalindrome(char* word, char* palindrome) {
	int indexWord = 0;
	while (word[indexWord] != '\0') {

		if (word[indexWord] != palindrome[indexWord]) {
			return 0;
		}

		indexWord++;
	}
	return 1;
}

// функция обработки найденного слова
void wordProcessing(char* word) {
	char palindrome[MAXSTRING]; // строка, где будет храниться палиндром
	int sizeWord = 0;

	// длина слова:
	while (word[sizeWord] != '\0') {
		sizeWord++;
	}

	// формирование палиндрома
	for (int i = 0; i < sizeWord; i++) {
		palindrome[i] = word[sizeWord-1-i];
	}
	palindrome[sizeWord] = '\0';

	// печатать, если слово не палиндром. Задание.
	if (!isPalindrome(word, &palindrome)) {
		printf("%s ", palindrome);
	}
}

void wordInString(char* str) {
	char word[MAXSTRING]; // строка, где будет храниться найденное слово

	int indexStr = 0;
	int count = 0;
	bool prewSpace = true; // флаг "предыдущий символ был пробелом"

	while (str[indexStr] != '\0') {
		// если обрабатываемый символ - не пробел, тогда ...
		if (str[indexStr] != ' ') {

			// если предыдущий символ был пробелом, тогда ...
			if (prewSpace) {
				word[0] = str[indexStr]; // значит слово только началось и массив заполняется с начала
			}
			// если предыдущий символ не был пробелом
			else {
				count++;
				word[count] = str[indexStr]; // буквы слова заполняют массив
			}

			// на случай, если слово будет стоять в конце строки
			if (str[indexStr+1] == '\0') {
				// Слово закончилось и записывается символ окончания строки
				count++;
				word[count] = '\0';
				wordProcessing(&word);

				//очищение строки с найденным числом (для поиска следующего)
				count = 0;
				memset(word, 0, MAXSTRING);
			}

			prewSpace = false;
		}
		// если обрабатываемый символ - пробел, тогда ...
		else {
			// если предыдущий символ не был пробелом, тогда ...
			if (!prewSpace) {
				// Слово закончилось и записывается символ окончания строки
				count++;
				word[count] = '\0';

				wordProcessing(&word);

				//очищение строки с найденным числом (для поиска следующего)
				count = 0;
				memset(word, 0, MAXSTRING);
			}

			prewSpace = true;
		}
		indexStr++;
	}
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	char str[MAXSTRING] = "Жили были дед и баба\0";

	wordInString(&str); // функция поиска слов в строке (словом является сочетание букв, отделёное с двух сторон пробелом (первое и последнее слово отделяются пробелом с одной стороны))

	return 0;





}