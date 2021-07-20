#include <stdio.h>

int main() {
	char surname[6] = "Volkov";
	char* p;

	int lab[4] = { 12, 9, 14, 14 };

	int arr[3][4]; // Количество строк и столбцов

	for (int i = 0; i < 3; i++) {
		p = &surname[i];
		int code = *p;

		for (int j = 0; j < 4; j++) {
			
			arr[i][j] = code % lab[j];

			if (arr[i][j] == 0) {
				arr[i][j] = code / lab[j];
			}
		}
	}

	return 0;
}

