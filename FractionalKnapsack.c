// Жадный алгоритм. Задача с рюкзаком
// Матрица предметов:	[0] id предмета: 
//						[1] ценность; 
//						[2] вес; 
//						[3] удельная стоимость (0 - необходимо рассчитать); 
//						[4] количество имеющихся преметов (-1 - неогрниченное количество).

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define KNAPSACK 22			// вместимость рюкзака
#define NUMBEROFITEMS 3		// количество типов предметов

#define COLUMNS 5			// количество колонок в исходной матрице


void printResult(int * res, int size) {
	printf("Данная стоимость достигается следующим набором предметов:\n");

	for (int i = 0; i < size; i++) {
		printf("%d ", res[i]);
	}

	printf("\n");
}

void filling(int rows, float arr[][COLUMNS]) {
	float result = 0; // текущий вес рюкзака
	float totalCost = 0;

	int numbersOfItems[500]; // 500 предметов будет вмещать мешок
	
	int countNumberOfItem = 0; // счётчик для заполнения вышеуказанного массива numbersOfItems[].
	
	// прогон по каждому типу вещей
	for (int i = 0; i < rows; i++) {
		int countNumberOfItemsUsed = 0; // счётчик использованных предметов конкретного типа. Можно не использовать счётчик, а просто уменьшать число в ячейке arr[i][4]

		while (1) {

			if (result + arr[i][2] <= KNAPSACK) {

				if (arr[i][4] == -1) {
					// количество вещей данного типа неограничено. Складывать, пока не закончится место
					result += arr[i][2];

					numbersOfItems[countNumberOfItem] = arr[i][0];
					totalCost += arr[i][1];

					countNumberOfItem++;
				}
				else if (arr[i][4] == 0) {
					//printf("Вещь закончилась\n");
					break;
				}
				else {
					// количество вещей данного типа ограничено. Складывать, пока не закончится товар или место
					// если предметы ещё есть
					if (countNumberOfItemsUsed < arr[i][4]) {
						result += arr[i][2];

						numbersOfItems[countNumberOfItem] = arr[i][0];
						totalCost += arr[i][1];

						countNumberOfItem++;
						countNumberOfItemsUsed++;
					}
					else {
						//printf("Вещь закончилась\n");
						break;
					}
				}
			}
			else {
				// если вес анализируемого товара не помещается в рюкзак - выйти из while, чтобы перейти к следующей вещи.
				//printf("Вещь не помещается\n");
				break;
			}
		}
	}

	printf("Итоговая стоимость собранных предметов: %.3f\n", totalCost);
	printResult(&numbersOfItems, countNumberOfItem);

}

//сортировка строк массива по убыванию по значению столбца с удельным весом. Пузырьковая
void sortArrayDesc(int rows, float arr[][COLUMNS]) {

	// общее число прогонов
	for (int i = rows - 1; i > 0; i--) {

		// основной цикл перебора элементов
		for (int k = 0; k < i; k++) {

			// условие сортировки
			if (arr[k][3] < arr[k + 1][3]) {

				// перемещение каждого элемента массива в новую строку
				for (int j = 0; j < COLUMNS; j++) {
					float buffer = arr[k][j];
					arr[k][j] = arr[k+1][j];
					arr[k+1][j] = buffer;
				}
			}
		}
	}
}

// расчёт удельной стоимости
void calcUnitCost(int rows, float arr[][COLUMNS]) {

	for (int i = 0; i < rows; i++) {

		if (arr[i][3] == 0) {

			arr[i][3] = arr[i][1] / arr[i][2];

		}
	}
}

// вывод информации на экран
void printInfo(int rows, float arr[][COLUMNS]) {
	printf("Имеющиеся на данный момент данные:\n");

	for (int i = 0; i < rows; i++) {

		printf("Предмет с id-%.0f: вес - %.2f; ценность - %.3f. ", arr[i][0], arr[i][2], arr[i][1]);

		// в матрице для некоторых условий приняты соглашения. Следующие 2 оператора if проверяют данные соглашения.
		if (arr[i][3] == 0) {
			printf("Удельная стоимость не задана. ");
		}
		else {
			printf("Удельная стоимость - %.3f. ", arr[i][3]);
		}

		if (arr[i][4] == -1) {
			printf("Количество предметов неограничено.\n");
		}
		else {
			printf("Количество имеющихся предметов - %.0f.\n", arr[i][4]);
		}
	}
}


int main() {
	char* locale = setlocale(LC_ALL, "");

	// Матрица предметов: id предмета, ценность, вес, удельная стоимость (0 - необходимо рассчитать), количество имеющихся преметов (-1 - неогрниченное количество)
	float arr[NUMBEROFITEMS][COLUMNS] = {{ 1, 1, 2, 0, -1 },
										 { 2, 5, 6, 0, 2 }, 
										 { 3, 3, 4, 0, -1 }};

	printInfo(NUMBEROFITEMS, arr);			// вывод информации на экран
	calcUnitCost(NUMBEROFITEMS, arr);		// расчёт удельной стоимости 1 кг предмета
	sortArrayDesc(NUMBEROFITEMS, arr);		// сортировка строк массива
	printInfo(NUMBEROFITEMS, arr);			// вывод обновлённой информации на экран
	filling(NUMBEROFITEMS, arr);			// заполнение рюкзака + вывод результата

	return 0;
}
